//
// Created by Okami on 2021/12/5.
//

#ifndef BOOKSTORE_FILE_H
#define BOOKSTORE_FILE_H

#include <fstream>

using std::fstream;
using std::string;

template<class T, int n = 2>
class File {
    char file_name[64];
    fstream file;
    static const int sizeof_T = sizeof(T);
    static const int sizeof_int = sizeof(int);

public:
    void Initialize() {
        file.open(file_name, std::ios::out);
        file.close();
    }

    File(char *_file_name) {
        strcpy(file_name, _file_name);
    }

    File(string &_file_name) {
        strcpy(file_name, _file_name.c_str());
    }

    bool IsExist() {
        file.open(file_name);
        bool status = file.good();
        file.close();
        return status;
    }

    void WriteInfo(int &value, int i) {
        int index = sizeof_int * i;
        file.open(file_name);
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&value), sizeof_int);
        file.close();
    }

    void ReadInfo(int &value, int i) {
        int index = sizeof_int * i;
        file.open(file_name);
        file.seekg(index);
        file.read(reinterpret_cast<char *>(&value), sizeof_int);
        file.close();
    }

    void Write(T &value, int i) {
        int index = sizeof_T * i + sizeof_int * n;
        file.open(file_name);
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&value), sizeof_T);
        file.close();
    }

    void Read(T &value, int i) {
        int index = sizeof_T * i + sizeof_int * n;
        file.open(file_name);
        file.seekg(index);
        file.read(reinterpret_cast<char *>(&value), sizeof_T);
        file.close();
    }
};

#endif //BOOKSTORE_FILE_H
