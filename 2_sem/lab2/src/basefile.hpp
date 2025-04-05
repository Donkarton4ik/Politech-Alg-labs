#include <cstdio>
#include <iostream>
#include <cstring> //для strcpy

#pragma once //защита от двойного включения

class IFile{
    public:
        virtual ~IFile() = default;

        virtual bool can_read() = 0;// возвращает true, если из файла можно считать данные;
        virtual bool can_write() = 0;// возвращает true, если в файл можно записать данные;

        virtual size_t write(const void *buf, size_t n_bytes) = 0;
        virtual size_t read(void *buf, size_t max_bytes) = 0;
        virtual void close() = 0;
};


class BaseFile: public IFile{
    protected:
        FILE* file;
        bool to_close; //нужно ли закрывать файл в деструкторе

    public:
        BaseFile();
        BaseFile(const char* path, const char* mode);
        BaseFile(FILE* open_file);
        virtual ~BaseFile();

        void close(); //принудительное закрытие файла до деструктора

        bool is_open();// возвращает true, если файл успешно открыт;
        bool can_read();// возвращает true, если из файла можно считать данные;
        bool can_write();// возвращает true, если в файл можно записать данные;
        size_t write_raw(const void *buf, size_t n_bytes);//записывает указанное количество байт в файл и возвращает количество байт, которое удалось записать;
        size_t read_raw(void *buf, size_t max_bytes);//читает доступные данные в буфер, но не более указанного количества и возвращает количество байт, которое удалось считать;
        long tell();//возвращает текущий сдвиг файла
        bool seek(long offset);//устанавливает сдвиг файла и возвращает true, если операция успешна.

        virtual size_t write(const void *buf, size_t n_bytes);
        virtual size_t read(void *buf, size_t max_bytes);
};

class Base32File: public BaseFile{
    private:
        char TABLE[33];
    public:
        Base32File(const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
        Base32File(const char* path, const char* mode, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
        Base32File(FILE* open_file, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
        ~Base32File() override {std::cout<<"Деструктор, Base32File "<< this <<std::endl;};

        size_t write(const void *buf, size_t n_bytes) override;
        size_t read(void *buf, size_t max_bytes) override;
};

class RleFile: public BaseFile{
    private:
        void Create_bigger_array(char** Rle_text, int* len_array);

    public:
        RleFile();
        RleFile(const char* path, const char* mode);
        RleFile(FILE* open_file);
        ~RleFile() override {std::cout<<"Деструктор, RleFile "<< this <<std::endl;};

        size_t write(const void *buf, size_t n_bytes) override;
        size_t read(void *buf, size_t max_bytes) override;
};

void write_int(IFile& file, int n);


class Base32File2: public IFile{
    private:
        IFile* ptr_file;
        char TABLE[33];
    public:
        Base32File2(IFile* file, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456") : ptr_file(file){strncpy(TABLE, table, 32);};
        ~Base32File2() override {delete ptr_file;};

        size_t write(const void *buf, size_t n_bytes) override;
        size_t read(void *buf, size_t max_bytes) override;

        bool can_read() override;
        virtual bool can_write() override;
        void close() override;
};

class RleFile2: public IFile{
    private:
        IFile* ptr_file;
        void Create_bigger_array(char** Rle_text, int* len_array);

    public:
        RleFile2(IFile* file) : ptr_file(file){};
        ~RleFile2() override {delete ptr_file;};

        size_t write(const void *buf, size_t n_bytes) override;
        size_t read(void *buf, size_t max_bytes) override;

        bool can_read() override;
        bool can_write() override;
        void close() override;
};

/*class Enigma: public IFile{
    private:
        IFile* ptr_file;
        char TABLE[33];
        void Create_bigger_array(char** Rle_text, size_t* len_array, int plus);
        void Code32(char* str, size_t n_bytes, char*& coded, size_t* len_coded);
        void CodeRle(char* str, size_t n_bytes, char*& coded, size_t* len_coded);
        void Decode32(char*& str, size_t max_bytes, char*& decoded, size_t* len_decoded);
        void DecodeRle(char*& str, size_t max_bytes, char*& decoded, size_t* len_decoded);

    public:
        Enigma(IFile* file, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456") : ptr_file(file){strncpy(TABLE, table, 32);};
        ~Enigma() override {delete ptr_file;};

        size_t write(const void *buf, size_t n_bytes) override;
        size_t read(void *buf, size_t max_bytes) override;

        bool can_read() override;
        virtual bool can_write() override;
        void close() override;
};
*/