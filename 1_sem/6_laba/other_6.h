
struct Book {
    char author[150];         //автор
    char name[150];          //название
    char type[150];         //жанр
    char description[150]; //описание
    char year[6];         //год издания
};

//vvod / vivod
void menu(bool* FLAG, Book** library, int* len_library, int* free_places);
Book new_book();
void print_book(const Book* book);
void print_library(Book** library, int* len_library, int* free_places);
void library_is_none();
void the_only_one();
void print_short_long(Book** library, int* len_library, int* free_places, int* kol_vo, int* SHORT, int* LONG);
void get_name_of_book(char* name_of_book, const char* operation);
void type_of_field_print_sort_edit(Book** library, int* len_library, int* type_of_field, char* text_of_type, const char* text_of_operation);
void print_founded_in_library(Book** library, int* len_library);
void set_new_value(Book** library, int* len_library, int k, int* field);
void name_error_message();
bool question_sort();
void print_file_not_opened();
void ask_file_name(char* file_name, const char* text_of_operation);
void SUCCESSFUL();

//Library
void create_bigger_library(Book** library, int* len_library, int* free_places);
void add_book(Book** library, int* len_library, int* free_places);
void exit(bool* FLAG);
void delete_book(Book** library, int* len_library, int* free_places);
void create_smaller_library_and_delete(Book** library, int* len_library, int* free_places, int index_to_delete);
void edit_book(Book** library, int* len_library);
void find_short_long(Book** library, int* len_library, int* free_places);
void save_in_file(Book** library, int* len_library, int* free_places);
bool is_txt(char* file_name);
void read_from_file(Book** library, int* len_library, int* free_places);
void delete_end_str(Book** library, int* len_library, int* free_places);

//structures
char* get_field_value(Book* book, int field);

//sort
void SoRtInG(Book** library, int* len_library, int* free_places);
void vstavochka(Book** library, int* len_library, int* free_places, int* type_of_field);