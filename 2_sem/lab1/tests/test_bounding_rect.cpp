#include<cassert>
#include"../src/rect.hpp"

int main(){
    /*Rect r1(1, 5, 8, 0), r2(-4, 1, 7, -1); //все параметры верно стоят
    Rect r3(1, -4, -1, 7); //перепутаны лево-право и верх-низ
    Rect r4 = bounding_rect(r1, r2), r5 = bounding_rect(r1, r3); */
    Rect r1(1, 5, 0, 8), r2(-4, 1, -1, 7); //все параметры верно стоят
    Rect r3(1, -4, 7, -1); //перепутаны лево-право и верх-низ
    Rect r4 = bounding_rect(r1, r2), r5 = bounding_rect(r1, r3);

    assert(r4.get_left() == -4);
    //assert(r4.get_right() == 5);
    assert(r4.get_right() == 6);
    assert(r4.get_top() == 8);
    assert(r4.get_bottom() == -1);

    //assert(r5.get_left() == -4);
    assert(r5.get_left() == -3);
    //assert(r5.get_right() == 5);
    assert(r5.get_right() == 6);
    assert(r5.get_top() == 8);
    //assert(r5.get_bottom() == -1);
    assert(r5.get_bottom() == 0);

    return 0;
}