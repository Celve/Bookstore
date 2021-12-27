//
// Created by Okami on 2021/12/9.
//

#include "Bookstore.h"

Bookstore::Bookstore() = default;

void Bookstore::Output() {
    user_system.Output();
    book_system.Output();
}

void Bookstore::Initialize() {
    book_system.Initialize();
    user_system.Initialize();
    finance_log_system.Initialize();
    employee_log_system.Initialize();
}

void Bookstore::Run(string &command) {
    try {
        if (!CheckCommand(command))
            throw Exception();
        vector<string> split;
        Split(command, split);
        if (split.empty())
            return ;
        if (split.size() >= 2 && split[0] == "show" && split[1] == "finance")
            ShowFinance(split);
        else if (split[0] == "quit" || split[0] == "exit")
            Quit(split);
        else if (split[0] == "su")
            Su(split);
        else if (split[0] == "logout")
            Logout(split);
        else if (split[0] == "register")
            Register(split);
        else if (split[0] == "passwd")
            Passwd(split);
        else if (split[0] == "useradd")
            UserAdd(split);
        else if (split[0] == "delete")
            Delete(split);
        else if (split[0] == "modify")
            Modify(split);
        else if (split[0] == "buy")
            Buy(split);
        else if (split[0] == "select")
            Select(split);
        else if (split[0] == "show")
            Show(split);
        else if (split[0] == "import")
            Import(split);
        else if (split[0] == "report")
            Report(split);
        else if (split[0] == "log")
            Log(split);
        else
            throw Exception();
    }
    catch (Exception) {
        puts("Invalid");
    }
}

void Bookstore::Quit(vector<string> &list) {
    if (list.size() != 1)
        throw Exception();
    while (user_system.LogOut());
    exit(0);
}

void Bookstore::Su(vector<string> &list) {
    if (list.size() > 3 || list.size() == 1)
        throw Exception();
    string temp;
    if (list.size() == 2 && (!CheckMixed(list[1]) || !user_system.Su(list[1], temp)))
        throw Exception();
    if (list.size() == 3 && (!CheckMixed(list[1]) || !CheckMixed(list[2]) || !user_system.Su(list[1], list[2])))
        throw Exception();
    book_system.DeSelect();
}

void Bookstore::Logout(vector<string> &list) {
    if (list.size() > 1 || !user_system.LogOut())
        throw Exception();
    book_system.Select(user_system.Book());
}

void Bookstore::Register(vector<string> &list) {
    if (list.size() != 4 || !CheckMixed(list[1]) || !CheckMixed(list[2]) || !CheckName(list[3]))
        throw Exception();
    if (!user_system.Register(list[1], list[2], list[3]))
        throw Exception();
}

void Bookstore::Passwd(vector<string> &list) {
    if (list.size() > 4 || list.size() < 3)
        throw Exception();
    string temp;
    if (list.size() == 3 && (!CheckMixed(list[1]) || !CheckMixed(list[2]) || !user_system.Passwd(list[1], temp, list[2])))
        throw Exception();
    if (list.size() == 4 && (!CheckMixed(list[1]) || !CheckMixed(list[2]) || !CheckMixed(list[3]) || !user_system.Passwd(list[1], list[2], list[3])))
        throw Exception();
}

void Bookstore::UserAdd(vector<string> &list) {
    if (list.size() != 5)
        throw Exception();
    if (!CheckMixed(list[1]) || !CheckMixed(list[2]) || !CheckNumber(list[3]) || !CheckName(list[4]))
        throw Exception();
    if (!user_system.UserAdd(list[1], list[2], list[3], list[4]))
        throw Exception();
}

void Bookstore::Delete(vector<string> &list) {
    if (list.size() != 2)
        throw Exception();
    if (!CheckMixed(list[1]) || !user_system.Delete(list[1]))
        throw Exception();
}

void Bookstore::Modify(vector<string> &list) {
    if (list.size() == 1 || !user_system.CheckPriority(3))
        throw Exception();
    vector<pair<string, string>> factor;
    vector<string> keywords;
    for (int i = 1; i < list.size(); ++i) {
        string first, second;
        if (!Divide(list[i], first, second))
            throw Exception();
        if (!CheckPair(first, second, keywords))
            throw Exception();
        factor.emplace_back(first, second);
    }
    sort(factor.begin(), factor.end());
    for (int i = 1; i < factor.size(); ++i)
        if (factor[i].first == factor[i - 1].first)
            throw Exception();
    string isbn, name, author, price;
    for (int i = 0; i < factor.size(); ++i)
        if (factor[i].first == "-ISBN")
            isbn = factor[i].second;
        else if (factor[i].first == "-name")
            name = factor[i].second;
        else if (factor[i].first == "-author")
            author = factor[i].second;
        else if (factor[i].first == "-price")
            price = factor[i].second;
    if (!book_system.Modify(isbn, name, author, keywords, price))
        throw Exception();
    AddLog(list);
}

void Bookstore::Buy(vector<string> &list) {
    if (list.size() != 3 || !user_system.CheckPriority(1))
        throw Exception();
    if (!CheckIsbn(list[1]) || !CheckQuantity(list[2]))
        throw Exception();
    Book book;
    if (!book_system.Buy(list[1], list[2], book))
        throw Exception();
    finance_log_system.AddFinanceLog(list[0], book, stoi(list[2]), stoi(list[2]) * book.price);
    cout << fixed << setprecision(2) << stoi(list[2]) * book.price << endl;
}

void Bookstore::Select(vector<string> &list) {
    if (list.size() != 2 || !user_system.CheckPriority(3))
        throw Exception();
    if (!CheckIsbn(list[1]))
        throw Exception();
    if (user_system.IsEmpty())
        throw Exception();
    book_system.Select(list[1]);
    user_system.Select(book_system.GetAddress());
    AddLog(list);
}

void Bookstore::Show(vector<string> &list) {
    if (list.size() > 2 || !user_system.CheckPriority(1))
        throw Exception();
    vector<Book> res;
    if (list.size() == 1)
        book_system.ShowAll(res);
    else {
        string first, second;
        vector<string> keywords;
        if (!Divide(list[1], first, second))
            throw Exception();
        if (first == "-price" || !CheckPair(first, second, keywords) || keywords.size() > 1)
            throw Exception();
        if (first == "-ISBN" && !book_system.ShowIsbn(second, res))
            throw Exception();
        if (first == "-name" && !book_system.ShowName(second, res))
            throw Exception();
        if (first == "-author" && !book_system.ShowAuthor(second, res))
            throw Exception();
        if (first == "-keyword" && !book_system.ShowKeyword(second, res))
            throw Exception();
    }
    for (int i = 0; i < res.size(); ++i)
        cout << res[i] << endl;
    if (res.empty())
        cout << endl;
    AddLog(list);
}

void Bookstore::Import(vector<string> &list) {
    if (list.size() != 3 || !user_system.CheckPriority(3))
        throw Exception();
    if (!CheckQuantity(list[1]) || !CheckDot(list[2]))
        throw Exception();
    if (!book_system.Import(list[1], list[2]))
        throw Exception();
    Book book = book_system.SelectedBook();
    finance_log_system.AddFinanceLog(list[0], book, stoi(list[1]), stod(list[2]));
    AddLog(list);
}

void Bookstore::ShowFinance(vector<string> &list) {
    if (list.size() > 3 || !user_system.CheckPriority(7))
        throw Exception();
    if (list.size() == 2 && !finance_log_system.ShowFinanceLog())
        throw Exception();
    if (list.size() == 3 && (!CheckQuantity(list[2]) || !finance_log_system.ShowFinanceLog(stoi(list[2]))))
        throw Exception();
}

void Bookstore::Report(vector<string> &list) {
    if (list.size() != 2)
        throw Exception();
    if (list[1] == "finance") {
        if (!user_system.CheckPriority(7))
            throw Exception();
        finance_log_system.ReportFinance();
    }
    else if (list[1] == "employee") {
        if (!user_system.CheckPriority(7))
            throw Exception();
        employee_log_system.ReportEmployeeLog();
    }
    else if (list[1] == "myself") {
        User user;
        if (!user_system.Top(user) || user.GetPriority() != 3)
            throw Exception();
        employee_log_system.ReportEmployeeLog(user.GetId());
    }
    else
        throw Exception();
}

void Bookstore::Log(vector<string> &list) {
    throw Exception();
}

bool Bookstore::AddLog(vector<string> &list) {
    User cur;
    if (!user_system.Top(cur))
        return false;
    if (cur.GetPriority() == 3) {
        employee_log_system.AddEmployeeLog(cur.GetId(), list);
        return true;
    }
    return false;
}