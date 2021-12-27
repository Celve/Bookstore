//
// Created by Okami on 2021/12/11.
//

#include "Log.h"

EmployeeLog::EmployeeLog() = default;

EmployeeLog::EmployeeLog(char *id_, vector<string> &commands_) {
    strcpy(id, id_);
    n = commands_.size();
    for (int i = 0; i < n; ++i)
        strcpy(commands[i], commands_[i].c_str());
}


void EmployeeLogSystem::Initialize() {
    file.Initialize();
    employee_index.Initialize();
    file.WriteInfo(n = 0, 0);
}

EmployeeLogSystem::EmployeeLogSystem(): file("EmployeeBasic.dat"), employee_index("EmployeeIndex.dat") {
    if (!file.IsExisted())
        Initialize();
    else
        file.ReadInfo(n, 0);
}

EmployeeLogSystem::~EmployeeLogSystem() {
    file.WriteInfo(n, 0);
}

void EmployeeLogSystem::AddEmployeeLog(char *id, vector<string> &commands) {
//    cout<< "Add: " << id << endl;
    EmployeeLog cur(id, commands);
    file.Write(cur, n);
    employee_index.Insert(id, n++);
}

bool EmployeeLogSystem::ReportEmployeeLog() {
    vector<int> res;
    employee_index.Traverse(res);
    if (res.empty()) {
        puts("");
        return false;
    }
    char temp[31];
    EmployeeLog cur;
    file.Read(cur, res[0]);
    cout << cur.id << ": \n";
    strcpy(temp, cur.id);
    for (int i = 0; i < res.size(); ++i) {
        file.Read(cur, res[i]);
        if (strcmp(cur.id, temp)) {
            cout << cur.id << ": \n";
            strcpy(temp, cur.id);
        }
        string output;
        for (int j = 0; j < cur.n; ++j)
            output += string(cur.commands[j]) + " ";
        cout << "\t" << output << endl;
    }
    return true;
}

bool EmployeeLogSystem::ReportEmployeeLog(char *id) {
    vector<int> res;
    employee_index.Find(id, res);
    cout << id << ": \n";
    if (res.empty()) {
        puts("");
        return false;
    }
    for (int i = 0; i < res.size(); ++i) {
        EmployeeLog cur;
        file.Read(cur, res[i]);
        string output;
        for (int j = 0; j < cur.n; ++j)
            output += string(cur.commands[j]) + " ";
        cout << "\t" << output << endl;
    }
    return true;
}

FinanceLog::FinanceLog() {
    money = 0;
    quantity = 0;
}

FinanceLog::FinanceLog(string &command_, Book &book, int quantity, double money): book(book), quantity(quantity), money(money) {
    strcpy(command, command_.c_str());
}

void FinanceLogSystem::Initialize() {
    file.Initialize();
    file.WriteInfo(n, 0);
}

FinanceLogSystem::FinanceLogSystem(): file("FinanceBasic.dat") {
    if (!file.IsExisted())
        Initialize();
    else
        file.ReadInfo(n, 0);
}

void FinanceLogSystem::AddFinanceLog(string &command, Book book, int quantity, double money) {
    FinanceLog cur(command, book, quantity, money);
    file.Write(cur, n++);
}

bool FinanceLogSystem::ShowFinanceLog(int time) {
    if (time == kNone)
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
        file.Read(cur, i);
        if (!strcmp(cur.command, "buy"))
            revenue += cur.money;
        else
            expenditure += cur.money;
    }
    cout << fixed << std::setprecision(2)<< "+ " << revenue << " - " << expenditure << endl;
    return true;
}

void FinanceLogSystem::ReportFinance() {
    for (int i = 0; i < n; ++i) {
        FinanceLog cur;
        file.Read(cur, i);
        cout << fixed << std::setprecision(2) << cur.command << "\t" << cur.quantity << "\t" << cur.money << endl;
    }
}

FinanceLogSystem::~FinanceLogSystem() {
    file.WriteInfo(n, 0);
}
