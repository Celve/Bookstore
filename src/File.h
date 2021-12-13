//
// Created by Okami on 2021/12/5.
//

#ifndef BOOKSTORE_FILE_H
#define BOOKSTORE_FILE_H

#include <fstream>
#include <cstring>

using std::fstream;
using std::string;

template<class T, int n = 2>
class File {
    char file_name[64];
    fstream file;
    static const int kSizeofT = sizeof(T);
    static const int kSizeofInt = sizeof(int);

public:
    void Initialize() {
        file.open(file_name, std::ios::out);
        file.close();
    }

    File(char *file_name_) {
        strcpy(file_name, file_name_);
    }

    File(string &file_name_) {
        strcpy(file_name, file_name_.c_str());
    }

    bool IsExisted() {
        file.open(file_name);
        bool status = file.good();
        file.close();
        return status;
    }

    void WriteInfo(int &value, int i) {
        int index = kSizeofInt * i;
        file.open(file_name);
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&value), kSizeofInt);
        file.close();
    }

    void ReadInfo(int &value, int i) {
        int index = kSizeofInt * i;
        file.open(file_name);
        file.seekg(index);
        file.read(reinterpret_cast<char *>(&value), kSizeofInt);
        file.close();
    }

    void Write(T &value, int i) {
        int index = kSizeofT * i + kSizeofInt * n;
        file.open(file_name);
        file.seekp(index);
        file.write(reinterpret_cast<char *>(&value), kSizeofT);
        file.close();
    }

    void Read(T &value, int i) {
        int index = kSizeofT * i + kSizeofInt * n;
        file.open(file_name);
        file.seekg(index);
        file.read(reinterpret_cast<char *>(&value), kSizeofT);
        file.close();
    }
};

#endif //BOOKSTORE_FILE_H
