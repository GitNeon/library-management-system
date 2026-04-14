#include <iostream>
#include <fstream>  // 文件读取必须的头文件
#include <sstream>  // 字符串流（用来切分逗号）必须的头文件
#include <limits> // 用于处理错误的输入缓冲区
#include <cstdint>

#ifdef _WIN32
#define NOMINMAX // 防止 windows.h 定义 max/min 宏，避免与标准库冲突
#include <windows.h>
#endif

#include "entity/user.h"
#include "entity/book.h"

using namespace std; // 在 main.cpp 里用 using namespace std; 是允许的

// ==================== 界面打印函数 ====================

/// @brief 打印欢迎界面
void showWelcome() {
    cout << "==========================================\n";
    cout << "*                                        *\n";
    cout << "*       欢迎使用图书管理系统 (V1.0)      *\n";
    cout << "*                                        *\n";
    cout << "==========================================\n";
}

/// @brief 打印主菜单
void showMainMenu() {
    cout << "\n【 主 菜 单 】\n";
    cout << "------------------------------------------\n";
    cout << "  1. 登录系统\n";
    cout << "  0. 退出程序\n";
    cout << "------------------------------------------\n";
    cout << "请输入您的选择 (0-1): ";
}

/// @brief 打印管理员菜单界面
void printAdminMenu() {
    cout << "\n【 管 理 员 菜 单 】\n";
    cout << "------------------------------------------\n";
    cout << "  1. 添加图书\n";
    cout << "  2. 删除图书\n";
    cout << "  3. 修改图书信息\n";
    cout << "  4. 查看所有图书\n";
    cout << "  0. 返回上一级\n";
    cout << "------------------------------------------\n";
    cout << "请输入您的选择 (0-4): ";
}

/// @brief 检查图书编号是否已存在
bool isBookIdExist(const string& id) {
    ifstream inFile("./data/book.csv");
    if (!inFile.is_open()) return false;

    string line;
    getline(inFile, line); // 跳过表头

    while (getline(inFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string fileBookId;
        getline(ss, fileBookId, ',');
        if (fileBookId == id) {
            inFile.close();
            return true;
        }
    }

    inFile.close();
    return false;
}

/// @brief 添加图书功能
void doAddBook() {
    cout << "\n--- 添加图书 ---\n";

    string id, name, author, publisher, publishDate;
    uint16_t total;

    cout << "请输入图书编号: ";
    cin >> id;
    cout << "请输入书名: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空缓冲区，防止书名被截断
    getline(cin, name);
    cout << "请输入作者: ";
    getline(cin, author);
    cout << "请输入出版社: ";
    getline(cin, publisher);
    cout << "请输入出版日期: ";
    getline(cin, publishDate);
    cout << "请输入总册数: ";
    cin >> total;

    // 校验总册数合法性
    if (cin.fail() || total <= 0) {
        cout << "\n【错误】总册数必须为正整数！\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    // 校验图书编号是否已存在
    if (isBookIdExist(id)) {
        cout << "\n【错误】图书编号 " << id << " 已存在，请勿重复添加！\n";
        return;
    }

    // 构造 Book 对象
    Book newBook(id, name, author, publisher, publishDate, static_cast<uint16_t>(total));

    // 追加写入 CSV 文件
    ofstream outFile("./data/book.csv", ios::app);
    if (!outFile.is_open()) {
        cout << "\n【系统错误】无法打开 book.csv 文件！\n";
        return;
    }

    outFile << newBook.getId() << ","
            << newBook.getName() << ","
            << newBook.getAuthor() << ","
            << newBook.getPublisher() << ","
            << newBook.getPublishDate() << ","
            << newBook.getTotal() << ","
            << newBook.getAvailable() << "\n";

    outFile.close();
    cout << "\n【成功】图书《" << name << "》添加成功！\n";
}

/// @brief 管理员菜单循环
void showAdminMenu() {
    int choice = -1;

    do {
        printAdminMenu();
        cin >> choice;

        if (cin.fail()) {
            cout << "\n【错误】输入非法！请输入数字。\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
            case 1:
                doAddBook();
                break;
            case 2:
                cout << "\n>>> 删除图书功能开发中...\n";
                break;
            case 3:
                cout << "\n>>> 修改图书信息功能开发中...\n";
                break;
            case 4:
                cout << "\n>>> 查看所有图书功能开发中...\n";
                break;
            case 0:
                cout << "\n>>> 返回上一级菜单。\n";
                break;
            default:
                cout << "\n【错误】您输入的选项不存在，请重新选择！\n";
                break;
        }
    } while (choice != 0);
}

void showReaderMenu() {
    cout << "\n>>> 进入 [读者菜单] (功能开发中...)\n";
}


// ==================== 核心业务函数 (占位符) ====================

/// @brief 登录功能（后续实现）
void doLogin() {
    cout << "\n>>> 正在进入登录模块...\n";
    // 这里未来会写：读取user.csv -> 比对账号密码 -> 根据isAdmin进入不同菜单

    string input_username;
    string input_password;

    cout << "\n--- 用户登录 ---\n";
    cout << "请输入账号: ";
    cin >> input_username;
    cout << "请输入密码: ";
    cin >> input_password;

    ifstream inFile("./data/user.csv");
    if (!inFile.is_open()) {
        cout << "\n【系统错误】找不到 user.csv 文件！\n";
        return; // 直接返回主菜单
    }

    string line;
    bool isLoginSuccess = false;
    bool isAdmin = false;

    // 读取第一行表头，并丢弃（不需要处理）
    getline(inFile, line);

    while (getline(inFile, line)) {
        // 如果遇到空行就跳过（防止CSV末尾多了一个回车）
        if (line.empty()) continue;

        // 【核心技巧】：用 stringstream 把这一行字符串塞进去，然后用逗号切分
        stringstream ss(line);
        string fileUsername, filePassword, fileRealName, fileIsAdminStr;

        // 按逗号拆分，分别存入四个变量
        getline(ss, fileUsername, ',');
        getline(ss, filePassword, ',');
        getline(ss, fileRealName, ',');
        getline(ss, fileIsAdminStr, ',');

        // 4. 比对账号和密码
        if (fileUsername == input_username && filePassword == input_password) {
            isLoginSuccess = true;
            // CSV里存的是 "1" 或 "0"，转成 bool 类型
            isAdmin = (fileIsAdminStr == "1"); 
            
            cout << "\n【提示】登录成功！欢迎您，" << fileRealName << "。\n";
            break; // 找到了就立刻跳出循环，不用再往下找了
        }
    }

    inFile.close();
    
    // 根据登录结果分发菜单
    if (isLoginSuccess) {
        if (isAdmin) {
            showAdminMenu();
        } else {
            showReaderMenu();
        }
    } else {
        cout << "\n【错误】账号或密码错误！请重新登录。\n";
    }
}

// ==================== 主函数 ====================

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);       // 设置控制台输入编码为 UTF-8
    SetConsoleOutputCP(65001); // 设置控制台输出编码为 UTF-8
#endif

    int choice = -1; // 初始化为一个不可能的菜单选项

    // do-while 循环：先显示一次菜单，再判断条件
    // 这是写控制台菜单最标准的句式
    do {
        showWelcome();
        showMainMenu();

        // 接收用户输入
        cin >> choice;

        // 【防坑核心】：如果用户输入的不是数字（比如输入了字母 a）
        if (cin.fail()) {
            cout << "\n【错误】输入非法！请输入数字。\n";
            cin.clear(); // 清除错误状态标志
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空输入缓冲区里的垃圾字符
            choice = -1; // 强制把选项重置为非法，让它走下面的 default
            continue;    // 直接跳过后面的 switch，重新循环画菜单
        }

        // 根据用户的选择执行不同操作
        switch (choice) {
            case 1:
                doLogin();
                break;
            case 0:
                cout << "\n>>> 感谢使用，再见！\n";
                break;
            default:
                cout << "\n【错误】您输入的选项不存在，请重新选择！\n";
                break;
        }

    } while (choice != 0); // 只要不是选 0，就一直在循环里出不来

    return 0;
}
