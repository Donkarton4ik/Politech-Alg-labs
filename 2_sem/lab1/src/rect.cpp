#include "rect.hpp"
#include <iostream>

Rect::Rect(int l, int r, int t, int b){
    set_all(l, r, t, b); //добавил после рефакторинга
    std::cout<<"Конструктор с параметрами, адрес объекта: "<< this <<std::endl;
}

Rect::Rect(){
    set_all(0, 0, 0, 0); //добавил после рефакторинга
    std::cout<<"Конструктор по умолчанию, адрес объекта: "<< this <<std::endl;
}

Rect::Rect(const Rect& other){
    /*left = other.left;
    right = other.right;
    top = other.top;
    bottom = other.bottom;*/
    x_point = other.x_point;
    width = other.width;
    y_point = other.y_point;
    height = other.height;
    std::cout<<"Конструктор копирования, адрес объекта: "<< this <<std::endl;
}

Rect::~Rect() {std::cout<< "Объект с адресом "<< this <<" уничтожен!" << std::endl;}

/*void Rect::set_all(int l, int r, int t, int b){
    left = l; 
    right = r; 
    top = t; 
    bottom = b; 
}*/
void Rect::set_all(int x, int wh, int y, int ht){
    x_point = x; 
    width = wh; 
    y_point = y; 
    height = ht; 
}

/*void Rect::inflate(int d_left, int d_right = 0, int d_top = 0, int d_bottom = 0){
    if(left <= right){
        left -= d_left;
        right += d_right;
    } 
    else{
        left += d_left;
        right -= d_right;
    }

    if(bottom <= top){
        bottom -= d_bottom;
        top += d_top;
    } 
    else{
        bottom += d_bottom;
        top -= d_top;
    }
}*/
void Rect::inflate(int d_left, int d_right, int d_bottom, int d_top){
    if(x_point <= x_point+width){
        x_point -= d_left;
        width += d_right+d_left;
    } 
    else{
        width -= d_left;
        x_point += d_right+d_left;
    }

    if(y_point <= y_point+height){
        y_point -= d_bottom;
        height += d_top+d_bottom;
    }
    else{
        height -= d_bottom;
        y_point += d_top+d_bottom;
    }
}


void Rect::inflate(int amount){ //после рефакторинга
    inflate(amount, amount, amount, amount);
}

void Rect::inflate(int dw, int dh){ //после рефакторинга
    inflate(dw, dw, dh, dh);
}

void Rect::move(int x, int y){
    /*left += x;
    right += x;
    top += y;
    bottom += y;*/
    x_point += x;
    y_point += y;
}

void print_rect(Rect &r){
    //std::cout << r.get_left() << " " << r.get_right() << " " << r.get_top() << " " << r.get_bottom() << '\n';
    std::cout << r.get_left() << " " << r.get_right() << " " << r.get_bottom() << " " << r.get_top() << '\n';
}

Rect bounding_rect(Rect r1, Rect r2){
    int left1 = (r1.get_left() <= r1.get_right()) ? r1.get_left() : r1.get_right();
    //int right1 = (r1.get_left() <= r1.get_right()) ? r1.get_right() : r1.get_left();
    int right1 = (r1.get_left() <= r1.get_right()) ? r1.get_right() : r1.get_left();
    //int top1 = (r1.get_top() >= r1.get_bottom()) ? r1.get_top() : r1.get_bottom();
    int top1 = (r1.get_top() >= r1.get_bottom()) ? r1.get_top() : r1.get_bottom();
    int bottom1 = (r1.get_top() >= r1.get_bottom()) ? r1.get_bottom() : r1.get_top();

    int left2 = (r2.get_left() <= r2.get_right()) ? r2.get_left() : r2.get_right();
    //int right2 = (r2.get_left() <= r2.get_right()) ? r2.get_right() : r2.get_left();
    int right2 = (r2.get_left() <= r2.get_right()) ? r2.get_right() : r2.get_left();
    //int top2 = (r2.get_top() >= r2.get_bottom()) ? r2.get_top() : r2.get_bottom();
    int top2 = (r2.get_top() >= r2.get_bottom()) ? r2.get_top() : r2.get_bottom();
    int bottom2 = (r2.get_top() >= r2.get_bottom()) ? r2.get_bottom() : r2.get_top();

    int left = (left1 <= left2) ? left1 : left2;
    //int right = (right1 >= right2) ? right1 : right2;
    int right = (right1 >= right2) ? right1 - left : right2 - left;
    //int top = (top1 >= top2) ? top1 : top2;
    int bottom = (bottom1 <= bottom2) ? bottom1 : bottom2;
    int top = (top1 >= top2) ? top1 - bottom : top2 - bottom;
    //Rect rect(left, right, top, bottom);
    Rect rect(left, right, bottom, top);
    return rect;
}

int Rect::get_width(){
    //return (left <= right) ? (right - left) : (left - right);
    return width;
}

int Rect::get_height(){
    //return (bottom <= top) ? (top - bottom) : (bottom - top);
    return height;
}

int Rect::get_square(){
    return (get_width() * get_height());
}

void Rect::set_height(int a){
    //(bottom <= this->top) ? (top = bottom + a) : (bottom = top + a);
    height = a;
}

void Rect::set_width(int a){
    //(left <= right) ? (right = left + a) : (left = right + a);
    width = a;
}