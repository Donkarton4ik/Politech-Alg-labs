#include <iostream>
#include "other_6.h"

char* get_field_value(Book* book, int field){ //возвращает значение у конкретного поля конкретной книги
    switch (field) {
        case 1:
            return book->author;
        case 2:
            return book->name;
        case 3:
            return book->type;
        case 4:
            return book->description;
        case 5:
            return book->year;
        default:
            return NULL;
    }
}
