
#include <iostream>
#include <cstring> // Для strlen

int main(){
    std::cout << "Задание 6" << std::endl;
    std::cout << "Введите текст, который вам повторит кошак: ";

    int total_i = 0, vivod_i = -1; // глобальный счётчик итераций + счётчик строк на вывод

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
                vivod[vivod_i][nomer_bukvi++] = ' ';
            }
            break;
        }

        int probel = 0;
        for(int i = 0; i < 40; i++){
            if (vvod_cat[total_i] == ' ') probel++;
            total_i++;
        }

        if((probel > 0) && (vvod_cat[total_i] != ' ') && (vvod_cat[total_i + 1] != ' ')){
            int local_probel = 0;
            for(int j = total_i - 40; j < total_i; j++){
                if (vvod_cat[j] == ' ') local_probel++;
                if (local_probel == probel) {
                    total_i = j + 1;
                    break;
                }
                vivod[vivod_i][nomer_bukvi++] = vvod_cat[j];
            }
            while(nomer_bukvi < 40){
                vivod[vivod_i][nomer_bukvi++] = ' ';
            }
        }
        
        else{
            for (int j = total_i - 40; j < total_i; j++) {
                vivod[vivod_i][nomer_bukvi++] = vvod_cat[j];
            }
        }
    }

    std::cout << " __________________________________________" << std::endl;
    for (int i = 0; i <= vivod_i; i++) {
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

    delete[] vvod_cat;
    for (int i = 0; i <= vivod_i; i++){
        delete[] vivod[i];
    }
    delete[] vivod;

    return 0;
}