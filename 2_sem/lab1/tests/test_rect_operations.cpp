#include<cassert>
#include"../src/rect.hpp"
#include<iostream>

int main(){
    Rect r;
    r.set_all(1, 2, 4, 3);

    r.inflate(1);
    assert(r.get_left() == 0);
    //assert(r.get_right() == 3);
    assert(r.get_right() == 4);
    //assert(r.get_top() == 5);
    assert(r.get_top() == 8);
    //assert(r.get_bottom() == 2);
    assert(r.get_bottom() == 3);

    r.inflate(1, 2);
    assert(r.get_left() == -1);
    //assert(r.get_right() == 4);
    assert(r.get_right() == 5);
    //assert(r.get_top() == 7);
    assert(r.get_top() == 10);
    //assert(r.get_bottom() == 0);
    assert(r.get_bottom() == 1);

    r.inflate(0, 1, 0, 1);
    assert(r.get_left() == -1);
    //assert(r.get_right() == 5);
    assert(r.get_right() == 6);
    //assert(r.get_top() == 7);
    assert(r.get_top() == 11);
    //assert(r.get_bottom() == -1);
    assert(r.get_bottom() == 1);

    r.move(1);
    assert(r.get_left() == 0);
    //assert(r.get_right() == 6);
    assert(r.get_right() == 7);
    /*assert(r.get_top() == 7);
    assert(r.get_bottom() == -1);*/
    assert(r.get_top() == 11);
    assert(r.get_bottom() == 1);

    r.move(1, 2);
    assert(r.get_left() == 1);
    //assert(r.get_right() == 7);
    assert(r.get_right() == 8);
    //assert(r.get_top() == 9);
    assert(r.get_top() == 13);
    //assert(r.get_bottom() == 1);
    assert(r.get_bottom() == 3);

    return 0;
}