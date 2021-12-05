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

    Node(int _index, char *_key, int _hash, int _children);

    int Find(char *_key, int _hash);

    bool Insert(char *_key, int _hash, int _children);

    bool Delete(char *_key, int _hash);

    void Shift(int k);

    void DeShift(int k);

    void Split(Node &node);

    void Merge(Node &node);
};

class BPlusTree {
    char file_name[MAXS];
    fstream file;
    int n, r;
    static const int sizeof_node = sizeof(Node);
    static const int sizeof_int = sizeof(int);
public:
    void DFSOutput(int index);

    void Output();

    void Initialize();

    BPlusTree(char *fileName);

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

    void Find(char *key, vector<int> &value);
};

#endif //BOOKSTORE_BPLUSTREE_H
