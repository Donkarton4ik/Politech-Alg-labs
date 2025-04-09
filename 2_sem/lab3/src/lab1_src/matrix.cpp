#include"matrix.hpp"
#include<iostream>

Matrix::Matrix(int n){
    m_rows = n;
    m_columns = n;
    m_matr = new double* [n];
    for(int i=0; i<n; i++){
        (m_matr)[i] = new double [n]();
    }

    for(int i=0; i< m_rows; i++){
        for(int j=0; j< m_columns; j++){
            if(i==j) {(m_matr)[i][j] = 1;}
        }
    }
}

Matrix::Matrix(int m, int n, double fill_value){
    m_rows = m;
    m_columns = n;
    m_matr = new double* [m];
    for(int i=0; i<m; i++){
        m_matr[i] = new double [n]();
    }

    for(int i=0; i< m_rows; i++){
        for(int j=0; j< m_columns; j++){
            m_matr[i][j] = fill_value;
        }
    }
}

Matrix::Matrix(const Matrix& other){
    m_rows = other.m_rows;
    m_columns = other.m_columns;
    m_matr = new double*[m_rows];
    for(int i=0; i<m_rows; i++){
        m_matr[i] = new double [m_columns]();
        for(int j=0; j<m_columns; j++){
            m_matr[i][j] = other.m_matr[i][j];
        }
    }
}

Matrix::~Matrix(){
    for(int i=0; i<m_rows; i++){delete [] m_matr[i];}
    delete [] m_matr;
}


double Matrix::get(int i, int j){
    if (i<=0 || j<=0 || i>m_rows || j>m_columns){
        throw "Ошибка индекса!";
    }
    return m_matr[i-1][j-1];
}

void Matrix::set(int i, int j, double value){
    if (i<=0 || j<=0 || i>m_rows || j>m_columns){
        throw "Ошибка индекса!";
    }
    m_matr[i-1][j-1] = value;
}

int Matrix::get_height(){
    return m_rows;
}

int Matrix::get_width(){
    return m_columns;
}

void Matrix::negate(){
    for(int i=0; i<m_rows; i++){
        for(int j=0; j<m_columns; j++){
            m_matr[i][j] = -m_matr[i][j];
        }
    }
}

void Matrix::add_in_place(Matrix &other){
    if (m_rows!=other.m_rows || m_columns!=other.m_columns){
        throw "Нельзя складывать матрицы разного размера!";
    }

    for(int i=0; i<m_rows; i++){
        for(int j=0; j<m_columns; j++){
            m_matr[i][j] += other.m_matr[i][j];
        }
    }
}

Matrix Matrix::multiply(Matrix &other){
    if (m_columns!=other.m_rows){
        throw "На эту матрицу умножать нельзя!";
    }
    
    Matrix product(m_rows, other.m_columns, 0);

    for(int i=0; i < m_rows; i++){
        for(int j=0; j < other.m_columns; j++){
            for(int k=0; k < m_columns; k++){
                (product.m_matr)[i][j] += (m_matr)[i][k] * (other.m_matr)[k][j];
            }
        }
    }

    return product;
}

void Matrix::print_matr(){
    for(int i=0; i<m_rows; i++){
        for(int j=0; j<m_columns; j++){
            std::cout<< m_matr[i][j] << " ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

Matrix& Matrix::operator=(const Matrix& other){ //Лаба 3 Задание 1.1
    if(this != &other){
        for(int i=0; i<m_rows; i++){delete [] m_matr[i];}
        delete [] m_matr;

        m_rows = other.m_rows;
        m_columns = other.m_columns;
        m_matr = new double*[m_rows];
        for(int i=0; i<m_rows; i++){
            m_matr[i] = new double [m_columns]();
            for(int j=0; j<m_columns; j++){
                m_matr[i][j] = other.m_matr[i][j];
            }
        }
    }
    return *this;
}