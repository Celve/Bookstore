//
// Created by Okami on 2021/12/4.
//

#include "System.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

System bookstore;

int main() {
//    string temp = "1.2233";
//    CheckDot(temp);
//    cout << temp << endl;
//    freopen("test.out", "w", stdout);
    bookstore.Initialize();
    string command;
    while (getline(cin, command)) {
//        cout << command << endl;
        bookstore.Run(command);
//        cout << endl;
//        bookstore.Output();
//        cout << command << endl;
    }
}