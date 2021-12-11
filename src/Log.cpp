//
// Created by Okami on 2021/12/11.
//

#include "Log.h"

FinanceLog::FinanceLog() {
    money = 0;
    quantity = 0;
}

FinanceLog::FinanceLog(string &_command, Book book, int quantity, double money): book(book), quantity(quantity), money(money) {
    strcpy(command, _command.c_str());
}

void LogSystem::Initialize() {
    finance.Initialize();
    finance.WriteInfo(n, 0);
}

LogSystem::LogSystem(): finance("Finance.dat") {
    if (!finance.IsExisted())
        Initialize();
    else
        finance.ReadInfo(n, 0);
}

void LogSystem::AddFinanceLog(string &command, Book book, int quantity, double money) {
    FinanceLog cur(command, book, quantity, money);
    finance.Write(cur, n++);
}

bool LogSystem::ShowFinanceLog(int time) {
    if (time == NONE)
        time = n;
    if (!time) {
        puts("");
        return true;
    }
    if (time > n || time < 0)
        return false;
    double revenue = 0, expenditure = 0;
    for (int i = n - time; i < n; ++i) {
        FinanceLog cur;
        finance.Read(cur, i);
        if (!strcmp(cur.command, "buy"))
            revenue += cur.money;
        else
            expenditure += cur.money;
    }
    cout << "+ " << revenue << " - " << expenditure << endl;
    return true;
}