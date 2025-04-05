#include "matrix.h"
#include <iostream>

void m_zero(Matrix *A, int m, int n){
    A->rows = m;
    A->columns = n;
    A->matr = new double* [m];
    for(int i=0; i<m; i++){
        (A->matr)[i] = new double [n]();
    }
}

void m_print(Matrix *A){ //не просили, но тупо удобно
    for(int i=0; i< A->rows; i++){
        for(int j=0; j< A->columns; j++){
            std::cout<<(A->matr)[i][j] << " ";
        }
        std::cout<< std::endl;
    }
}

void m_free(Matrix *A){
    for(int i=0; i< A->rows; i++){
        delete [] (A->matr)[i];
    }
    delete [] A->matr;
}

void m_id(Matrix *A, int n){
    A->rows = n;
    A->columns = n;
    A->matr = new double* [n];
    for(int i=0; i<n; i++){
        (A->matr)[i] = new double [n]();
    }

    for(int i=0; i< A->rows; i++){
        for(int j=0; j< A->columns; j++){
            if(i==j) {(A->matr)[i][j] = 1;}
        }
    }
}

void m_copy(const Matrix *src, Matrix *dst){
    if(src->rows == dst->rows && src->columns == dst->columns){
        for(int i=0; i< src->rows; i++){
            for(int j=0; j< src->columns; j++){
                (dst->matr)[i][j] = (src->matr)[i][j];
            }
        }
    }

    else{
        std::cout<<"Матрицы имеют разные размеры!" << std::endl;
        // NOTE: лучше вернуть ошибку через return
    }
}

int m_width(const Matrix *A){
    return A->columns;
}

int m_height(const Matrix *A){
    return A->rows;
}

void m_set(Matrix *A, int i, int j, double value){
    (A->matr)[i-1][j-1] = value;
}

double m_get(const Matrix* A, int i, int j){
    return (A->matr)[i-1][j-1];
}

int m_add(Matrix *A, const Matrix *B){
    if(A->rows == B->rows && A->columns == B->columns){
        for(int i=0; i< A->rows; i++){
            for(int j=0; j< A->columns; j++){
                (A->matr)[i][j] += (B->matr)[i][j];
            }
        }
        return 0;
    }

    else{return 1;}
}

void m_neg(Matrix *A){
    for(int i=0; i< A->rows; i++){
        for(int j=0; j< A->columns; j++){
            (A->matr)[i][j] = -(A->matr)[i][j];
        }
    }
}

int m_mult(const Matrix *A, const Matrix *B, Matrix *dst){
    if(A->columns == B->rows){
        // TODO: что если в dst неправильный размер?
        for(int i=0; i< A->rows; i++){
            for(int j=0; j< B->columns; j++){ //перебираем матрицу произведения
                
                for(int k=0; k< A->columns; k++){  //строка в А и столбец в B
                    (dst->matr)[i][j] += (A->matr)[i][k] * (B->matr)[k][j];
                }
            }
        }
        return 0;
    }

    else{return 1;}
}

/**
     * Задание 3.2.4.
     *
     * С помощью полученного функционала реализуйте матричное вычисление чисел
     * Фибоначчи. Делается это с помощью такой формулы:
     *
     * /  F[n]  \ = / 1  1 \ * / F[n-1] \
     * \ F[n-1] /   \ 1  0 /   \ F[n-2] /
     *
     * Задайте матрицу в центре и матрицу-вектор с двумя первыми числами
     * Фибоначчи: 1 и 0. Выполняйте эту формулу итеративно и выведите первые 40
     * чисел Фибоначчи.
     */
void fibbonachi(long int* fib, int n){
    switch (n){
    case 1:
        fib[0] = 0;
        break;
    case 2:
        fib[0] = 0;
        fib[1] = 1;
        break;
    
    default:
        fib[0] = 0;
        fib[1] = 1;
        Matrix A, B, C; //матрица слева, по центру, справа

        m_zero(&B, 2, 2);
        m_set(&B, 1, 1, 1);
        m_set(&B, 1, 2, 1);
        m_set(&B, 2, 1, 1);
        m_set(&B, 2, 2, 0);

        m_zero(&A, 2, 1);
        m_zero(&C, 2, 1);
        for(int i=2; i<n; i++){
            m_set(&C, 1, 1, fib[i-1]); //правая матрица
            m_set(&C, 2, 1, fib[i-2]);

            m_set(&A, 1, 1, 0); //ВАЖНО ОБНУЛЯТЬ ЛЕВУЮ МАТРИЦУ
            m_set(&A, 2, 1, 0);

            m_mult(&B, &C, &A); //левая матрица, равная произведению
            fib[i] = m_get(&A, 1, 1);
        }
        m_free(&A);
        m_free(&B);
        m_free(&C);
        break;
    }
}
