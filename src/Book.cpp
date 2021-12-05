//
// Created by Okami on 2021/12/5.
//

#include "Book.h"

Book::Book() = default;

Book::Book(string _ISBN) {
    strcpy(ISBN, _ISBN.c_str());
}

bool Book::ModifyISBN(string _ISBN) {
    if (_ISBN.empty())
        return false;
    strcpy(ISBN, _ISBN.c_str()); // TODO: whether input same ISBN is failed?
    return true;
}

bool Book::ModifyName(string _name) {
    if (_name.empty())
        return false;
    strcpy(name, _name.c_str());
    return true;
}

bool Book::ModifyAuthor(string _author) {
    if (_author.empty())
        return false;
    strcpy(author, _author.c_str());
    return true;
}

bool Book::ModifyKeyword(string _keyword) {
    if (_keyword.empty())
        return false;
    _keyword += "|";
    int start = 0, end = _keyword.find('|');
    vector<string> list;
    while (end != _keyword.npos) {
        string current = _keyword.substr(start, end - start + 1);
        list.push_back(current);
    }
    sort(list.begin(), list.end());
    for (int i = 0; i < list.size() - 1; ++i)
        if (list[i] == list[i + 1])
            return false;
    n = list.size();
    for (int i = 0; i < n; ++i)
        strcpy(keyword[i], list[i].c_str());
    return true;
}

bool Book::ModifyPrice(string _price) {
    if (_price.empty())
        return false;
    price = stod(_price);
    return true;
}

void BookSystem::Initialize() {

}

BookSystem::BookSystem(string file_name): file(file_name) {
    if (!file.IsExist())
        Initialize();
    else {
        n = 0;
        file.WriteInfo(n, 0);
    }
}

BookSystem::~BookSystem() {
    file.WriteInfo(n, 0);
}