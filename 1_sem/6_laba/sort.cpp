#include <iostream>
#include "other_6.h"
#include <cstring>

void SoRtInG(Book** library, int* len_library, int* free_places){
    int type_of_field=0; //сортируемое поле
    char text_of_type[50]; //имя сортируемого поля
    if((*len_library)-(*free_places)==0){library_is_none();}
    else{
        type_of_field_print_sort_edit(library, len_library, &type_of_field, text_of_type, "сортировки");
        vstavochka(library, len_library, free_places, &type_of_field);
        SUCCESSFUL();
    }
}

void vstavochka(Book** library, int* len_library, int* free_places, int* type_of_field){
    if(question_sort()){ //по возрастанию
        for(int i=1; i<(*len_library)-(*free_places); i++){
            Book tmp = (*library)[i];
            int j=0;
            for(j=0; j<i; j++){
                if(strcmp( get_field_value(&(*library)[j],  *type_of_field), get_field_value(&tmp,  *type_of_field)) > 0){break;}
            }
            for(int k=i; k>j; k--){
                (*library)[k] = (*library)[k-1];
            }
            (*library)[j] = tmp;
        }
    }
    else{ //по убыванию
        for(int i=1; i<(*len_library)-(*free_places); i++){
            Book tmp = (*library)[i];
            int j=0;
            for(j=0; j<i; j++){
                if(strcmp( get_field_value(&(*library)[j],  *type_of_field), get_field_value(&tmp,  *type_of_field)) < 0){break;}
            }
            for(int k=i; k>j; k--){
                (*library)[k] = (*library)[k-1];
            }
            (*library)[j] = tmp;
        }
    }
}

