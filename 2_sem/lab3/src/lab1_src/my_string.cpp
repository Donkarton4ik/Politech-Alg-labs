#include"my_string.hpp"
#include<cstring>
#include<iostream>

MyString::MyString(){
    m_str = new char[1];
    strcpy(m_str, "");
}

MyString::MyString(const char * str){
    m_str = new char[strlen(str)+1];
    strcpy(m_str, str);
}

MyString::MyString(const MyString& other){
    m_str = new char[strlen(other.m_str) + 1];
    strcpy(m_str, other.m_str);
}

MyString::~MyString(){
    delete [] m_str;
}

char MyString::get(int i){
    return m_str[i-1];
}

void MyString::set(int i, char c){
    m_str[i-1] = c;
}

void MyString::set_new_string(const char *str){
    delete[] m_str;  
    m_str = new char[strlen(str) + 1];
    strcpy(m_str, str);
}

void MyString::print(){
    std::cout<<m_str<<std::endl;
}

void MyString::read_line() {
    char ch; // Считываемый символ
    int len_str = 0;
    char *read_str = new char[len_str]; //вводимая строка

    while(std::cin.get(ch) && ch != '\n'){
        char *vrem = new char[len_str + 2];
        for(int i=0; i<len_str; i++){vrem[i] = read_str[i];}
        vrem[len_str] = ch;
        len_str++;
        delete[] read_str;
        read_str = vrem;
    }

    read_str[len_str] = '\0';
    set_new_string(read_str);
    delete[] read_str;
}

const char* MyString::get_m_str(){
    return m_str;
}


void MyString::operator=(const MyString& other){ //Лаба 3 Задание 1.1
    if (this != &other){
        delete [] m_str;
        m_str = new char[strlen(other.m_str) + 1];
        strcpy(m_str, other.m_str);
    }
}