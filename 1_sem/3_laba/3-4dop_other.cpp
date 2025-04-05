#include "3-4dop_other.h"
#include <iostream>

char* encode_cat(char* vvod_cat, char* encode_vvod_cat, int len_message){
    for(int i=0; i<len_message; i++){
        encode_vvod_cat[i] = vvod_cat[i] + 3;
    }
    return encode_vvod_cat;
}

char* decode_cat(char* encode_vvod_cat, char* decode_vvod_cat, int len_message){
    for(int i=0; i<len_message; i++){
        decode_vvod_cat[i] = encode_vvod_cat[i] - 3;
    }
    return decode_vvod_cat;
}


void KOSHAK(char* vvod_cat, int len_message, char probel_char){
    int total_i = 0, vivod_i = -1; // глобальный счётчик итераций + счётчик строк на вывод
    char **vivod = new char*[vivod_i+1]; // массив строк на вывод

    while(total_i < len_message){     //ЗАПОЛНЕНИЕ ВЫВОДА
        vivod_i++;
        char **vrem_vivod = new char*[vivod_i + 1];
        for(int i = 0; i < vivod_i; i++){
            vrem_vivod[i] = vivod[i];
        }
        vrem_vivod[vivod_i] = new char[41](); // инициализируем новую строку нулями
        delete[] vivod;
        vivod = vrem_vivod;

        int nomer_bukvi = 0;
        if(total_i + 39 >= len_message){  // если оставшаяся часть строки короче 40 символов
            for(int i = total_i; i < len_message; i++){
                vivod[vivod_i][nomer_bukvi++] = vvod_cat[i];
            }
            while(nomer_bukvi < 40){
                vivod[vivod_i][nomer_bukvi++] = ' '; //специально оставил как было
            }
            break;
        }

        int probel = 0;
        for(int i = 0; i < 40; i++){
            if(vvod_cat[total_i] == probel_char){probel++;}
            total_i++;
        }

        if((probel > 0) && (vvod_cat[total_i] != probel_char) && (vvod_cat[total_i + 1] != probel_char)){
            int local_probel = 0;
            for(int j = total_i - 40; j < total_i; j++){
                if(vvod_cat[j] == probel_char){local_probel++;}
                if(local_probel == probel){
                    total_i = j + 1;
                    break;
                }
                vivod[vivod_i][nomer_bukvi++] = vvod_cat[j];
            }
            while(nomer_bukvi < 40){
                vivod[vivod_i][nomer_bukvi++] = probel_char;
            }
        }
        
        else{
            for(int j = total_i - 40; j < total_i; j++){
                vivod[vivod_i][nomer_bukvi++] = vvod_cat[j];
            }
        }
    }

    std::cout<< std::endl;
    std::cout << " __________________________________________" << std::endl;
    for(int i = 0; i <= vivod_i; i++){
        std::cout << "| " << vivod[i] << " |" << std::endl;
    }
    std::cout << " ------------------------------------------" << std::endl;
    std::cout << "    \\             " << std::endl;
    std::cout << "     \\            " << std::endl;
    std::cout << "       /\\_/\\  (  " << std::endl;
    std::cout << "      ( ^.^ ) _)   " << std::endl;
    std::cout << "        \\\"/  (   " << std::endl;
    std::cout << "      ( | | )      " << std::endl;
    std::cout << "     (__d b__)     " << std::endl;
    std::cout<< std::endl;
    
    for(int i = 0; i <= vivod_i; i++){
        delete[] vivod[i];
    }
    delete[] vivod;
}