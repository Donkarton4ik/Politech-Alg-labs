#include"basefile.hpp"
#include<iostream>
#include <unistd.h> //для truncate()
#include <cstring> //для strcpy

BaseFile::BaseFile(){
    file = nullptr;
    to_close = false;
    std::cout<<"Базовый конструктор, BaseFile "<< this <<std::endl;
}

BaseFile::BaseFile(const char* path, const char* mode){
    file = fopen(path, mode); //если не может открыть файл то возвращает nullptr
    if(!file){
        std::cout<< "Ошибка при работе с файлом!\n"; 
    }
    to_close = (file != nullptr);
    std::cout<<"Конструктор, открывающий файл, BaseFile "<< this <<std::endl;
}

BaseFile::BaseFile(FILE* open_file){
    file = open_file;
    to_close = false;
    std::cout<<"Конструктор для открытого файла, BaseFile "<< this <<std::endl;
}

void BaseFile::close(){
    fclose(file);
    to_close = false;
}

BaseFile::~BaseFile(){
    if(file && to_close){fclose(file);}
    std::cout<<"Деструктор, BaseFile "<< this <<std::endl;
}

bool BaseFile::is_open(){
    return file != nullptr;
}

bool BaseFile::can_read(){
    if(file == nullptr){return 0;}
    
    int ch = fgetc(file); //fgetc считываем 1 символ или возвращает EOF (~-1)
    if(ch != EOF){
        ungetc(ch, file); //возвращает символ обратно в буфер потока
        return true;
    }
    return false;
}

bool BaseFile::can_write(){
    if(file == nullptr){return 0;}

    if(fputc(' ', file) != EOF){ //fputc записывает 1 символ или возвращает EOF (~-1)
        fseek(file, 0, SEEK_END); //перемещает указатель записи на конец файла (без этого не удаляется лишний символ)
        ftruncate(fileno(file), ftell(file) - 1);//ftell возвращает длину файла в байтах, truncate укорачивает файл до n байтов
        return true;
    }
    return false;
}

size_t BaseFile::write_raw(const void *buf, size_t n_bytes){
    if (file == nullptr){return 0;}
    
    size_t bytes = fwrite(buf, 1, n_bytes, file);
    return bytes;
}

size_t BaseFile::read_raw(void *buf, size_t max_bytes){
    if (file == nullptr){return 0;}
    
    size_t bytes = fread(buf, 1, max_bytes, file);
    return bytes;
}

size_t BaseFile::write(const void *buf, size_t n_bytes){ //для задания 2.4+
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void *buf, size_t max_bytes){ //для задания 2.4+
    return read_raw(buf, max_bytes);
}

long BaseFile::tell(){
    if (file == nullptr){return 0;}
    return ftell(file);
}
        
bool BaseFile::seek(long offset){
    if (file == nullptr){return 0;}
    if(fseek(file, offset, SEEK_CUR) == 0){return true;};//SEEK_CUR - от текущей позиции; ==0 ~ успешный сдвиг
    return false;
}



Base32File::Base32File(const char* table): BaseFile(){
    strncpy(TABLE, table, 32);
    std::cout<<"Базовый конструктор, Base32File "<< this <<std::endl;
}

Base32File::Base32File(const char* path, const char* mode, const char* table): BaseFile(path, mode){
    strncpy(TABLE, table, 32);
    std::cout<<"Конструктор, открывающий файл, Base32File "<< this <<std::endl;
}

Base32File::Base32File(FILE* open_file, const char* table): BaseFile(open_file){
    strncpy(TABLE, table, 32);
    std::cout<<"Конструктор для открытого файла, Base32File "<< this <<std::endl;
}



size_t Base32File::write(const void *buf, size_t n_bytes){
    const char* char_buf = static_cast<const char*>(buf); //преобразуем из void в char
    
    int k=0;
    int len_coded = (n_bytes * 8 + 5 - 1) / 5;     //длина закодированной строки (по 5 бит)

    char* to_write = new char[len_coded]; //сюда запишем зашифрованную строку, которую передадим в write_raw

    int len_to_code = len_coded*5;               //длина двоичной вводимой строки с учётом добавочных нулей
    int* bin_raw_data = new int[len_to_code];              //двоичная вводимая строка с учётом добавочных нулей
    for(int i=0; i < static_cast<int>(n_bytes); i++){
        for(int j=7; j>=0; j--){
            bin_raw_data[k] = (static_cast<int>(char_buf[i]) >> j) & 1;
            k++;
        }
    }
    while(k<len_to_code){
        bin_raw_data[k] = 0;
        k++;
    }
    for(int i=0; i<len_coded; i++){
        int new_ch = 0; //закодированный символ (5 бит)
        for(int j=4; j>=0; j--){  //перевод бинарного символа в десятичную систему
           new_ch += bin_raw_data[i*5 + (5 - j - 1)] * (1 << j); // [i*5 + (5 - j - 1)] n-ый элемент пятёрки в бинарном массиве; (1 << j) ~ 2^j;
        }
        to_write[i] = TABLE[new_ch];
    }

    size_t t = write_raw(to_write, len_coded);
    delete [] to_write;
    delete [] bin_raw_data;
    return t;
}

size_t Base32File::read(void *buf, size_t max_bytes){
    char* get_from_file = new char[max_bytes]; //сюда считаем шифр из файла
    read_raw(get_from_file, max_bytes);

    int k = 0;
    int code_of_5; //десятичное значение бинарной пятёрки
    int len_decoded = max_bytes * 5 / 8;     //длина декодированной строки (по 8 бит)
    int len_to_decode = len_decoded*8;                 //длина двоичной декодированной строки
    int* bin_decoded_data = new int[len_to_decode];              //двоичная декодированная строка
    
    for(int i=0; i< static_cast<int>(max_bytes); i++){
        for(int j=0; j<32; j++){
            if(TABLE[j] == get_from_file[i]){
                code_of_5=j;
                break;
            }
        }
    
        for(int j=4; j>=0; j--){
            if (k < len_to_decode){  //без этого санитайзер выдает ошибку
                bin_decoded_data[k] = (code_of_5 >> j) & 1;
                k++;
            }
        }
    }
    
    for(int i=0; i<len_decoded; i++){
        int new_ch = 0; //закодированный символ (8 бит)
        for(int j=7; j>=0; j--){  //перевод бинарного символа в десятичную систему
           new_ch += bin_decoded_data[i*8 + (8 - j - 1)] * (1 << j); // [i*8 + (8 - j - 1)] n-ый элемент восьмёрки в бинарном массиве; (1 << j) ~ 2^j;
        }
        static_cast<char*>(buf)[i] = static_cast<char>(new_ch); //в тот же буфер записываем декодированное значение, но оно короче шифра, поэтому оставшийся мусор удаляем из буфера
    }

    delete [] bin_decoded_data;
    delete [] get_from_file;
    return len_decoded;
}



RleFile::RleFile(): BaseFile(){std::cout<<"Базовый конструктор, RleFile "<< this <<std::endl;}

RleFile::RleFile(const char* path, const char* mode): BaseFile(path, mode){std::cout<<"Конструктор, открывающий файл, RleFile "<< this <<std::endl;}

RleFile::RleFile(FILE* open_file): BaseFile(open_file){std::cout<<"Конструктор для открытого файла, RleFile "<< this <<std::endl;}

void RleFile::Create_bigger_array(char** Rle_text, int* len_array){ //увеличиваем массив с текстом Rle на 2
    char* vrem_Rle_text = new char[(*len_array)+2];
    for(int i=0; i<(*len_array); i++){
        vrem_Rle_text[i] = (*Rle_text)[i];
    }

    delete [] *Rle_text;
    *Rle_text = vrem_Rle_text;
    (*len_array)+=2;
}

size_t RleFile::write(const void *buf, size_t n_bytes){
    const char* char_buf = static_cast<const char*>(buf); //преобразуем из void в char
    int len_array=0, len_Rle_text=0;
    char* Rle_text = new char[len_array];
    
    for(int i=0; i < static_cast<int>(n_bytes); i++){
        char ch = char_buf[i];
        int count=1;
        while( (i+1 < static_cast<int>(n_bytes)) && (char_buf[i] == char_buf[i+1]) ){
            count++;
            i++;
        }
        Create_bigger_array(&Rle_text, &len_array); //добавляем +2 места для записи
        Rle_text[len_Rle_text] = ch;
        Rle_text[len_Rle_text+1] = static_cast<char>(count);
        len_Rle_text+=2;
    }

    size_t t = write_raw(Rle_text, len_Rle_text);
    delete [] Rle_text;
    return t;
}

size_t RleFile::read(void *buf, size_t max_bytes){
    char* read_text = new char[max_bytes]; //сюда считаем RLE
    size_t counter = 0;

    read_raw(read_text, max_bytes);
    for(int i=0; i < static_cast<int>(max_bytes); i+=2){
        for(int k=0; k < static_cast<int>(read_text[i+1]); k++){ //read_text[i+1] это кол-во символов вида read_text[i]
            static_cast<char*>(buf)[counter] = read_text[i];
            counter++;
        }
    }
    delete [] read_text;
    return counter;
}


void write_int(IFile& file, int n){
    int poz = 1;
    while(poz*10 < abs(n)){poz*=10;}
    char ch[1];
    if (n < 0) { file.write("-", 1); n = -n;}
    while (n > 0) {
        ch[0] = static_cast<char>('0' + n/poz );
        file.write(static_cast<const char*>(ch), 1);
        n%=poz;
        poz/=10;
    }
}