#include <functional>
#include <iostream>
#include <string>
#include <windows.h>
#include <memory>
#include <typeinfo>

using namespace std;

class Screen {
public:
    typedef string::size_type pos;

    char get_cursor() const {
        return contents[cursor];
    }

    char get() const;

    char get(pos ht, pos wd) const {
        return 'T';
    };

    string testContent = "TEST";
private:
    string contents = "prtest";
    pos cursor = 0;
    pos height = 100;
    pos width = 100;
};

class Player {
private:
    string m_name;
    int m_score;
public:
    Player(string n) : m_name(n) {}

    // 1. 无参数的常量成员函数
    int getLevel() const {
        return 99;
    }

    // 2. 带参数的普通成员函数
    void setScore(int score) {
        m_score = score;
        std::cout << m_name << " 的分数被设置为: " << m_score << std::endl;
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // 测试1，数据成员指针的定义
    // 假设我们有一个ptr指针指向Screen中的某个成员
    const string Screen::*ptr;
    ptr = &Screen::testContent;

    Screen *myScreen = new Screen();
    cout << myScreen->*ptr << endl;

    // 指向成员函数
    auto func_ptr = &Screen::get_cursor;
    cout << (myScreen->*func_ptr)() << endl;

    // 重载的函数，必须显式的声明函数类型
    char (Screen::*pmf2)(Screen::pos h, Screen::pos w) const;
    pmf2 = &Screen::get;

    cout << (myScreen->*pmf2)(0, 0) << endl;

    using Action = char (Screen::*)(Screen::pos, Screen::pos) const;
    Action get = &Screen::get;

    delete myScreen;

    // 测试:function包装成员函数
    // 使用function 生成一个可调用对象
    // auto fcn = &string::empty;
    std::function<bool (const string&)> fcn = &string::empty;

    cout << "----------------" << endl;

    // 自定义类的function使用
    function<int (const Player&)> fcn_getLevel =  &Player::getLevel;
    Player p("Alice");
    // 调用时，第一个参数传对象
    std::cout << fcn_getLevel(p) << std::endl; // 输出 99

    // 非const函数
    function<void (Player&, int)> fcn_setScore_ref = &Player::setScore;
    Player p1("Bob");
    // 调用时，第一个参数传对象，后面传方法的参数
    fcn_setScore_ref(p1, 100); // 输出: Bob 的分数被设置为: 100


    // 不需要写模板参数！直接传入成员函数指针
    auto fcn_mem = std::mem_fn(&Player::setScore);

    Player p2("Bob2");
    fcn_mem(&p2, 100);

    return 0;
}
