//
// Created by Okami on 2021/12/9.
//

#ifndef BOOKSTORE_UTILS_H
#define BOOKSTORE_UTILS_H

#include <iostream>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::pair;

static bool CheckCommand(string &command) {
    if (command.size() > 512)
        return false;
    for (int i = 0; i < command.size(); ++i)
        if (!isascii(command[i]))
            return false;
    return true;
}

static void Split(string &command, vector<string> &res) {
    res.clear();
    bool is_string = false;
    string current;
    for (int i = 0; i < command.size(); ++i) {
        if (command[i] == '\"')
            is_string ^= 1;
        if (command[i] == ' ' && !is_string) {
            if (!current.empty()) {
                res.push_back(current);
                current.clear();
            }
            continue;
        }
        current.push_back(command[i]);
    }
    if (current.size())
        res.push_back(current);
}

static bool Divide(string &command, string &first, string &second) {
    int p = command.find('=');
    if (p == string::npos)
        return false;
    first = command.substr(0, p);
    second = command.substr(p + 1, command.size() - p - 1);
    return true;
}

static bool CheckKeyword(string keyword, vector<string> &list) {
    if (keyword.size() > 60 || keyword.empty())
        return false;
    for (int i = 0; i < keyword.size(); ++i)
        if (iscntrl(keyword[i]) || keyword[i] == '\"')
            return false;
    keyword += "|";
    int start = 0, end = keyword.find('|');
    while (end != string::npos) {
        if (start > end - 1)
            return false;
        string current = keyword.substr(start, end - start);
        list.push_back(current);
        start = end + 1;
        end = keyword.find('|', end + 1);
    }
    vector<string> temp = list;
    sort(temp.begin(), temp.end());
    for (int i = 0; i < list.size() - 1; ++i)
        if (temp[i] == temp[i + 1])
            return false;
    return true;
}

static bool CheckIsbn(string &isbn) {
    if (isbn.size() > 20 || isbn.empty())
        return false;
    for (int i = 0; i < isbn.size(); ++i)
        if (iscntrl(isbn[i]))
            return false;
    return true;
}

static bool CheckQuote(string &quote) {
    if (quote.size() > 60 || quote.empty())
        return false;
    for (int i = 0; i < quote.size(); ++i)
        if (iscntrl(quote[i]) || quote[i] == '\"')
            return false;
    return true;
}

static bool CheckQuantity(string &quantity) {
    if (quantity.size() > 10 || quantity.empty())
        return false;
    for (int i = 0; i < quantity.size(); ++i)
        if (!isdigit(quantity[i]))
            return false;
    long long temp = stoll(quantity);
    if (temp > 2147483647)
        return false;
    return true;
}

static bool CheckDot(string &dot) {
    if (dot.size() > 13 || dot.empty())
        return false;
    int sum = 0;
    for (int i = 0; i < dot.size(); ++i)
        if (!isdigit(dot[i]) && dot[i] != '.')
            return false;
        else if (dot[i] == '.')
            ++sum;
    if (sum >= 2)
        return false;
    if (!sum)
        return true;
    int p = dot.find('.');
    if (dot.size() - p - 1 > 2)
        dot = dot.substr(0, dot.size() - (dot.size() - p - 3));
    return true;
}

static bool CheckMixed(string &mixed) {
    if (mixed.size() > 30 || mixed.empty())
        return false;
    for (int i = 0; i < mixed.size(); ++i)
        if (!isdigit(mixed[i]) && !isalpha(mixed[i]) && mixed[i] != '_')
            return false;
    return true;
}

static bool CheckName(string &name) {
    if (name.size() > 30 || name.empty())
        return false;
    for (int i = 0; i < name.size(); ++i)
        if (iscntrl(name[i]))
            return false;
    return true;
}

static bool CheckNumber(string &number) {
    return (number == "1" || number == "3" || number == "7");
}

static bool CheckPair(string &first, string &second, vector<string> &keywords) {
    if (first != "-ISBN" && first != "-name" && first != "-author" && first != "-keyword" && first != "-price")
        return false;
    if (first == "-name" || first == "-author" || first == "-keyword") {
        if (second.front() != '\"' || second.back() != '\"')
            return false;
        second = second.substr(1, second.size() - 2);
    }
    if (first == "-ISBN" && !CheckIsbn(second))
        return false;
    if (first == "-name" && !CheckQuote(second))
        return false;
    if (first == "-author" && !CheckQuote(second))
        return false;
    if (first == "-keyword" && !CheckKeyword(second, keywords))
        return false;
    if (first == "-price" && !CheckDot(second))
        return false;
    return true;
}

#endif //BOOKSTORE_UTILS_H