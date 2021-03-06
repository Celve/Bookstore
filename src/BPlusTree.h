//
// Created by Okami on 2021/12/2.
//

#ifndef BOOKSTORE_BPLUSTREE_H
#define BOOKSTORE_BPLUSTREE_H

#define MAXN 40
#define MINN 19
#define MAXS 64

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <fstream>
#include "File.h"

using std::fstream;
using std::swap;
using std::cout;
using std::endl;
using std::vector;

class Node {
public:
    int n, r;
    int index, pre, next;
    bool is_leaf;
    char key[MAXN + 1][MAXS + 1];
    int hash[MAXN + 1];
    int children[MAXN + 1];

    explicit Node(int index = -2);

    Node(int index_, char *key_, int hash_, int children_);

    int Find(char *key_, int hash_);

    bool Insert(char *key_, int hash_, int children_);

    bool Delete(char *key_, int hash_);

    void Shift(int k);

    void DeShift(int k);

    void Split(Node &node);

    void Merge(Node &node);
};

class BPlusTree {
    char file_name[MAXS];
    File<Node> file;
    int n, r;
public:
    void DFSOutput(int index);

    void Output();

    void Initialize();

    BPlusTree(char *file_name);

    ~BPlusTree();

    void Write(Node &node, int i);

    void Read(Node &node, int i);

    void AddBehind(Node &node, Node &next_node);

    bool Insert(char *key, int value, Node &node);

    bool Insert(char *key, int value);

    int Find(char *key, int hash, Node &node);

    int Find(char *key, int hash);

    bool Delete(char *key, int hash, Node &node);

    bool Delete(char *key, int hash);

    int FindPtr(char *key, Node &node);

    bool Find(char *key, vector<int> &value);

    void Traverse(vector<int> &value);
};

#endif //BOOKSTORE_BPLUSTREE_H