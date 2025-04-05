
//Прототипы используемых в данном задании функций:

void sort(char* pcFirst, int nNumber, int size,
     void (*Swap)(void*, void*), int (*Compare)(void*, void*) );
void swap_int(void* p1, void* p2);
int cmp_int(void* p1, void* p2);

void swap_double(void* p1, void* p2);
int cmp_double(void* p1, void* p2);

void swap_str(void* p1, void* p2);
int cmp_str(void* p1, void* p2);

//Задание 2.1
double add(double A21, double B21);
double sub(double A21, double B21);
double mul(double A21, double B21);
double div(double A21, double B21);

double cal(double(*func)(double A21, double B21), double A21, double B21);

//Задание 2.3
void print_max(int* mas, const int len);
void print_min(int* mas, const int len);
void sort_asc(int* mas, const int len);
void sort_desc(int* mas, const int len);

//Задание 2.4
double integrate(double(*func)(double), double floor, double ceiling, double dots);
double linear(double x);
double parabola(double x);

//Задание 3.1
struct Book {
    char author[50];
    char name[100]; //добавляется 2 байта до кратности 4
    int year;
    float price;
    char type[50]; //добавляется 2 байта до кратности 4, т к из-за int и float вся структура должна быть кратна 4
};

void print_book(const Book& book);
Book new_book();