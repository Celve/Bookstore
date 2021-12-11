//
// Created by Okami on 2021/12/2.
//

#ifndef BOOKSTORE_USERS_H
#define BOOKSTORE_USERS_H

/*
 *  User system
 *      Operation:
 *          su:
 *              function: log in
 *              parameter: id, password(omitted with higher priority)
 *              status: failed(wrong password), successful
 *              required priority: 0
 *          logout:
 *              function: log out
 *              parameter: none
 *              status: failed(no active account), successful
 *              required priority: 1
 *          register:
 *              function: register an account(priority 1)
 *              parameter: id, password, name
 *              status: failed(id is same as existed account), successful
 *              required priority: 0
 *          passwd:
 *              function: reset password
 *              parameter: id, old password(omitted with priority 7), new password
 *              status: failed(no such account, wrong answer), successful
 *              required priority: 1
 *          useradd:
 *              function: just like register, but with priority
 *              parameter: id, password, priority, name
 *              status: failed(priority equaled or higher), successful
 *              required priority: 3
 *          delete:
 *              function: delete the account
 *              parameter: id
 *              status: failed(didn't exist, active)
 *              required priority: 7
 */

/*
 *  User
 *      Property:
 *          ID: letter, number and _; max length = 30
 *          Name: visible ascii; max length = 30
 *          Password: letter, number and _; max length = 30
 *          Priority: {7, 3, 1}
 */

#include <stack>
#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include "BPlusTree.h"
#include "File.h"
#include "Book.h"

using std::stack;
using std::string;
using std::unordered_map;
using std::pair;
using std::max;

class User {
    char id[31];
    char name[31];
    char password[31];
    int priority;

public:
    friend class UserSystem;

    User();

    User(char *_id, char *_name, char *_password, int priority);
};

class UserPair {
public:
    int book;
    int user;

    UserPair(int user = -1);

    void Select(int _book);
};

class UserSystem {
    vector<UserPair> users;
    unordered_map<int, int> online;
    File<User, 1> file;
    BPlusTree id_index;
    int n;

public:
    UserSystem();

    ~UserSystem();

    void Initialize();

    void Output();

    bool Su(string &ID, string &password);

    bool LogOut();

    bool Register(string &_id, string &_password, string &_name);

    bool Passwd(string &_id, string &_old_password, string &_new_password);

    bool UserAdd(string &_id, string &_password, string &_priority, string &_name);

    bool Delete(string &_id);

    bool Select(int book);

    int Book();

    bool CheckPriority(int priority);

    bool IsEmpty();
};

#endif //BOOKSTORE_USERS_H
