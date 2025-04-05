#include<cassert>
#include"../src/rect.hpp"

int main(){
    Rect rect(1, 2, 3, 5);

    //assert(rect.get_width() == 1);
    assert(rect.get_width() == 2);
    //assert(rect.get_height() == 2);
    assert(rect.get_height() == 5);
    //assert(rect.get_square() == 2);
    assert(rect.get_square() == 10);
    rect.set_width(4);
    rect.set_height(6);
    assert(rect.get_width() == 4);
    assert(rect.get_height() == 6);

    return 0;
}