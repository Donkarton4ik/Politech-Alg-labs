#include<cassert>
#include"../src/rect.hpp"

int main(){
    Rect rect1; //конструктор по умолчанию
    assert(rect1.get_left() == 0);
    assert(rect1.get_right() == 0);
    assert(rect1.get_top() == 0);
    assert(rect1.get_bottom() == 0);

    Rect rect2(1, 2, 3, 4); //конструктор с параметрами
    assert(rect2.get_left() == 1);
    //assert(rect2.get_right() == 2);
    assert(rect2.get_right() == 3);
    //assert(rect2.get_top() == 3);
    assert(rect2.get_top() == 7);
    //assert(rect2.get_bottom() == 4);
    assert(rect2.get_bottom() == 3);

    rect2.set_all(5, 6, 7, 8);
    assert(rect2.get_left() == 5);
    //assert(rect2.get_right() == 6);
    assert(rect2.get_right() == 11);
    //assert(rect2.get_top() == 7);
    assert(rect2.get_top() == 15);
    //assert(rect2.get_bottom() == 8);
    assert(rect2.get_bottom() == 7);
    
    return 0;
}