#include "other.h"
#include <cassert>
#include <iostream>
#include <cstdarg>

//Задание 2.1
int inc_by_value(int a){
    a++;
    return a;
}

void inc_by_pointer(int* a){
    (*a)++;
}
void inc_by_reference(int& a){
    a++;
}

//Задание 2.2
void swap(int* a, int* b){
    int vr = *a;
    *a = *b;
    *b = vr;
}
void swap(int& a, int& b){
    int vr = a;
    a = b;
    b = vr;
}

//Задание 3.1
int min_odnomer(const int mas[], int len){
    assert (len>0);
    int min = mas[0];
    for(int i=0; i<len; i++){
        if(mas[i] < min){min = mas[i];}
    }
    return min;
}

int min_dvumer(int **mas, int m, int n){
    assert (m>0 && n>0);
    int min = mas[0][0];
    for(int i=0; i<m; i++){
        int min_str = min_odnomer(mas[i], n);
        if(min_str < min){min = min_str;}
    }
    return min;
}

int min_dvumer_VSTR(int* const mas, int m, int n){
    assert (m>0 && n>0);
    int min = *(&mas[0]); //указатель на 0 элемент 0 строки
    for(int i=0; i<m; i++){
        int min_str = min_odnomer(&mas[i * n], n); //указатель на элемент начала n-ой строки
        if(min_str < min){min = min_str;}
    }
    return min;
}

//Задание 3.2
/*int str_sravn(const char* a, const char* b){
    int i=0;
    while(a[i]!='\0'){
        if (a[i]-b[i] != 0){return a[i]-b[i];}
        i++;
    }
    // TODO: чтение за пределы `a`?
    while(b[i]!='\0'){
        if (a[i]-b[i] != 0){return a[i]-b[i];}
        i++;
    }
    return 0;
}*/

int str_sravn(const char* a, const char* b) {
    int i = 0;
    while(a[i] != '\0' || b[i] != '\0'){
        if(a[i] != b[i]){
            return a[i] - b[i];
        }
        i++;
    }
    return 0; //строки равны
}

//Задание 4
bool visokos(int year){ //если високосный, то return 1
    return ((year%400==0) || ((year%4==0)&&(year%100!=0)));
}

int DayOfYear(int* mas, int date, int month){
    int day = date;
    for(int i=0; i<month-1; i++){
        day+=mas[i];
    }
    return day;
}

void DayOfMonth(int *mas, int day, int* date){
    int i=0;
    while(day> mas[i]){
        day-=mas[i];
        i++;
    }
    date[0] = day;
    date[1] = i+1; //i+1 - месяц
}

//Задание 5
int* add_unique(int* arr, int &n, int new_value){
    bool flag = true;
    for(int i=0; i<n; i++){
        if(new_value == arr[i]){  //ищем дубликат
                flag=false;
                break;
            } 
    }

    if(flag){
        int* new_arr = new int[n+1];
        for(int i=0; i<n; i++){
            new_arr[i] = arr[i]; //копируем массив
        }
        
        new_arr[n] = new_value;
        n++;

        delete [] arr;
        arr = new_arr;
    }
    return arr;
}

void print_array(int* arr, int n){
    for(int i=0; i<n; i++){
        std::cout<< arr[i] << " ";
    }
    std::cout<< std::endl;
}

//Задание 6
int recurs_sum(int sum, int k, int n){
    sum+=k;
    k++;
    if(k<=n){sum = recurs_sum(sum, k, n);}
    return sum;
}

//Задание 7
int encoded32_size(int raw_size){
    return (raw_size * 8 + 5 - 1) / 5; //приписывание байтов ~ округлению вверх => A/B = A+B-1//B
}

int decoded32_size(int encode_size){
    return encode_size * 5 / 8;
}

int encode32(const char *raw_data, int raw_size, char *dst){
    if (!raw_data || !dst || raw_size <= 0){
        return 1;
    }

    int k=0;
    int len_coded = encoded32_size(raw_size);     //длина закодированной строки (по 5 бит)
    int len_to_code = len_coded*5;               //длина двоичной вводимой строки с учётом добавочных нулей
    int bin_raw_data[len_to_code];              //двоичная вводимая строка с учётом добавочных нулей
    for(int i=0; i<raw_size; i++){
        for(int j=7; j>=0; j--){
            bin_raw_data[k] = (static_cast<int>(raw_data[i]) >> j) & 1;
            k++;
        }
    }
    while(k<len_to_code){
        bin_raw_data[k] = 0;
        k++;
    }
    char TABLE[32] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6'};
    for(int i=0; i<len_coded; i++){
        int new_ch = 0; //закодированный символ (5 бит)
        for(int j=4; j>=0; j--){  //перевод бинарного символа в десятичную систему
           new_ch += bin_raw_data[i*5 + (5 - j - 1)] * (1 << j); // [i*5 + (5 - j - 1)] n-ый элемент пятёрки в бинарном массиве; (1 << j) ~ 2^j;
        }
        dst[i] = TABLE[new_ch];

    }
    return 0;
}

int decode32(const char *encoded_data, int encoded_size, char *dst){
    if (!encoded_data || !dst || encoded_size <= 0){
        return 1;
    }

    int k = 0;
    int code_of_5; //десятичное значение бинарной пятёрки
    char TABLE[32] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6'};
    int len_decoded = decoded32_size(encoded_size);     //длина декодированной строки (по 8 бит)
    int len_to_decode = len_decoded*8;                 //длина двоичной декодированной строки
    int bin_decoded_data[len_to_decode];              //двоичная декодированная строка
    
    for(int i=0; i<encoded_size; i++){
        bool error=true;
        for(int j=0; j<32; j++){
            if(TABLE[j] == encoded_data[i]){
                code_of_5=j;
                error = false;
                break;
            }
        }

        if(error){return 2;} //если символ не из таблицы
    
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
        dst[i] = static_cast<char>(new_ch);
    }
    return 0;
}

//Задание 8
void var_args(int nN1, ...){
    va_list args;
    va_start(args, nN1);
    int count = 2; //учитывая nN1 и 0
    std::cout<<"Аргументы: ";
    std::cout<< nN1 << " ";
    int k;
    while((k = va_arg(args, int)) != 0){
        std::cout<< k << " ";
        count++;
    }
    va_end(args);
    std::cout<< 0 << std::endl;
    std::cout<<"Всего аргументов: " << count << std::endl;
    std::cout<< std::endl;
}

//Задание 9
int *my_min(int* mas, int n){
    int *min_ptr = mas;
    for(int i=0; i<n; i++){
        if(mas[i] < *min_ptr){
            min_ptr = &(mas[i]);
        }
    }
    return min_ptr;
}
