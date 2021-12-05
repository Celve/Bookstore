//
// Created by Okami on 2021/12/2.
//

#ifndef BOOKSTORE_USERS_H
#define BOOKSTORE_USERS_H

/*
 *  User system
 *      Operation:
 *          su:
 *              function: log in
 *              parameter: id, password(omitted with higher priority)
 *              status: failed(wrong password), successful
 *              required priority: 0
 *          logout:
 *              function: log out
 *              parameter: none
 *              status: failed(no active account), successful
 *              required priority: 1
 *          register:
 *              function: register an account(priority 1)
 *              parameter: id, password, name
 *              status: failed(id is same as existed account), successful
 *              required priority: 0
 *          passwd:
 *              function: reset password
 *              parameter: id, old password(omitted with priority 7), new password
 *              status: failed(no such account, wrong answer), successful
 *              required priority: 1
 *          useradd:
 *              function: just like register, but with priority
 *              parameter: id, password, priority, name
 *              status: failed(priority equaled or higher), successful
 *              required priority: 3
 *          delete:
 *              function: delete the account
 *              parameter: id
 *              status: failed(didn't exist, active)
 *              required priority: 7
 */

/*
 *  User
 *      Property:
 *          ID: letter, number and _; max length = 30
 *          Name: visible ascii; max length = 30
 *          Password: letter, number and _; max length = 30
 *          Priority: {7, 3, 1}
 */

#endif //BOOKSTORE_USERS_H
