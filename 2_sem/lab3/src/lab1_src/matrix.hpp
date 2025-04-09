class Matrix{
    private:
        int m_rows;
        int m_columns;
        double** m_matr;
    public:
        Matrix(int n);
        Matrix(int m, int n, double fill_value = 0);
        Matrix(const Matrix& other);
        ~Matrix();

        double get(int i, int j);
        void set(int i, int j, double value);
        int get_height();
        int get_width();
        void negate();
        void add_in_place(Matrix &other);
        Matrix multiply(Matrix &other);

        void print_matr();

        void operator=(const Matrix& other); //Лаба 3 Задание 1.1
};