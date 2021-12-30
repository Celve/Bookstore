

# 开发文档Bookstore

_version：1.1_

_Author:  peroni_

## log

2021.12.16 统一了变量名；修改逻辑结构为顶层的Bookstore与四个子模块

2021.12.30 取消了emoji

## 程序功能

#### 一.图书信息的维护

#### 二.用户信息的维护

#### 三.书店交易相关信息维护

## 主体逻辑说明

命令统一由command类处理，再在其中进行其他类的相互调用

## 各个类的接口及成员说明

#### Bookstore.h/Bookstore.cpp

```c++
class Bookstore {
private:
    BookSystem book_system;
    UserSystem user_system;
    FinanceLogSystem finance_log_system;
    EmployeeLogSystem employee_log_system;
    
public:
    Bookstore();

    void Output();

    void Initialize();

    void Run(string &command);

    void Quit(vector<string> &list);

    void Su(vector<string> &list);

    void Logout(vector<string> &list);

    void Register(vector<string> &list);

    void Passwd(vector<string> &list);

    void UserAdd(vector<string> &list);

    void Delete(vector<string> &list);

    void Modify(vector<string> &list);

    void Buy(vector<string> &list);

    void Select(vector<string> &list);

    void Show(vector<string> &list);

    void Import(vector<string> &list);

    void Report(vector<string> &list);

    void Log(vector<string> &list);

    void ShowFinance(vector<string> &list);

    bool AddLog(vector<string> &lit);
};
```





#### UserSystem.cpp/UserSystem.h

##### UserSystem类

当前用户级别和书本选择；

```c++
class UserSystem {
    vector<UserPair> users;
    unordered_map<int, int> online;
    File<User, 1> file;
    BPlusTree id_index;
    int n;

public:
    UserSystem();

    ~UserSystem();

    void Initialize();

    void Output();

    bool Su(string &ID, string &password);

    bool LogOut();

    bool Register(string &_id, string &_password, string &_name);

    bool Passwd(string &_id, string &_old_password, string &_new_password);

    bool UserAdd(string &_id, string &_password, string &_priority, string &_name);

    bool Delete(string &_id);

    bool Select(int book);

    int Book();

    bool CheckPriority(int priority);

    bool Top(User &cur);

    bool IsEmpty();
};
```

##### User类

| 变量名     | 变量类型                |
| ---------- | ----------------------- |
| userID_    | 字符数组 max length: 30 |
| name_      | 字符数组 max length: 30 |
| authority_ | 整形                    |
| password_  | 字符数组 max length: 30 |

##### UserSelect类

```c++
class UserSelect{
  public:
    int userID_;
    char isbn_[20];
    bool bookselected_ = false;//当前是否选中图书
}
```



#### BookSystem.cpp/BookSystem.h

##### LogManager类

```c++
class LogManager{
public:
void showFinance(int time);

void showFinance();

void reportMyself();

void reportFinance();

void reportEmployee();

void showLog();
  
void addLog(string command);
}
```

```c++
class Log{
public:
 char[] employee_;
 char[] command_;
}
```



##### BookSystem类

```c++
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
```



##### Book类

```c++
class Book{
public:
char isbn_[20]; 
  
char name_[60]; 
  
char author_[60];
  
int keyword_num_;
  
char keyword_[keyword_num][60];
  
double price_; 
  
int quantity_; 
  
 }
```



#### Blocklist.cpp Blocklist.h

```c++
class UllNode {
public:
    int offset_;
    char str_[64];
  
bool operator<(const UllNode &x) const;

UllNode();

UllNode(const int &arg1, const std::string &arg2);


};

```

```c++
class UllBlock {
// For ULL class internal use only
public:
    int nxt_;
    int pre_;
    int num_;
    UllNode array_[BLOCK_SIZE];//BLOCK_SIZE块的大小

UllBlock();

UllBlock &operator=(const UllBlock &right);

};
```

```c++
class Ull {
private:
    const std::string file_name;
    std::fstream fi, fo, fi2, fo2, fip, fip2, fop, fop2;
    // File Input/Output fstream objects
    // P for private methods

inline int nextBlock(const int &offset);

inline void delBlock(const int &offset);

void mergeBlock(const int &offset1, const int &offset2);

void splitBlock(const int &offset);

public:
    Ull(const std::string &arg);

~Ull();

void findNode(const std::string &key, std::vector<int> &array);
// Returns an empty array if the node doesn't exist

void addNode(const UllNode &node);

int deleteNode(const UllNode &node);

}
```

## 文件存储结构

#### 内存

登陆栈

日志：time

#### 外存

##### books

book_basic.dat 

统一存储所有图书，按照添加前后顺序排列

##### user

user_basic.dat

userselect.dat

登陆账户及其选择的图书

##### log

command.dat

finance.dat

#### 索引文件

index_isbn.dat

index_author.dat

index_name.dat

index_keyword.dat

index_id.dat

index_employee.dat

## 具体算法说明

*关于key值重复的问题：维护第二关键字，重载比较函数。

*安排部分数据存储于内存：user stack

*对于关键字查询，将同一本书的不同关键字拆开，分别对应相同的index存入文件中。

*维护关于不同show方式的index文件

*对于用户和command文件也要开index加速寻找

*time次数的实现比较简单，直接从数据文件末根据size大小全部读入内存即可

## 其他补充说明

*参考了google命名规范

*生成日志格式：

```c++
📚 My Bookstore Log    [ 标题 ] for employee
---------------------------------------------

name 
	command

name
	command

📚 My Bookstore Log    [ 标题 ] for finance
---------------------------------------------
[ income ]  -[ outcome ]

[ income ]  -[ outcome ]
```

