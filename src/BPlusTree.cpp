//
// Created by Okami on 2021/12/4.
//

#include "BPlusTree.h"

void BPlusTree::Output() {
    cout << "Output: " << n << endl;
    cout << "Root: " << r << endl;
    for (int i = 0; i < n; ++i) {
        Node temp;
        Read(temp, i);
        cout << i << "(" << temp.is_leaf << ")"<< ": ";
        for (int j = 0; j < temp.n; ++j)
            cout << temp.key[j] << " ";
        cout << "| ";
        for (int j = 0; j < temp.n; ++j)
            cout << temp.children[j] << " ";
        cout << "| ";
        for (int j = 0; j < temp.n; ++j)
            cout << temp.hash[j] << " ";
        cout << endl;
    }
    cout << endl;
}

Node::Node(int index): index(index) {
    pre = next = -3;
    n = 0;
    is_leaf = false;
}

Node::Node(int _index, const char *_key, int _hash, const int _children) {
    index = _index;
    pre = next = -3;
    n = 1;
    is_leaf = false;
    strcpy(key[0], _key);
    hash[0] = _hash;
    children[0] = _children;
}

bool Node::Insert(const char *_key, int _hash, const int _children) {
    for (int i = 0; i < n; ++i) {
        if (!strcmp(_key, key[i]) && _hash == hash[i])
            return false;
        if (strcmp(_key, key[i]) < 0 || (!strcmp(_key, key[i]) && _hash < hash[i])) {
            Shift(i);
            strcpy(key[i], _key);
            hash[i] = _hash;
            children[i] = _children;
            ++n;
            return true;
        }
    }
    strcpy(key[n], _key);
    hash[n] = _hash;
    children[n++] = _children;
    return true;
}

bool Node::Delete(const char *_key, int _hash) {
    for (int i = 0; i < n; ++i) {
        if (!strcmp(_key, key[i]) && _hash == hash[i]) {
            DeShift(i);
            --n;
            return true;
        }
    }
    return false;
}

void Node::DeShift(int k) {
    for (int i = k; i < n - 1; ++i) {
        swap(key[i], key[i + 1]);
        swap(hash[i], hash[i + 1]);
        swap(children[i], children[i + 1]);
    }
}

void Node::Shift(int k) {
    for (int i = n - 1; i >= k; --i) {
        swap(key[i], key[i + 1]);
        swap(hash[i], hash[i + 1]);
        swap(children[i], children[i + 1]);
    }
}

void Node::Split(Node &node) {
    node.n = n - (n >> 1);
    n >>= 1;
    for (int i = 0; i < node.n; ++i) {
        strcpy(node.key[i], key[i + n]);
        node.hash[i] = hash[i + n];
        node.children[i] = children[i + n];
    }
}

void Node::Merge(Node &node) {
    for (int i = 0; i < node.n; ++i) {
        strcpy(key[n + i], node.key[i]);
        hash[n + i] = node.hash[i];
        children[n + i] = node.children[i];
    }
    n += node.n;
}

void BPlusTree::Write(Node &node, int i) {
    int index = sizeof(int) * 2 + sizeof(Node) * (i + 1);
    file.open(file_name);
    file.seekp(index);
    file.write(reinterpret_cast<char *>(&node), sizeof(Node));
    file.close();
}

void BPlusTree::Read(Node &node, int i) {
    int index = sizeof(int) * 2 + sizeof(Node) * (i + 1);
    file.open(file_name);
    file.seekg(index);
    file.read(reinterpret_cast<char *>(&node), sizeof(Node));
    file.close();
}

void BPlusTree::AddBehind(Node &node, Node &pre_node) {
    Node next_node;
    Read(next_node, pre_node.next);
    node.pre = pre_node.index;
    node.next = next_node.index;
    pre_node.next = node.index;
    next_node.pre = node.index;
    Write(pre_node, pre_node.index);
    Write(node, node.index);
    Write(next_node, next_node.index);
}

//n; r; head; tail; ...
void BPlusTree::Initialize() {
    file.open(file_name, std::ios::out);
    n = 0;
    file.write(reinterpret_cast<char *>(&n), sizeof(int));
    Node head, tail;
    head.next = tail.index = -1;
    tail.pre = head.index = -2;
    Write(head, -2);
    Write(tail, -1);
    file.close();
}

BPlusTree::BPlusTree(char *_file_name) {
    strcpy(file_name, _file_name);
    file.open(file_name);
    if (!file.good()) {
        file.close();
        Initialize();
    }
    else {
        file.read(reinterpret_cast<char *>(&n), sizeof(int));
        file.read(reinterpret_cast<char *>(&r), sizeof(int));
        file.close();
    }
}

BPlusTree::~BPlusTree() {
    file.open(file_name);
    file.write(reinterpret_cast<char *>(&n), sizeof(int));
    file.write(reinterpret_cast<char *>(&r), sizeof(int));
    file.close();
}

bool BPlusTree::Insert(const char *key, int value, int index) {
    Node node;
    Read(node, index);
    if (node.is_leaf) {
        bool status = node.Insert(key, value, value);
        if (!status)
            return false;
        Write(node, index);
        return true;
    }
    for (int i = 1; i <= node.n; ++i) {
        int judgement = strcmp(key, node.key[i]);
        if (i == node.n || judgement < 0 || (!judgement && value < node.hash[i])) {
            bool status = Insert(key, value, node.children[i - 1]);
            if (!status)
                return false;
            Node child;
            Read(child, node.children[i - 1]);
            strcpy(node.key[i - 1], child.key[0]);
            node.hash[i - 1] = child.hash[0];
            if (child.is_leaf && child.n >= MAXN) {
                Node half(n++);
                child.Split(half);
                half.is_leaf = true;
                AddBehind(half, child);
                node.Insert(half.key[0], half.hash[0], half.index);
            } else if (child.n >= MAXN + 1) {
                Node half(n++);
                child.Split(half);
                node.Insert(half.key[0], half.hash[0], half.index);
                Write(child, child.index);
                Write(half, half.index);
            }
            Write(node, index);
            return true;
        }
    }
    return false;
}

bool BPlusTree::Insert(const char *key, int value) {
    Node temp;
    Read(temp, r);
    if (!temp.n) {
        n = 2;
        r = 0;
        Node root(0, key, value, 1), node(1, key, value, value), head;
        node.is_leaf = true;
        Read(head, -2);
        AddBehind(node, head);
        Write(root, root.index);
        return true;
    }
    bool status = Insert(key, value, r);
    if (!status)
        return false;
    Node root;
    Read(root, r);
    if (root.n >= MAXN + 1) {
        n += 2;
        Node new_root(r = n - 2, root.key[0], root.hash[0], root.index), half(n - 1);
        root.Split(half);
        new_root.Insert(half.key[0], half.hash[0], half.index);
        Write(root, root.index);
        Write(new_root, new_root.index);
        Write(half, half.index);
    }
    return true;
}

int BPlusTree::Find(const char *key, int hash, int index) {
    Node node;
    Read(node, index);
    if (node.is_leaf) {
        for (int i = node.n - 1; i >= 0; --i)
            if (!strcmp(key, node.key[i]) && hash == node.hash[i])
                return node.children[i];
        return -1;
    }
    for (int i = 1; i <= node.n; ++i)
        if (i == node.n || strcmp(key, node.key[i]) < 0 || !strcmp(key, node.key[i]) && hash < node.hash[i])
            return Find(key, hash, node.children[i - 1]);
    return -1;
}

int BPlusTree::Find(const char *key, int hash) {
    return Find(key, hash, r);
}

int BPlusTree::FindPtr(const char *key, int index) {
    Node node;
    Read(node, index);
    if (node.is_leaf)
        return index;
    for (int i = 1; i <= node.n; ++i)
        if (i == node.n || strcmp(key, node.key[i]) < 0)
            return FindPtr(key, node.children[i - 1]);
    return -1;
}

void BPlusTree::Find(const char *key, vector<int> &value) {
    int index = FindPtr(key, r);
    if (index == -1)
        return;
    Node current;
    Read(current, index);
    bool flag = false;
    do {
        flag = false;
        for (int i = 0; i < current.n; ++i)
            if (!strcmp(current.key[i], key)) {
                flag = true;
                value.push_back(current.hash[i]);
            }
        if (current.pre >= 0 && current.n && !strcmp(current.key[0], key))
            Read(current, current.pre);
        else
            break;
    } while (flag);
    sort(value.begin(), value.end());
}

bool BPlusTree::Delete(const char *key, int hash, int index) {
    Node node;
    Read(node, index);
    if (node.is_leaf) {
        bool status = node.Delete(key, hash);
        if (!status)
            return false;
        Write(node, index);
        return true;
    }
    for (int i = 0; i < node.n; ++i)
        if (i == node.n - 1 || strcmp(key, node.key[i + 1]) < 0 || (!strcmp(key, node.key[i + 1]) && hash < node.hash[i + 1])) {
            bool status = Delete(key, hash, node.children[i]);
            if (!status)
                return false;
            Node child;
            Read(child, node.children[i]);
            if (child.n) {
                strcpy(node.key[i], child.key[0]);
                node.hash[i] = child.hash[0];
            }
            else {
                node.DeShift(i);
                --node.n;
            }
            int flag = !child.is_leaf;
            if (child.n && child.n < MINN + flag) {
                Node left_child, right_child, temp;
                if (i != 0) {
//                    puts("left lend");
                    Read(left_child, node.children[i - 1]);
                    if (left_child.n > MINN + flag) {
                        --left_child.n;
                        child.Insert(left_child.key[left_child.n], left_child.hash[left_child.n], left_child.children[left_child.n]);
                        strcpy(node.key[i], child.key[0]);
                        node.hash[i] = child.hash[0];
                        Write(node, index);
                        Write(left_child, left_child.index);
                        Write(child, child.index);
                        return true;
                    }
                }
                if (i != node.n - 1) {
//                    puts("right lend");
                    Read(right_child, node.children[i + 1]);
                    if (right_child.n > MINN + flag) {
                        child.Insert(right_child.key[0], right_child.hash[0], right_child.children[0]);
                        right_child.DeShift(0);
                        --right_child.n;
                        strcpy(node.key[i + 1], right_child.key[0]);
                        node.hash[i + 1] = right_child.hash[0];
                        Write(node, index);
                        Write(right_child, right_child.index);
                        Write(child, child.index);
                        return true;
                    }
                }
                if (i != 0) {
                    node.DeShift(i);
                    --node.n;
                    left_child.Merge(child);
                    if (left_child.is_leaf) {
                        left_child.next = right_child.index;
                        right_child.pre = left_child.index;
                        Write(right_child, right_child.index);
                    }
                    Write(left_child, left_child.index);
                    Write(node, node.index);
                    Write(temp, child.index);
                }
                else if (i != node.n - 1) {
                    node.DeShift(i + 1);
                    --node.n;
                    child.Merge(right_child);
                    swap(child.key, right_child.key);
                    swap(child.hash, right_child.hash);
                    swap(child.children, right_child.children);
                    swap(child.n, right_child.n);
//                    strcpy(node.key[i], right_child.key[0]);
//                    node.hash[i] = right_child.hash[0];
                    if (right_child.is_leaf) {
                        left_child.next = right_child.index;
                        right_child.pre = left_child.index;
                        Write(left_child, left_child.index);
                    }
                    Write(right_child, right_child.index);
                    Write(node, node.index);
                    Write(temp, child.index);
                }
                if (index == r && node.n == 1 && !child.is_leaf) {
                    Write(temp, r);
                    r = node.children[0];
                }
                return true;
            }
            else
                Write(node, node.index);
        }
    return false;
}

bool BPlusTree::Delete(const char *key, int hash) {
    Delete(key, hash, r);
}