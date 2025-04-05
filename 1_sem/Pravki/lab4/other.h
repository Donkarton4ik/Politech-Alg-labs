//Задание 2.1
int inc_by_value(int a);
void inc_by_pointer(int* a);
void inc_by_reference(int& a);

//Задание 2.2
void swap(int* a, int* b);
void swap(int& a, int& b);

//Задание 3.1
int min_odnomer(const int mas[], int len);
int min_dvumer(int **mas, int m, int n);
int min_dvumer_VSTR(int* const mas, int m, int n);

//Задание 3.2
int str_sravn(const char* a, const char* b);

//Задание 4
bool visokos(int year);
int DayOfYear(int* mas, int date, int month);
void DayOfMonth(int* mas, int day, int* date);

//Задание 5
int* add_unique(int* arr, int &n, int new_value);
void print_array(int* arr, int n);

//Задание 6
int recurs_sum(int sum, int k, int n);

//Задание 7
int encoded32_size(int raw_size);
int decoded32_size(int encode_size);
int encode32(const char *raw_data, int raw_size, char *dst);
int decode32(const char *encoded_data, int encoded_size, char *dst);

//Задание 8
void var_args(int nN1, ...);

//Задание 9
int *my_min(int* mas, int n);