//
// Created by Okami on 2021/12/6.
//

#include "User.h"

User::User() = default;

User::User(char *id_, char *name_, char *password_, int priority):  priority(priority) {
    strcpy(id, id_);
    strcpy(name, name_);
    strcpy(password, password_);
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

bool UserSystem::Su(string &id_, string &password_) {
    if (id_.empty())
        return false;
    char id[31], password[31];
    strcpy(id, id_.c_str());
    strcpy(password, password_.c_str());
    User selected;
    vector<int> res;
    if (!id_index.Find(id, res))
        return false;
    file.Read(selected, res[0]);
    if ((password_.empty() && !CheckPriority(selected.priority + 1)) || (!password_.empty() && strcmp(selected.password, password) != 0))
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

bool UserSystem::Register(string &id_, string &password_, string &name_) {
    char id[31], password[31], name[31];
    strcpy(id, id_.c_str());
    vector<int> res;
    if (id_index.Find(id, res))
        return false;
    id_index.Insert(id, n);
    strcpy(password, password_.c_str());
    strcpy(name, name_.c_str());
    User selected(id, name, password, 1);
    file.Write(selected, n++);
    return true;
}

bool UserSystem::Passwd(string &id_, string &old_password_, string &new_password_) {
    if (users.size() == 1)
        return false;
    if (!CheckPriority(7) && old_password_.empty())
        return false;
    vector<int> res;
    char id[31], new_password[31], old_password[31];
    strcpy(id, id_.c_str());
    if (!id_index.Find(id, res))
        return false;
    User selected;
    file.Read(selected, res[0]);
    strcpy(new_password, new_password_.c_str());
    strcpy(old_password, old_password_.c_str());
    if (!old_password_.empty() && strcmp(selected.password, old_password))
        return false;
    strcpy(selected.password, new_password);
    file.Write(selected, res[0]);
    return true;
}

bool UserSystem::UserAdd(string &id_, string &password_, string &_priority, string &name_) {
    int priority = stoi(_priority);
    if (!CheckPriority(max(3, priority + 1)))
        return false;
    char id[31], password[31], name[31];
    strcpy(id, id_.c_str());
    vector<int> res;
    if (id_index.Find(id, res))
        return false;
    id_index.Insert(id, n);
    strcpy(password, password_.c_str());
    strcpy(name, name_.c_str());
    User selected(id, name, password, priority);
    file.Write(selected, n++);
    return true;
}

bool UserSystem::Delete(string &id_) {
    if (!CheckPriority(7))
        return false;
    vector<int> res;
    char id[31];
    strcpy(id, id_.c_str());
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