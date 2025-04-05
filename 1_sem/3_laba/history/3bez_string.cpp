
#include <iostream>
#include <cstring> // Для strlen

int main() {
    std::cout << "Задание 6" << std::endl;
    std::cout << "Введите текст, который вам повторит кошак: ";
    
    char vvod_cat[100000];
    std::cin.ignore();  //без него какая-то дичь вводится (очищение буфера cin)
    std::cin.getline(vvod_cat, 100000); // Считываем строку в массив символов

    char vivod[1000][41] = {}; // Массив строк, каждая строка длиной до 40 символов + '\0'
    int len_message = strlen(vvod_cat);
    int total_i = 0, vivod_i = -1; //глабальный счетчик итераций + счетчик строк на вывод

    while (total_i < len_message) {
        if (total_i + 39 >= len_message) {  // Если оставшаяся часть строки короче 40 символов (вывод последней строки)
            vivod_i++;
            int nomer_bukvi = 0;
            for (int i = total_i; i < len_message; i++) {
                vivod[vivod_i][nomer_bukvi++] = vvod_cat[i];
            }
            while (nomer_bukvi < 40){vivod[vivod_i][nomer_bukvi++] = ' ';}
            break;
        }

        int probel = 0;
        for (int i = 0; i < 40; i++) {
            if (vvod_cat[total_i] == ' '){probel++;}
            total_i++;
        }

        if ((probel > 0) && (vvod_cat[total_i] != ' ') && (vvod_cat[total_i + 1] != ' ')) { //если 40-ым эл-том мы разрубаем слово
            int local_probel = 0;
            vivod_i++;
            int nomer_bukvi = 0;
            for (int j = total_i - 40; j < total_i; j++) {
                if (vvod_cat[j] == ' ') local_probel++;
                if (local_probel == probel) {
                    total_i = j + 1;
                    break;
                }
                vivod[vivod_i][nomer_bukvi++] = vvod_cat[j];
            }
            while (nomer_bukvi < 40){vivod[vivod_i][nomer_bukvi++] = ' ';}
        } 
        
        else {
            vivod_i++;
            int nomer_bukvi = 0;
            for (int j = total_i - 40; j < total_i; j++) {
                vivod[vivod_i][nomer_bukvi++] = vvod_cat[j];
            }
        }
    }

    std::cout << " _________________________________________" << std::endl;
    for (int i = 0; i <= vivod_i; i++) {
        std::cout << "| " << vivod[i] << " |" << std::endl;
    }
    std::cout << " ----------------------------------------" << std::endl;
    std::cout << "    \\             " << std::endl;
    std::cout << "     \\            " << std::endl;
    std::cout << "       /\\_/\\  (  " << std::endl;
    std::cout << "      ( ^.^ ) _)   " << std::endl;
    std::cout << "        \\\"/  (   " << std::endl;
    std::cout << "      ( | | )      " << std::endl;
    std::cout << "     (__d b__)     " << std::endl;

    return 0;
}