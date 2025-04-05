#include <iostream>
#include <cstring> // Для strlen

int encoded32_size(int raw_size) {
    return (raw_size * 8 + 4) / 5; // Округление вверх для преобразования 8-битных блоков в 5-битные
}

int encode32(const char *raw_data, int raw_size, char *dst) {
    if (!raw_data || !dst || raw_size <= 0) {
        return 1;
    }

    int len_coded = encoded32_size(raw_size); // Длина закодированной строки (в символах)
    int len_to_code = len_coded * 5;         // Длина бинарной строки (в битах)
    int *bin_raw_data = new int[len_to_code](); // Двоичная строка с добавочными нулями

    int k = 0;
    // Переводим входные данные в двоичный массив
    for (int i = 0; i < raw_size; i++) {
        for (int j = 7; j >= 0; j--) {
            bin_raw_data[k++] = (static_cast<int>(raw_data[i]) >> j) & 1;
        }
    }

    // Заполняем оставшиеся биты нулями
    while (k < len_to_code) {
        bin_raw_data[k++] = 0;
    }

    char TABLE[32] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 
                      'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6'};

    // Кодируем данные
    for (int i = 0; i < len_coded; i++) {
        int new_ch = 0; // Закодированный символ (5 бит)
        for (int j = 4; j >= 0; j--) {
            int index = i * 5 + (4 - j);
            if (index < len_to_code) {
                new_ch += bin_raw_data[index] * (1 << j);
            }
        }
        dst[i] = TABLE[new_ch]; // Используем таблицу кодирования
    }

    delete[] bin_raw_data; // Освобождаем память
    return 0;
}




int main(){
        std::cout<<"Задание 7"<<std::endl;
        char ch; // Считываемый символ
        int raw_size = 0;
        char *raw_data = new char[raw_size];

        while(std::cin.get(ch) && ch != '\n'){
            char *vrem = new char[raw_size + 1];
            std::copy(raw_data, raw_data + raw_size, vrem);
            vrem[raw_size] = ch;
            raw_size++;
            delete[] raw_data;
            raw_data = vrem;
        }

        char dst[encoded32_size(raw_size)];
        bool rez = encode32(raw_data, raw_size, dst);
        std::cout<< "0 - закодировалось; 1 - нет. Результат: " << rez << std::endl;

        if(!rez){
            for(int i=0; i<encoded32_size(raw_size); i++){
                std::cout<< dst[i] << " ";
            }
        }
        



        delete [] raw_data;
        //delete [] dst;
    }
