#include"my_string.hpp"

class TextWrapper{
    private:
        char * vvod;
        char **vivod;
        int total_i, vivod_i, len_message, line_width;

        void increase_vivod_by_1();
        void Short_last_line(int nomer_bukvi);
        int count_probels();
        void WRAP();

    public:
        TextWrapper(MyString input, int line_width=40);
        ~TextWrapper();
        
        void print_wrapped();
        
};
