#include"basefile.hpp"
#include<iostream>
#include <unistd.h> //для truncate()
#include <cstring> //для strcpy


bool Base32File2::can_read(){
    return ptr_file->can_read();
}

bool Base32File2::can_write(){
    return ptr_file->can_write();
}

void Base32File2::close(){
    ptr_file->close();
}

size_t Base32File2::write(const void *buf, size_t n_bytes){
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

    size_t t = ptr_file->write(to_write, len_coded);
    delete [] to_write;
    delete [] bin_raw_data;
    return t;
}

size_t Base32File2::read(void *buf, size_t max_bytes){
    char* get_from_file = new char[max_bytes]; //сюда считаем шифр из файла
    ptr_file->read(get_from_file, max_bytes);
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



bool RleFile2::can_read(){
    return ptr_file->can_read();
}

bool RleFile2::can_write(){
    return ptr_file->can_write();
}

void RleFile2::close(){
    ptr_file->close();
}

void RleFile2::Create_bigger_array(char** Rle_text, int* len_array){ //увеличиваем массив с текстом Rle на 2
    char* vrem_Rle_text = new char[(*len_array)+2];
    for(int i=0; i<(*len_array); i++){
        vrem_Rle_text[i] = (*Rle_text)[i];
    }

    delete [] *Rle_text;
    *Rle_text = vrem_Rle_text;
    (*len_array)+=2;
}

size_t RleFile2::write(const void *buf, size_t n_bytes){
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

    size_t t = ptr_file->write(Rle_text, len_Rle_text);
    delete [] Rle_text;
    return t;
}

size_t RleFile2::read(void *buf, size_t max_bytes){
    char* read_text = new char[max_bytes]; //сюда считаем RLE
    size_t counter = 0;

    ptr_file->read(read_text, max_bytes);
    for(int i=0; i < static_cast<int>(max_bytes); i+=2){
        for(int k=0; k < static_cast<int>(read_text[i+1]); k++){ //read_text[i+1] это кол-во символов вида read_text[i]
            static_cast<char*>(buf)[counter] = read_text[i];
            counter++;
        }
    }
    delete [] read_text;
    return counter;
}
