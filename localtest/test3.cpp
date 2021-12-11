//
// Created by Okami on 2021/12/7.
//

#include "BPlusTree.h"
#include "Book.h"

using namespace std;

BookSystem book_system;

int main() {
    book_system.Initialize();
    string isbn = "123456789", name = "Legend of me", author = "Okami", keyword = "biography|legend|supreme|immortal", price = "100.00", quantity = "100", total_cost = "10000.00";
    book_system.Select(isbn);
    book_system.ModifyName(name);
    book_system.ModifyAuthor(author);
    book_system.ModifyKeyword(keyword);
    book_system.ModifyPrice(price);
    book_system.Import(quantity, total_cost);
    vector<Book> res;
    book_system.ShowAuthor(author, res);
    for (int i = 0; i < res.size(); ++i)
        cout << res[i] << endl;
    puts("");
}