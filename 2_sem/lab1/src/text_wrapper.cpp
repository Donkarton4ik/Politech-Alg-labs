#include"text_wrapper.hpp"
#include<iostream>
#include<cstring>

TextWrapper::TextWrapper(MyString input, int line_width){
    this->line_width = line_width;
    total_i = 0;  //глобальный счётчик итераций
    vivod_i = -1; //счётчик строк на вывод
    vivod = nullptr;

    vvod = new char[strlen(input.get_m_str()) + 1];
    strcpy(vvod, input.get_m_str());
    len_message = strlen(vvod);
}

TextWrapper::~TextWrapper(){
    delete [] vvod;
    for(int i = 0; i <= vivod_i; i++){
        delete[] vivod[i];
    }
    delete[] vivod;
}

void TextWrapper::increase_vivod_by_1(){ //увеличивает массив вывода на 1
    vivod_i++;
    char **vrem_vivod = new char*[vivod_i + 1];
    for(int i = 0; i < vivod_i; i++){
        vrem_vivod[i] = vivod[i];
    }
    vrem_vivod[vivod_i] = new char[line_width+1](); // инициализируем новую строку нулями
    delete[] vivod;
    vivod = vrem_vivod; 
}

void TextWrapper::Short_last_line(int nomer_bukvi){
    for(int i = total_i; i < len_message; i++){
        vivod[vivod_i][nomer_bukvi++] = vvod[i];
    }
    while(nomer_bukvi < line_width){
        vivod[vivod_i][nomer_bukvi++] = ' ';
    }
    
}

int TextWrapper::count_probels(){ //кол-во пробелов в строке
    int probel = 0;
    for(int i = 0; i < line_width; i++){
        if (vvod[total_i] == ' '){probel++;}
        total_i++;
    }
    return probel;
}

void TextWrapper::WRAP(){ //заполнение массива на вывод
    while(total_i < len_message){
        int nomer_bukvi = 0;
        increase_vivod_by_1();  //добавляем новую строку

        if(total_i + (line_width-1) >= len_message){  // если оставшаяся часть строки короче line_width символов
            Short_last_line(nomer_bukvi);
            break;
        }
    
        int probel = count_probels(); //кол-во пробелов в строке
        
        if((probel > 0) && (vvod[total_i] != ' ') && (total_i + 1 < len_message) && (vvod[total_i + 1] != ' ')){ 
            int local_probel = 0;
            for(int j = total_i - line_width; j < total_i; j++){
                if(vvod[j] == ' '){local_probel++;}
                if(local_probel == probel){
                    total_i = j + 1;
                    break;
                }
                vivod[vivod_i][nomer_bukvi++] = vvod[j];
            }
            while (nomer_bukvi < line_width){
                vivod[vivod_i][nomer_bukvi++] = ' ';
            }
        }

        else{
            for(int j = total_i - line_width; j < total_i; j++){
                vivod[vivod_i][nomer_bukvi++] = vvod[j];
            }
        }
    }
    
}

void TextWrapper::print_wrapped(){
    WRAP();
    for(int i = 0; i <= vivod_i; i++){
        std::cout << vivod[i] << std::endl;
    }
}
