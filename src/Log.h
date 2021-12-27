//
// Created by Okami on 2021/12/3.
//

#ifndef BOOKSTORE_LOG_H
#define BOOKSTORE_LOG_H

/*
 *  log system:
 *      property:
 *          time
 *      operation:
 *          report myself
 *          show file:
 *              function:
 *                  show the last n trade total cost
 *              parameter: time
 *              status:
 *                  failed: time > maximum time
 *                  successful
 *          report file:
 *              function: accountancy
 *          report employee:
 *              function: work log
 *          log:
 *              particular log
 */

#include "File.h"
#include "Book.h"
#include "User.h"

using std::setprecision;
using std::fixed;
using std::vector;
using std::string;

class EmployeeLog {
private:
    int n;
    char id[31];
    char commands[21][61];
public:
    friend class EmployeeLogSystem;

    EmployeeLog();

    EmployeeLog(char *id_, vector<string> &commands);
};

class EmployeeLogSystem {
private:
    int n;
    File<EmployeeLog, 1> file;
    BPlusTree employee_index;

public:
    void Initialize();

    EmployeeLogSystem();

    ~EmployeeLogSystem();

    void AddEmployeeLog(char *id, vector<string> &commands);

    bool ReportEmployeeLog(char *id);

    bool ReportEmployeeLog();
};

class FinanceLog {
private:
    char command[21];
    Book book;
    int quantity;
    double money;
public:
    friend class FinanceLogSystem;

    FinanceLog();

    FinanceLog(string &command_, Book &book, int quantity, double money);
};

class FinanceLogSystem {
private:
    static const int kNone = 0x3f3f3f3f;
    int n;
    File<FinanceLog, 1> file;

public:
    void Initialize();

    FinanceLogSystem();

    ~FinanceLogSystem();

    void AddFinanceLog(string &command, Book book, int quantity, double money);

    bool ShowFinanceLog(int time = kNone);

    void ReportFinance();
};


#endif //BOOKSTORE_LOG_H
