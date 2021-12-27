//
// Created by Okami on 2021/12/9.
//

#ifndef BOOKSTORE_BOOKSTORE_H
#define BOOKSTORE_BOOKSTORE_H

#include <iostream>
#include <vector>
#include "Utils.h"
#include "User.h"
#include "Book.h"
#include "Log.h"
#include "Exception.h"

using std::string;
using std::vector;
using std::fixed;
using std::setprecision;

class Bookstore {
private:
    BookSystem book_system;
    UserSystem user_system;
    FinanceLogSystem finance_log_system;
    EmployeeLogSystem employee_log_system;

    bool AddLog(vector<string> &list);
public:
    Bookstore();

    void Output();

    void Initialize();

    void Run(string &command);

    void Quit(vector<string> &list);

    void Su(vector<string> &list);

    void Logout(vector<string> &list);

    void Register(vector<string> &list);

    void Passwd(vector<string> &list);

    void UserAdd(vector<string> &list);

    void Delete(vector<string> &list);

    void Modify(vector<string> &list);

    void Buy(vector<string> &list);

    void Select(vector<string> &list);

    void Show(vector<string> &list);

    void Import(vector<string> &list);

    void Report(vector<string> &list);

    void Log(vector<string> &list);

    void ShowFinance(vector<string> &list);
};


#endif //BOOKSTORE_BOOKSTORE_H
