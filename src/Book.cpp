//
// Created by Okami on 2021/12/5.
//

#include "Book.h"

Book::Book() = default;

Book::Book(string isbn_) {
    strcpy(isbn, isbn_.c_str());
    quantity = n = 0;
    total_cost = price = 0;
    name[0] = author[0] = '\0';
    for (int i = 0; i <= 60; ++i)
        keyword[i][0] = '\0';
}

bool Book::IsExisted() {
    return strlen(isbn);
}

std::ostream &operator << (std::ostream &os, const Book &book) {
    os << book.isbn << "\t" << book.name << "\t" << book.author << "\t";
    os << book.keyword[0];
    for (int i = 1; i < book.n; ++i)
        os << "|" << book.keyword[i];
    os << std::fixed << std::setprecision(2) << "\t" << book.price << "\t" << book.quantity;
    return os;
}

bool Book::operator < (const Book &rhs) const {
    int n = strlen(isbn), m = strlen(rhs.isbn);
    for (int i = 0; i < min(n, m); ++i)
        if (isbn[i] != rhs.isbn[i])
            return isbn[i] < rhs.isbn[i];
    return n < m;
}

void BookSystem::Initialize() {
    file.Initialize();
    isbn_index.Initialize();
    name_index.Initialize();
    author_index.Initialize();
    keyword_index.Initialize();
    file.WriteInfo(n = 0, 0);
}

BookSystem::BookSystem(): file("BookBasic.dat"), isbn_index("BookIsbn.bin"), name_index("BookName.bin"), author_index("BookAuthor.bin"), keyword_index("BookKeyword.bin") {
    address = -1;
    if (!file.IsExisted())
        Initialize();
    else
        file.ReadInfo(n, 0);
}

void BookSystem::Output() {
    puts("---begin---");
    for (int i = 0; i < n; ++i) {
        Book current;
        file.Read(current, i);
        cout << current << endl;
    }
    puts("---end---");
}

bool BookSystem::ShowCommon(string &_key, BPlusTree &common_index, vector<Book> &res) {
    char key[61];
    strcpy(key, _key.c_str());
    vector<int> index;
    common_index.Find(key, index);
    for (int i = 0; i < index.size(); ++i) {
        Book current;
        file.Read(current, index[i]);
        res.push_back(current);
    }
    sort(res.begin(), res.end());
    return true;
}

void BookSystem::ShowAll(vector<Book> &res) {
    vector<int> index;
    isbn_index.Traverse(index);
    for (int i = 0; i < index.size(); ++i) {
        Book book;
        file.Read(book, index[i]);
        res.push_back(book);
    }
}

bool BookSystem::ShowIsbn(string &isbn, vector<Book> &res) {
    return ShowCommon(isbn, isbn_index, res);
}

bool BookSystem::ShowName(string &name, vector<Book> &res) {
    return ShowCommon(name, name_index, res);
}

bool BookSystem::ShowAuthor(string &author, vector<Book> &res) {
    return ShowCommon(author, author_index, res);
}

bool BookSystem::ShowKeyword(string &keyword, vector<Book> &res) {
    return ShowCommon(keyword, keyword_index, res);
}

void BookSystem::Select(string &isbn) {
    char isbn_[21];
    strcpy(isbn_, isbn.c_str());
    vector<int> index;
    isbn_index.Find(isbn_, index);
    if (isbn_index.Find(isbn_, index))
        file.Read(selected, address = index[0]);
    else {
        Book book(isbn_);
        file.Write(book, address = n++);
        isbn_index.Insert(isbn_, address);
        selected = book;
    }
}

bool BookSystem::IsSelected() {
    return selected.IsExisted();
}

void BookSystem::ModifyIsbn(string &isbn) {
    char isbn_[21];
    strcpy(isbn_, selected.isbn);
    strcpy(selected.isbn, isbn.c_str());
    file.Write(selected, address);
    isbn_index.Delete(isbn_, address);
    isbn_index.Insert(selected.isbn, address);
}

void BookSystem::ModifyName(string &name) {
    char name_[61];
    strcpy(name_, selected.name);
    strcpy(selected.name, name.c_str());
    file.Write(selected, address);
    name_index.Delete(name_, address);
    name_index.Insert(selected.name, address);
}

void BookSystem::ModifyAuthor(string &author) {
    char author_[61];
    strcpy(author_, selected.author);
    strcpy(selected.author, author.c_str());
    file.Write(selected, address);
    author_index.Delete(author_, address);
    author_index.Insert(selected.author, address);
}

void BookSystem::ModifyKeyword(vector<string> &keywords) {
    char keyword_[61][61];
    int used_n = selected.n;
    for (int i = 0; i < used_n; ++i)
        strcpy(keyword_[i], selected.keyword[i]);
    selected.n = keywords.size();
    for (int i = 0; i < selected.n; ++i)
        strcpy(selected.keyword[i], keywords[i].c_str());
    file.Write(selected, address);
    for (int i = 0; i < used_n; ++i)
        keyword_index.Delete(keyword_[i], address);
    for (int i = 0; i < selected.n; ++i)
        keyword_index.Insert(selected.keyword[i], address);
}

void BookSystem::ModifyPrice(string &price) {
    selected.price = stod(price);
    file.Write(selected, address);
}

bool BookSystem::Modify(string &isbn, string &name, string &author, vector<string> &keywords, string &price) {
    if (address == -1)
        return false;
    if (!isbn.empty()) {
        char isbn_[21];
        vector<int> index;
        strcpy(isbn_, isbn.c_str());
        if (isbn_index.Find(isbn_, index))
            return false;
        ModifyIsbn(isbn);
    }
    if (!name.empty())
        ModifyName(name);
    if (!author.empty())
        ModifyAuthor(author);
    if (!keywords.empty())
        ModifyKeyword(keywords);
    if (!price.empty())
        ModifyPrice(price);
    return true;
}

bool BookSystem::Import(string &quantity, string &total_cost) {
    if (address == -1)
        return false;
    selected.quantity += stoi(quantity);
    selected.total_cost += stod(total_cost);
    file.Write(selected, address);
    return true;
}

bool BookSystem::Buy(string &isbn, string &quantity, Book &book) {
    char isbn_[21];
    strcpy(isbn_, isbn.c_str());
    vector<int> index;
    if (!isbn_index.Find(isbn_, index))
        return false;
    int int_quantity = stoi(quantity);
    file.Read(book, index[0]);
    if (book.quantity < int_quantity)
        return false;
    book.quantity -= int_quantity;
    file.Write(book, index[0]);
    if (index[0] == address)
        file.Read(selected, address);
    return true;
}

void BookSystem::DeSelect() {
    selected = Book();
    address = -1;
}

int BookSystem::SelectedAddress() {
    return address;
}

Book BookSystem::SelectedBook() {
    return selected;
}

void BookSystem::Select(int book) {
    address = book;
    if (address == -1)
        selected = Book();
    else
        file.Read(selected, address);
}

BookSystem::~BookSystem() {
    file.WriteInfo(n, 0);
}