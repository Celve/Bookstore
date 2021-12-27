//
// Created by Okami on 2021/12/4.
//

#include "Bookstore.h"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

Bookstore bookstore;

int main() {
    string command;
    while (getline(cin, command))
        bookstore.Run(command);
}