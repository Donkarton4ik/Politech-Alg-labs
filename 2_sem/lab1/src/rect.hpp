class Rect{
    private:
        /*int left;
        int right;
        int top;
        int bottom;*/

        int x_point;
        int width;
        int y_point;
        int height;
    
    public:
        Rect(int l, int r, int t, int b);
        Rect();
        Rect(const Rect& other);
        ~Rect();

        /*int get_left() {return left;}
        int get_right() {return right;}
        int get_top() {return top;}
        int get_bottom() {return bottom;}*/
        int get_left() {return x_point;}
        int get_bottom() {return y_point;}
        int get_right() {return x_point + width;}
        int get_top() {return y_point + height;}
        void set_all(int l, int r, int t, int b);

        void inflate(int amount);
        void inflate(int dw, int dh);
        //void inflate(int d_left, int d_right, int d_top, int d_bottom);
        void inflate(int d_left, int d_right, int d_bottom, int d_top); //для удобста top и bottom <=> местами
        void move(int x, int y=0);

        int get_width();
        int get_height();
        int get_square();
        void set_height(int a);
        void set_width(int a);
};

void print_rect(Rect &r);
Rect bounding_rect(Rect r1, Rect r2);