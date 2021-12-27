//
// Created by Okami on 2021/12/3.
//

#ifndef BOOKSTORE_BOOKS_H
#define BOOKSTORE_BOOKS_H

/*
 *  Book system
 *      Operation:
 *          show:
 *              function: show some information
 *              parameter: (just one of these)
 *                  isbn
 *                  book name
 *                  author
 *                  keyword
 *              output:
 *                  in ascending order
 *                  [isbn] \t [book name] \t [author] \t [keyword] \t [price] \t [count] \n
 *              status:
 *                  failed:
 *                      blank parameter
 *                      multiple keyword
 *                  successful:
 *                      found
 *                      not been found
 *                      no parameter
 *              priority: 1
 *          buy:
 *              function: buy books in particular quantity
 *              parameter: isbn, quantity
 *              status:
 *                  failed: no books is in required
 *                  successful
 *              priority: 1
 *          select: (log out seemed as deselect)
 *              function: select particular book
 *              parameter: isbn
 *              status:
 *                  successful:
 *                      no such isbn: create such book with just isbn
 *              priority: 3
 *          modify:
 *              function: modify some information
 *              parameter: (maybe more than one)
 *                  isbn
 *                  name
 *                  author
 *                  keyword
 *                  price
 *              status:
 *                  failed:
 *                      didn't select a book
 *                      repeated same parameter
 *                      empty parameter content
 *                      keyword contain repeated information
 *                  successful
 *              priority: 3
 *          import:
 *              function: import books
 *              parameter: quantity, total cost
 *              status:
 *                  failed: didn't select a book
 *                  successful
 *              priority: 3
 */

/*
 *  Book
 *      Property:
 *          isbn: visible ascii; max length = 20
 *          Name: visible ascii except ""; max length = 60
 *          Author: visible ascii except ""; max length = 60
 *          Keyword: visible ascii except ""; max length = 60; divided by |
 *          Price: number and .; max length = 13; 2-bit precision
 *          Quantity: number; max length = 10; int
 *          Cost: number and .; max length = 13; 2-bit precision
 */

#define MAXS 64

#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "File.h"
#include <iomanip>
#include "BPlusTree.h"
#include "Utils.h"

using std::string;
using std::unordered_map;
using std::vector;
using std::stod;
using std::fstream;
using std::stoi;
using std::cout;
using std::endl;
using std::min;

class Book {
public:
    char isbn[21];
    char name[61];
    char author[61];
    int n;
    char keyword[61][61];
    double price;
    int quantity;
    double total_cost;

    Book();

    Book(string _isbn);

    bool IsExisted();

    friend std::ostream &operator << (std::ostream &os, const Book &book);

    bool operator < (const Book &rhs) const;
};

class BookSystem {
    int n, address;
    Book selected;
    File<Book, 1> file;
    BPlusTree isbn_index;
    BPlusTree name_index;
    BPlusTree author_index;
    BPlusTree keyword_index;

    bool ShowCommon(string &key, BPlusTree &index, vector<Book> &res);

public:
    void Initialize();

    BookSystem();

    void Output();

    void ShowAll(vector<Book> &res);

    bool ShowIsbn(string &isbn, vector<Book> &res);

    bool ShowName(string &name, vector<Book> &res);

    bool ShowAuthor(string &author, vector<Book> &res);

    bool ShowKeyword(string &keyword, vector<Book> &res);

    bool IsSelected();

    void Select(string &isbn);

    void ModifyIsbn(string &isbn);

    void ModifyName(string &name);

    void ModifyAuthor(string &author);

    void ModifyKeyword(vector<string> &keyword);

    void ModifyPrice(string &price);

    bool Modify(string &isbn, string &name, string &author, vector<string> &keywords, string &price);

    bool Import(string &quantity, string &total_cost);

    bool Buy(string &isbn, string &quantity, Book &book);

    void DeSelect();

    int GetAddress();

    Book SelectedBook();

    void Select(int book);

    ~BookSystem();
};

#endif //BOOKSTORE_BOOKS_H
