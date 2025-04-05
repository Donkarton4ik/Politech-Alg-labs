#include "3-4dop_other.h"
#include <iostream>

int main(){

    std::cout << "Введите текст, который вам повторит кошак: ";

    char ch; // Считываемый символ
    int len_message = 0;
    char *vvod_cat = new char[len_message]; //вводимая строка

    while(std::cin.get(ch) && ch != '\n'){
        char *vrem = new char[len_message + 1];
        std::copy(vvod_cat, vvod_cat + len_message, vrem);
        vrem[len_message] = ch;
        len_message++;
        delete[] vvod_cat;
        vvod_cat = vrem;
    }

    char* encode_vvod_cat = new char[len_message]; //закодированная введенная строка
    encode_cat(vvod_cat, encode_vvod_cat, len_message);
    //for(int i=0; i<len_message; i++){std::cout<<encode_vvod_cat[i];}
    char* decode_vvod_cat = new char[len_message]; //декодированная введенная строка
    decode_cat(encode_vvod_cat, decode_vvod_cat, len_message);

    char probel_char = ' '; //задаем отдельно пробел, потому что при кодировании некоторые символы меняются на пробелы, а логика стандартного кота заточена на ' '
    KOSHAK(vvod_cat, len_message, probel_char);            //обычный кошак
    KOSHAK(encode_vvod_cat, len_message, probel_char+3);  //закодированный кошак
    KOSHAK(decode_vvod_cat, len_message, probel_char); //декодированный кошак
    
    delete[] vvod_cat;
    delete[] encode_vvod_cat;
    delete[] decode_vvod_cat;

}