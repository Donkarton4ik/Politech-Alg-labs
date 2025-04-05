#include <iostream>
#include "other_6.h"
//#include "structures.h"
#include <cstring>

void menu(bool* FLAG, Book** library, int* len_library, int* free_places){
    printf("Выберите операцию:\n");
    printf("1. Распечатать содержимое картотеки\n");
    printf("2. Добавить новую книгу\n");
    printf("3. Удалить книгу по названию\n");
    printf("4. Изменить информацию о книге (например, изменить описание)\n");
    printf("5. Поиск книг по названию/автору/жанру/описанию/году издания\n");
    printf("6. Сортировка картотеки\n");
    printf("7. Сохранить текущее содержимое картотеки в файл\n");
    printf("8. Загрузить содержимое картотеки из файла\n");
    printf("9. Найти книги с самым длинным и самым коротким названием\n");
    printf("10. Выйти из программы\n\n");
    int operation;
    scanf("%d", &operation);

    switch (operation){

    case 1:
        printf("\033c"); // TODO: что это такое?
        print_library(library, len_library, free_places);
        break;
    case 2:
        printf("\033c");
        add_book(library, len_library, free_places);
        break;
    case 3:
        printf("\033c");
        delete_book(library, len_library, free_places);
        break;
    case 4:
        printf("\033c");
        edit_book(library, len_library);
        break;
    case 5:
        printf("\033c");
        print_founded_in_library(library, len_library);
        break;
    case 6:
        printf("\033c");
        SoRtInG(library, len_library, free_places);
        break;
    case 7:
        printf("\033c");
        save_in_file(library, len_library, free_places);
        break;
    case 8:
        printf("\033c");
        read_from_file(library, len_library, free_places);
        break;
    case 9:
        printf("\033c");
        find_short_long(library, len_library, free_places);
        break;
    case 10:
        printf("\033c");
        exit(FLAG);
        break;
    default:
        printf("\033c");
        printf("Ошибка ввода, попробуйте ещё раз!\n\n");
        while (getchar() != '\n');
        break;
    }
}

Book new_book(){
    Book book;
    int Year;
    const char* text_field[4] = {"автора", "название", "категорию", "краткое описание"};
    
    for(int i=0; i<4; i++){
        printf("Введите %s книги: ", text_field[i]);
        while(true){
            while(getchar() != '\n');
            if(!(scanf("%149[^\n]", get_field_value(&book, i+1)))){
                printf("Ошибка ввода!\n");
                printf("Введите %s книги: ", text_field[i]);
            }
            else{break;}
        }
    }

    printf("Введите год издания книги: "); //у года уже другое условие + нужно конвертировать
    while(true){
        while(getchar() != '\n');
        if( !(scanf("%d", &Year) && -4000 < Year && Year < 2026)){
            printf("Ошибка ввода!\n");
            printf("Введите год издания книги: ");
        }
        else{
            sprintf(book.year, "%d", Year); //конвертация Int -> char*
            break;
        }
    }

    printf("\n");
    return book;
}

void print_book(const Book* book){ //с const т к только читаем
    printf("Автор: %s\n", book->author);
    printf("Название: %s\n", book->name);
    printf("Категория: %s\n", book->type);
    printf("Краткое описание книги: %s\n", book->description);
    printf("Год издания: %s\n\n", book->year);
}

void print_library(Book** library, int* len_library, int* free_places){
    printf("Картотека:\n");
    if( (*len_library)-(*free_places) > 0 ){
        for(int i=0; i<(*len_library)-(*free_places); i++){ // до пустых ячеек не доходит
            print_book(&(*library)[i]);
        }
        printf("Для продолжения нажмите Enter.\n");
        while (getchar() != '\n'); //первый что-то еще дочищает в буфере
        while (getchar() != '\n');
        printf("\033c");
    }

    else{library_is_none();}
}

void library_is_none(){
    printf("\033c");
    printf("Картотека пуста!\n\n");
    printf("Для продолжения нажмите Enter.\n");
    while (getchar() != '\n'); //первый что-то еще дочищает в буфере
    while (getchar() != '\n');
    printf("\033c");
}

void the_only_one(){
    printf("В картотеке лишь 1 книга!\n\n");
}

void print_short_long(Book** library, int* len_library, int* free_places, int* kol_vo, int* SHORT, int* LONG){ //выводит самые длинные и короткие названия
    if((*SHORT) == (*LONG)){
        printf("Все книги в картотеке одинаковой длины!\n\n");
        print_library(library, len_library, free_places);
    }
    
    else{
        printf("Книги с самым коротким названием:\n\n");
        for(int i=0; i < *kol_vo; i++){
            if(strlen((*library)[i].name) == *SHORT){
                print_book(&(*library)[i]);
            }
        }

        printf("Книги с самым длинным названием:\n\n");
        for(int i=0; i < *kol_vo; i++){
            if(strlen((*library)[i].name) == *LONG){
                print_book(&(*library)[i]);
            }
        }
    printf("Для продолжения нажмите Enter.\n");
    while (getchar() != '\n'); //первый что-то еще дочищает в буфере
    while (getchar() != '\n');
    printf("\033c");
    }
}

//выбор поля для принта по критерии / редактирования / сортировки по критерию
void type_of_field_print_sort_edit(Book** library, int* len_library, int* type_of_field, char* text_of_type, const char* text_of_operation){
    printf("Выберите критерий для %s:\n", text_of_operation);
    printf("1. Название книги\n");
    printf("2. Автор книги\n");
    printf("3. Жанр книги\n");
    printf("4. Описание книги\n");
    printf("5. Год издания\n\n");
    bool flag = true;

    while(flag){
        while (getchar() != '\n');
        scanf("%d", type_of_field);
        switch (*type_of_field){
            case 0: //для сортировки default почему-то не работает, а вот 0 работает
                printf("Ошибка ввода, попробуйте ещё раз!\n\n");
                break;
            case 1:
                *type_of_field = 1;
                strcpy(text_of_type,  "названию");
                flag = false;
                break;
            case 2:
                *type_of_field = 2;
                strcpy(text_of_type,  "автору");
                flag = false;
                break;
            case 3:
                *type_of_field = 3;
                strcpy(text_of_type,  "жанру");
                flag = false;
                break;
            case 4:
                *type_of_field = 4;
                strcpy(text_of_type,  "описанию");
                flag = false;
                break;
            case 5:
                *type_of_field = 5;
                strcpy(text_of_type,  "году издания");
                flag = false;
                break;
            default:
                printf("Ошибка ввода, попробуйте ещё раз!\n\n");
                break;
        }
    }
}

void print_founded_in_library(Book** library, int* len_library){ //принтит все книги по критерию
    char to_find [150]; //критерий текстовый (Пушкин, например)
    bool not_found = true;
    int type_of_field; //выводимое поле
    char text_of_type[50]; //название выводимого поля
    int Year;//критерий-год
    char strYear[6]; //он же но строкой

    type_of_field_print_sort_edit(library, len_library, &type_of_field, text_of_type, "печати");

    if(type_of_field==5){ //если требуется принтить именно по году
        printf("Поиск по году издания книги: ");
        while(true){
            while (getchar() != '\n');
            if ( !(scanf("%d", &Year) && -4000 < Year && Year < 2026)) {
                printf("Ошибка ввода!\n");
                printf("Введите год издания книги: ");
            }
            else{break;}
        }
        for(int i=0; i<(*len_library); i++){
            sprintf(strYear, "%d", Year);
            if (strcmp( (*library)[i].year, strYear) == 0){
                print_book(&(*library)[i]);
                not_found = false;
            }
        }
    }

    else{
        printf("Поиск по %s книги: ", text_of_type); //считывание того, что будем искать
        while(true){
            while (getchar() != '\n');
            if (!(scanf("%149[^\n]", to_find))){
                printf("Ошибка ввода!\n");
                printf("Поиск по %s книги: ", text_of_type);
            }
            else{break;}
        }

        for(int i=0; i<(*len_library); i++){
            if (strcmp( get_field_value(&(*library)[i], type_of_field), to_find) == 0){
                print_book(&(*library)[i]);
                not_found = false;
            }
        }
    }
    if(not_found){printf("Таких книг не найдено!\n\n");}
    printf("Для продолжения нажмите Enter.\n");
    while (getchar() != '\n'); //первый что-то еще дочищает в буфере
    while (getchar() != '\n');
    printf("\033c");
}

void get_name_of_book(char* name_of_book, const char* operation){ //используется для удаления и изменения информации о книге
    printf("Введите название книги, которую хотите %s: ", operation);
    while (getchar() != '\n');
    scanf("%149[^\n]", name_of_book);
}

void name_error_message(){ //используется для удаления и изменения информации о книге
    printf("Книга с таким названием не найдена!\n\n");
    printf("Для продолжения нажмите Enter.\n");
    while (getchar() != '\n'); //первый что-то еще дочищает в буфере
    while (getchar() != '\n');
    printf("\033c");
}

void set_new_value(Book** library, int* len_library, int k, int* field){ //изменяет соответствующее поле структуры
    char new_value[150];
    int Year;
    char strYear[6]; //он же но строкой

    if((*field)==5){ //если требуется изменить именно год
        printf("Введите год издания книги: ");
        while(true){
            while (getchar() != '\n');
            if ( !(scanf("%d", &Year) && -4000 < Year && Year < 2026)) {
                printf("Ошибка ввода!\n");
                printf("Введите год издания книги: ");
            }
            else{
                sprintf(strYear, "%d", Year);
                strcpy( (*library)[k].year, strYear); //изменение
                break;
            }
        }
    }

    else{ //для любого поля, кроме года
        while(true){
            printf("Введите новое значение: ");
            while (getchar() != '\n');
            if (!(scanf("%149[^\n]", new_value))) {
                printf("Ошибка ввода!\n");
            }
            else{break;}
        }

        strcpy(get_field_value(&(*library)[k], *field),  new_value); //изменение
    }
}

bool question_sort(){ //вопрос о сортировке по возрастанию/по убыванию
    int type;
    printf("\033c");
    printf("Выберите тип сортировки:\n");
    printf("1. По возрастанию\n");
    printf("2. По убыванию\n\n");
    while(true){
        while(getchar() != '\n');
        if(!(scanf("%d", &type) && (type==1 || type==2) )){
            printf("Ошибка ввода!\n");
            printf("Выберите тип сортировки:\n");
        }
        else{break;}
    }
    printf("\033c");
    if(type==1){return 1;}
    return 0;
}

void ask_file_name(char* file_name, const char* text_of_operation){
    while(true){
        printf("Введите название файла %s (с расширением .txt): ", text_of_operation);
        while (getchar() != '\n');
        if (!(scanf("%255[^\n]", file_name))) {
            printf("Ошибка ввода!\n");
        }
        else{break;}
    }
    printf("\033c");
}

void print_file_not_opened(){
    printf("Ошибка при работе с файлом! Попробуйте еще раз!\n\n");
    printf("Для продолжения нажмите Enter.\n");
    while (getchar() != '\n'); //первый что-то еще дочищает в буфере
    while (getchar() != '\n');
    printf("\033c");
}

void SUCCESSFUL() {
    printf("\033c");
    printf("Успешно! Для продолжения нажмите Enter.\n");
    while (getchar() != '\n'); //первый что-то еще дочищает в буфере
    while (getchar() != '\n');
    printf("\033c");
}
