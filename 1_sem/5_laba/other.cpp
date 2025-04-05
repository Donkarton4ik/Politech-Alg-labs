#include "other.h"
#include <iostream>
#include <cmath>
#include <cstring>

//Задание 2.2
void sort(char* pcFirst, int nNumber, int size, void (*Swap)(void*, void*), int (*Compare)(void*, void*) )
{
    int i;
    for(i=1; i<nNumber; i++)
        for(int j=nNumber-1; j>=i; j--)
        {
            char* pCurrent = pcFirst+j*size;
            char* pPrevious = pcFirst+(j-1)*size;
            if((*Compare)( pPrevious, pCurrent ) > 0)//требуется
                                                //переставить
                (*Swap)( pPrevious, pCurrent );
        }
}

void swap_int(void* p1, void* p2)
{
    int vrem = *(reinterpret_cast<int*>(p1));
    *(reinterpret_cast<int*>(p1)) = *(reinterpret_cast<int*>(p2));
    *(reinterpret_cast<int*>(p2)) = vrem;
}

int cmp_int(void* p1, void* p2)
{
    int nResult = (*(reinterpret_cast<int*>(p1))) - (*(reinterpret_cast<int*>(p2)));
    return nResult;
}

void swap_double(void* p1, void* p2)
{
    double vrem = *(reinterpret_cast<double*>(p1));
    *(reinterpret_cast<double*>(p1)) = *(reinterpret_cast<double*>(p2));
    *(reinterpret_cast<double*>(p2)) = vrem;
}

int cmp_double(void* p1, void* p2)
{
    double nResult = (*(reinterpret_cast<double*>(p1))) - (*(reinterpret_cast<double*>(p2)));
    if(nResult==0){return 0;}
    else if(nResult>0){return 1;}
    return -1;
}

void swap_str(void* p1, void* p2)
{
    char* vrem = *(char**)p1;
    *(char**)p1 = *(char**)p2;
    *(char**)p2 = vrem;
}

int cmp_str(void* p1, void* p2)
{
    return strcmp(*(char**)p1, *(char**)p2); 
}

//Задание 2.1
double add(double A21, double B21){return A21+B21;}
double sub(double A21, double B21){return A21-B21;}
double mul(double A21, double B21){return A21*B21;}
double div(double A21, double B21){return A21/B21;}

double cal(double(*func)(double A21, double B21), double A21, double B21){
    return func(A21, B21);
}

//Задание 2.3
void print_max(int* mas, const int len){
    int max = mas[0];
    for(int i=0; i<len; i++){
        if(mas[i]>max){max = mas[i];}
    }
    std::cout<<"Максимальный элемент массива: " << max << std::endl;
}

void print_min(int* mas, const int len){
    int min = mas[0];
    for(int i=0; i<len; i++){
        if(mas[i]<min){min = mas[i];}
    }
    std::cout<<"Максимальный элемент массива: " << min << std::endl;
}

void sort_asc(int* mas, const int len){
    for(int i=0; i < len-1; i++){
        bool flag = false;
        for(int k=0; k < len-i-1; k++){
            if(mas[k] > mas[k+1]){
                int vrem = mas[k];
                mas[k] = mas[k+1];
                mas[k+1] = vrem;
                flag = true;
            }
        }
        if (flag==false){break;}
    }
    std::cout<< "Отсортированный массив: ";
    for(int i=0; i<len; i++){std::cout<<mas[i] << " ";}
    std::cout<< std::endl;
}

void sort_desc(int* mas, const int len){
    for(int i=0; i < len-1; i++){
        bool flag = false;
        for(int k=0; k < len-i-1; k++){
            if(mas[k] < mas[k+1]){
                int vrem = mas[k];
                mas[k] = mas[k+1];
                mas[k+1] = vrem;
                flag = true;
            }
        }
        if (flag==false){break;}
    }
    std::cout<< "Отсортированный массив: ";
    for(int i=0; i<len; i++){std::cout<<mas[i] << " ";}
    std::cout<< std::endl;
}

//Задание 2.4
double integrate(double(*func)(double), double floor, double ceiling, double dots){
    double sum=0, len=(ceiling-floor)/dots;
    for(double i=floor; i<ceiling; i+=len){
        sum+= func(i) * len;
    }
    return sum;
}

double linear(double x){return x;}
double parabola(double x){return x*x;}

//Задание 3.1
void print_book(const Book& book){ //const эффективно (избегает копирования)
    printf("Автор: %s\n", book.author);
    printf("Название: %s\n", book.name);
    printf("Год издания: %d\n", book.year);
    printf("Цена(руб): %.2f\n", book.price);
    printf("Категория: %s\n", book.type);
}

Book new_book(){
    Book book;

    while (getchar() != '\n');
    printf("Введите автора книги: ");
    while(true){
        if (!(scanf("%49[^\n]", book.author))) {
            printf("Ошибка ввода!\n");
            printf("Введите автора книги: ");
            while (getchar() != '\n');
        }
        else{break;}
    }

    while (getchar() != '\n');
    printf("Введите название книги: ");
    while(true){
        if (!(scanf("%99[^\n]", book.name))) {
            printf("Ошибка ввода!\n");
            printf("Введите название книги: ");
            while (getchar() != '\n');
        }
        else{break;}
    }

    while (getchar() != '\n');
    printf("Введите год издания книги: ");
    while(true){
        if ( !(scanf("%d", &book.year) && -4000 < book.year && book.year < 2026)) {
            printf("Ошибка ввода!\n");
            printf("Введите год издания книги: ");
            while (getchar() != '\n');
        }
        else{break;}
    }

    while (getchar() != '\n');
    printf("Введите цену(в рублях) книги: ");
    while(true){
        if ( !(scanf("%f", &book.price) && book.price >= 0)) {
            printf("Ошибка ввода!\n");
            printf("Введите цену(в рублях) книги: ");
            while (getchar() != '\n');
        }
        else{break;}
    }

    while (getchar() != '\n');
    printf("Введите категорию книги: ");
    while(true){
        if (!(scanf("%49[^\n]", book.type))) {
            printf("Ошибка ввода!\n");
            printf("Введите категорию книги: ");
            while (getchar() != '\n');
        }
        else{break;}
    }

    return book;
}