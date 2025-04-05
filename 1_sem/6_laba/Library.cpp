#include <iostream>
#include "other_6.h"
#include <cmath> //для ceil
#include <cstring>
#include <cstdio> //для файлов
#include <cstdlib>// для atoi (char -> int)

void create_bigger_library(Book** library, int* len_library, int* free_places){ //увеличиваем массив
    int new_len_library;
    if((*len_library) == 0){
        new_len_library = 1;
        (*free_places) = 1;
    }
    else{
        new_len_library = static_cast<int>(ceil((*len_library)*1.5));
        (*free_places) = new_len_library - (*len_library);
    }

    Book* vrem_library = new Book[new_len_library];
    for(int i=0; i<(*len_library); i++){
        vrem_library[i] = (*library)[i];
    }

    delete [] (*library);
    *library = vrem_library;

    (*len_library) = new_len_library;
}

//перезаписываем в массив на единицу меньше + пропускаем "удаленное"
void create_smaller_library_and_delete(Book** library, int* len_library, int* free_places, int index_to_delete){
    int new_len_library  = (*len_library)-1;
    bool skip = false; //прошли ли значение которое удалили

    Book* vrem_library = new Book[new_len_library];

    int k=0;
    for (int i = 0; i < (*len_library); i++) {
        if(i == index_to_delete){
            continue; // пропускаем элемент с индексом index_to_delete
        }
        vrem_library[k++] = (*library)[i]; // Сдвигаем элементы
    }

    delete [] (*library);
    *library = vrem_library;

    (*len_library) = new_len_library;
}

void add_book(Book** library, int* len_library, int* free_places){
    if((*free_places) == 0){create_bigger_library(library, len_library, free_places);} //увеличиваем массив
    (*library)[(*len_library) - (*free_places)] = new_book(); //как раз получается индекс первого нового свободного эл-та
    (*free_places)--;
    SUCCESSFUL();
}

void delete_book(Book** library, int* len_library, int* free_places){
    char to_delete[150];
    get_name_of_book(to_delete, "удалить"); //считывание названия
    bool error = true;
    for(int i=0; i<(*len_library); i++){
        if (strcmp((*library)[i].name, to_delete) == 0){
            create_smaller_library_and_delete(library, len_library, free_places, i); //перезаписываем в массив на единицу меньше + пропускаем "удаленное"
            error = false;
            break; //если несколько дубликатов в картотеке, то удалится только первый
        }
    }
    if(error){name_error_message();} //не нашлось книги с таким названием для удаления
    else{SUCCESSFUL();}
}

void edit_book(Book** library, int* len_library){ //изменение книги
    char to_edit[150]; //имя книги
    int type_of_field; //изменяемое поле
    char text_of_type[50];  //в данном случае нужно только чтоб вызвать ф-цию, в edit не используется
    get_name_of_book(to_edit, "изменить"); //берем имя книги
    bool error = true;
    for(int i=0; i<(*len_library); i++){
        if (strcmp((*library)[i].name, to_edit) == 0){
            print_book(&(*library)[i]);
            type_of_field_print_sort_edit(library, len_library, &type_of_field, text_of_type, "редактирования"); //выбор поля
            set_new_value(library, len_library, i, &type_of_field); // изменение структуры
            error = false;
            break; //если несколько дубликатов в картотеке, то изменится только первая
        }
    }
    if(error){name_error_message();} //не нашлось книги с таким названием для удаления
    else{SUCCESSFUL();}
}

void find_short_long(Book** library, int* len_library, int* free_places){ //поиск самой длинной и короткой книги (доп)
    int kol_vo = (*len_library)-(*free_places); //число книг в картотеке
    
    switch(kol_vo){

    case 0:
        library_is_none(); //выведет: картотека пуста
        break;
    case 1:
        the_only_one(); //выведет: в картотеке только 1 эл-т
        print_book(&(*library)[0]); //выведет эту книгу

        printf("Для продолжения нажмите Enter.\n");
        while (getchar() != '\n'); //первый что-то еще дочищает в буфере
        while (getchar() != '\n');
        printf("\033c");
        break;
    default: //в картотеке больше 1 эл-та
        int SHORT = strlen((*library)[0].name), LONG = strlen((*library)[0].name); //длина названий книг
        int tmp_size;
        for(int i=0; i<kol_vo; i++){ //ищем макс и мин длину
            tmp_size = strlen((*library)[i].name);
            if(tmp_size < SHORT){SHORT = tmp_size;}
            if(tmp_size > LONG){LONG = tmp_size;}
        }

        print_short_long(library, len_library, free_places, &kol_vo, &SHORT, &LONG); //печатаем самые длинные и короткие
    }
    
}

bool is_txt(char* file_name){ //проверка на то, является ли строка txt-файлом
    int len = strlen(file_name);

    if(len < 5){return false;}
    for(int i=0; i<len; i++){
        //запрещённые в windows символы
        char ch = (file_name)[i];
        if(ch == '/' || ch == '\\' || ch == ':' || ch == '*' || ch == '?' || ch == '"' || ch == '<' || ch == '>' || ch == '|'){
            return false;}
    }

    return strcmp(file_name + len - 4, ".txt") == 0; //сравниваем последние 4 символа с ".txt"
}

void save_in_file(Book** library, int* len_library, int* free_places){
    char file_name[256]; //вроде как максимально допустимая для txt
    ask_file_name(file_name, "для записи");

    if(is_txt(file_name)){ //можно открыть/создать такой файл
        FILE* file = fopen(file_name, "w");
        int kol_vo = (*len_library)-(*free_places); //число книг в картотеке
        fprintf(file, "%d\n", kol_vo); //для начала запишем кол-во книг в картотеке 
        for(int i=0; i<kol_vo; i++){
            fprintf(file, "%s\n", (*library)[i].author);
            fprintf(file, "%s\n", (*library)[i].name);
            fprintf(file, "%s\n", (*library)[i].type);
            fprintf(file, "%s\n", (*library)[i].description);
            fprintf(file, "%s\n", (*library)[i].year);
        }
        fclose(file);
        SUCCESSFUL();
    }
    else{print_file_not_opened();} //файл не txt 
}

void read_from_file(Book** library, int* len_library, int* free_places){
    char file_name[256]; //вроде как максимально допустимая для txt
    ask_file_name(file_name, "для чтения");
    FILE* file = fopen(file_name, "r");
    if(file){ //файл смог открыться
        char ch[20];
        fgets(ch, 20, file);

        int new_len_library = atoi(ch); //число книг в файле
        delete[] (*library); //удаляем старый массив и создаем новый, который будет полностью забит новыми книгами
        *library = new Book[new_len_library];
        (*len_library) = new_len_library;
        (*free_places) = 0;

        for(int i=0; i<new_len_library; i++){
            fgets((*library)[i].author, 150, file);
            fgets((*library)[i].name, 150, file);
            fgets((*library)[i].type, 150, file);
            fgets((*library)[i].description, 150, file);
            fgets((*library)[i].year, 6, file);
        }
        delete_end_str(library, len_library, free_places); //из файла все поля читаются с \n, а нам нужно чтобы было \0
        fclose(file);
        SUCCESSFUL();
    }
    else{print_file_not_opened();} //файл не смог открыться 
}

void delete_end_str(Book** library, int* len_library, int* free_places){ //меняет \n -> \0 во всех полях книг массива книг
    for(int i=0; i<(*len_library)-(*free_places); i++){ //перебирает книги
        ((*library)[i].author) [strlen((*library)[i].author)-1] = '\0'; //в переводе на человеческий язык: (поле i-ой книги)[длина эл-та поля -1]
        ((*library)[i].name) [strlen((*library)[i].name)-1] = '\0';
        ((*library)[i].type) [strlen((*library)[i].type)-1] = '\0';
        ((*library)[i].description) [strlen((*library)[i].description)-1] = '\0';
        ((*library)[i].year) [strlen((*library)[i].year)-1] = '\0';
    }
}

void exit(bool* FLAG){
    (*FLAG) = false;
}