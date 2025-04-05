struct Matrix{
    int rows;
    int columns;
    double** matr;
};

void m_print(Matrix *A); //не просили, но тупо удобно
void m_zero(Matrix *A, int m, int n);
void m_free(Matrix *A);
void m_id(Matrix *A, int n);
void m_copy(const Matrix *src, Matrix *dst);
int m_width(const Matrix *A);
int m_height(const Matrix *A);
double m_get(const Matrix* A, int i, int j);
void m_set(Matrix *A, int i, int j, double value);
int m_add(Matrix *A, const Matrix *B);
void m_neg(Matrix *A);
int m_mult(const Matrix *A, const Matrix *B, Matrix *dst);
void fibbonachi(long int* fib, int n);