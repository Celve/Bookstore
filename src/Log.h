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
 *          show finance:
 *              function:
 *                  show the last n trade total cost
 *              parameter: time
 *              status:
 *                  failed: time > maximum time
 *                  successful
 *          report finance:
 *              function: accountancy
 *          report employee:
 *              function: work log
 *          log:
 *              particular log
 */

#include "File.h"
#include "Book.h"

using std::setprecision;
using std::fixed;

class FinanceLog {
private:
    char command[21];
    Book book;
    int quantity;
    double money;
public:
    friend class LogSystem;

    FinanceLog();

    FinanceLog(string &_command, Book book, int quantity, double money);
};

class LogSystem {
    static const int NONE = 0x3f3f3f3f;
    int n;
    File<FinanceLog, 1> finance;

public:
    void Initialize();

    LogSystem();

    ~LogSystem();

    void AddFinanceLog(string &command, Book book, int quantity, double money);

    bool ShowFinanceLog(int time = NONE);
};

#endif //BOOKSTORE_LOG_H
