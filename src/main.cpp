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
    string command;
    while (getline(cin, command))
        bookstore.Run(command);
}