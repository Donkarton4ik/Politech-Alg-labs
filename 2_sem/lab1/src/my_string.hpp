class MyString{
    private:
        char* m_str;
    public:
        MyString();
        MyString(const char * str);
        MyString(const MyString& other);
        ~MyString();

        char get(int i);
        void set(int i, char c);
        void set_new_string(const char *str);
        void print();
        void read_line();

        const char* get_m_str(); //для 2.4 номера
};