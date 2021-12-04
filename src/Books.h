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
 *                  ISBN
 *                  book name
 *                  author
 *                  keyword
 *              output:
 *                  in ascending order
 *                  [ISBN] \t [book name] \t [author] \t [keyword] \t [price] \t [count] \n
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
 *              parameter: ISBN, quantity
 *              status:
 *                  failed: no books is in required
 *                  successful
 *              priority: 1
 *          select: (log out seemed as deselect)
 *              function: select particular book
 *              parameter: ISBN
 *              status:
 *                  successful:
 *                      no such ISBN: create such book with just ISBN
 *              priority: 3
 *          modify:
 *              function: modify some information
 *              parameter: (maybe more than one)
 *                  ISBN
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
 *          ISBN: visible ascii; max length = 20
 *          Name: visible ascii except ""; max length = 60
 *          Author: visible ascii except ""; max length = 60
 *          Keyword: visible ascii except ""; max length = 60; divided by |
 *          Price: number and .; max length = 13; 2-bit precision
 *          Quantity: number; max length = 10; int
 *          Cost: number and .; max length = 13; 2-bit precision
 */

#endif //BOOKSTORE_BOOKS_H
