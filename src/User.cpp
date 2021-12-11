//
// Created by Okami on 2021/12/6.
//

#include "User.h"

User::User() = default;

User::User(char *_id, char *_name, char *_password, int priority):  priority(priority) {
    strcpy(id, _id);
    strcpy(name, _name);
    strcpy(password, _password);
}

void UserSystem::Output() {
    puts("---begin---");
    for (int i = 0; i < users.size(); ++i) {
        User temp;
        file.Read(temp, users[i].user);
        cout << temp.id << " " << temp.name << " " << temp.password << " " << temp.priority << endl;
    }
    puts("---end---");
    cout << endl;
    puts("---begin---");
    for (int i = 0; i < n; ++i) {
        User temp;
        file.Read(temp, i);
        cout << temp.id << " " << temp.name << " " << temp.password << " " << temp.priority << endl;
    }
    puts("---end---");
    cout << endl;
}

void UserSystem::Initialize() {
    file.Initialize();
    id_index.Initialize();
    file.WriteInfo(n = 2, 0);
    char root_id[31] = "root", root_name[31] = "root", root_password[31] = "sjtu";
    char guest_id[31] = "guest", guest_name[31] = "guest", guest_password[31] = "guest";
    User root(root_id, root_name, root_password, 7), guest(guest_id, guest_name, guest_password, 0);
    file.Write(guest, 0);
    id_index.Insert(root_id, 1);
    file.Write(root, 1);
    online.clear();
    online[0] = 1;
    while (!users.empty())
        users.pop_back();
    users.emplace_back(0);
}

UserSystem::UserSystem(): file("UserBasic.dat"), id_index("UserId.bin") {
    if (!file.IsExisted())
        Initialize();
    else {
        file.ReadInfo(n, 0);
        online[0] = 1;
        users.emplace_back(0);
    }
}

UserSystem::~UserSystem() {
    file.WriteInfo(n, 0);
}

bool UserSystem::Su(string &_id, string &_password) {
    if (_id.empty())
        return false;
    char id[31], password[31];
    strcpy(id, _id.c_str());
    strcpy(password, _password.c_str());
    User selected;
    vector<int> res;
    if (!id_index.Find(id, res))
        return false;
    file.Read(selected, res[0]);
    if ((_password.empty() && !CheckPriority(selected.priority + 1)) || (!_password.empty() && strcmp(selected.password, password) != 0))
        return false;
    users.emplace_back(res[0]);
    ++online[res[0]];
    return true;
}

bool UserSystem::LogOut() {
    if (users.size() == 1)
        return false;
    --online[users.back().user];
    users.pop_back();
    return true;
}

bool UserSystem::Register(string &_id, string &_password, string &_name) {
    char id[31], password[31], name[31];
    strcpy(id, _id.c_str());
    vector<int> res;
    if (id_index.Find(id, res))
        return false;
    id_index.Insert(id, n);
    strcpy(password, _password.c_str());
    strcpy(name, _name.c_str());
    User selected(id, name, password, 1);
    file.Write(selected, n++);
    return true;
}

bool UserSystem::Passwd(string &_id, string &_old_password, string &_new_password) {
    if (users.size() == 1)
        return false;
    if (!CheckPriority(7) && _old_password.empty())
        return false;
    vector<int> res;
    char id[31], new_password[31], old_password[31];
    strcpy(id, _id.c_str());
    if (!id_index.Find(id, res))
        return false;
    User selected;
    file.Read(selected, res[0]);
    strcpy(new_password, _new_password.c_str());
    strcpy(old_password, _old_password.c_str());
    if (!_old_password.empty() && strcmp(selected.password, old_password))
        return false;
    strcpy(selected.password, new_password);
    file.Write(selected, res[0]);
    return true;
}

bool UserSystem::UserAdd(string &_id, string &_password, string &_priority, string &_name) {
    int priority = stoi(_priority);
    if (!CheckPriority(max(3, priority + 1)))
        return false;
    char id[31], password[31], name[31];
    strcpy(id, _id.c_str());
    vector<int> res;
    if (id_index.Find(id, res))
        return false;
    id_index.Insert(id, n);
    strcpy(password, _password.c_str());
    strcpy(name, _name.c_str());
    User selected(id, name, password, priority);
    file.Write(selected, n++);
    return true;
}

bool UserSystem::Delete(string &_id) {
    if (!CheckPriority(7))
        return false;
    vector<int> res;
    char id[31];
    strcpy(id, _id.c_str());
    if (!id_index.Find(id, res) || online[res[0]])
        return false;
    id_index.Delete(id, res[0]);
    User temp;
    file.Write(temp, res[0]);
    return true;
}

bool UserSystem::Select(int book) {
    if (users.size() == 1)
        return false;
    UserPair current = users.back();
    users.pop_back();
    current.book = book;
    users.push_back(current);
    return true;
}

bool UserSystem::IsEmpty() {
    return users.size() == 1;
}

int UserSystem::Book() {
    return users.back().book;
}

bool UserSystem::CheckPriority(int priority) {
    User current;
    file.Read(current, users.back().user);
    return priority <= current.priority;
}

UserPair::UserPair(int user): user(user) {
    user = -1;
    book = -1;
};

void UserPair::Select(int _book) {
    book = _book;
}