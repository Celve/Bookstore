

# 开发文档Bookstore

_version：1.0_

_Author:  peroni_

## 程序功能

#### 一.图书信息的维护

#### 二.用户信息的维护

#### 三.书店交易相关信息维护

## 主体逻辑说明

命令统一由command类处理，再在其中进行其他类的相互调用

## 各个类的接口及成员说明

#### Main.cpp

##### 全局变量

```c++
vector<class userselect>//登陆栈，每次账号改变时更新当前操作权限

int priority = 0;
  
string selectISBN;
```

```c++
void Init();//实现初始化，root账户(usermanager类)
```

```c++
void RunCommand(string s);//读入一行命令并调用各类函数
```



#### Command.cpp/Command.h

##### CommandManager类

```c++
class CommandManager{
  
public:
  
void Run(string s);

string SplitString(string &before，string after, int devidedbykey = 0);//去掉before首1字符串，返回值after为首1字符串

bool CheckCommand(string s);//*鲁棒性

bool CheckPriority();//*判断权限是否正确

void Quit();

void Exit();
}
```



#### usermanager.cpp/usermanager.h

##### UserManager类

当前用户级别和书本选择；

```c++
class UserManager{
  
public:
  
void Initialize();//*初始化一个老板

bool Login(string id,string password);//*登陆

bool Login(string id);//*高权限登陆

bool Logout();//*登出

bool Register(string userID,string password,string username);//*注册

bool ChangePassword(string user_ID, string new_password, string old_password);//*修改密码

bool ChangePassword(string user_ID, string new_password);//*高权限修改密码

bool AddUser(string user_ID, string password, string priority, string user_name);//*创建账户

bool DeleteUser(string user_ID);//*删除账户
}
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
class Userselect{
  public:
    int userID_;
    char isbn_[20];
    bool bookselected = false;//当前是否选中图书
}
```



#### Bookstore.cpp/Bookstore.h

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



##### BookStore类

```c++
class BookStore{
public:
bool Buy(string isbn, int quantity);

bool show（string keyword）;

bool select(int isbn)

bool Modify(string isbn, string name, string author, string keyword, string price); 
}
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
  
double total_cost_;
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
    UllNode array_[BLOCK_SIZE];

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

🥸  name 
    command

🥸  name
    command

📚 My Bookstore Log    [ 标题 ] for finance
---------------------------------------------

💸 + [ income ]  -[ outcome ]

💸 + [ income ]  -[ outcome ]

📚 My Bookstore Log    [ 标题 ] for Log
---------------------------------------------
🥸  name   + "with" + command               💸 + [ income ]  -[ outcome ]
🥸  																				💸
🥸																					💸

```

