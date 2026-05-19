#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <memory>

using namespace std;

class HasPtr {
public:

    // 为了方便观察，增加一个 show 方法
    void show(const string& objName) const {
        cout << "[" << objName << "] Value: " << *ps
             << ", String Addr: " << ps
             << ", i: " << i << endl;
    }

    HasPtr(const string &s = string())
    : ps(new string(s)), i(0) {
        cout << "[Constructor] Called for: " << s << endl;
    }

    HasPtr(const HasPtr &p)
    : ps(new string(*p.ps)), i(p.i) {
        cout << "[Copy Constructor] Called to copy: " << *p.ps << endl;
    }

    HasPtr& operator=(const HasPtr &h);

    ~HasPtr() {
         cout << "[Destructor] Freeing memory for: " << *ps
             << " (Addr: " << ps << ")" << endl;
        delete ps;
     }

private:
    string *ps;
    int i;
};

HasPtr& HasPtr::operator=(const HasPtr &rhs) {
    auto newHas = new string(*rhs.ps);

    cout << "[HasPtr::operator=] Deleting old string: " << *ps
         << " (Addr: " << ps << ")" << endl;

    delete ps;

    cout << "[HasPtr::operator=] ps is deleted: " << *ps
        << " (Addr: " << ps << ")" << endl;

    ps = newHas;
    i = rhs.i;

    return * this;
};

// 专门测试自赋值的函数
void testSelfAssignment(HasPtr h) {
    cout << "\n--- 4. Testing Self-Assignment ---" << endl;
    h.show("h before self-assignment");
    h = h; // 触发自赋值
    h.show("h after self-assignment");
    cout << "--------------------------------" << endl;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "[========== main function running ==========]" << "\n\n";

    // 1. 测试构造函数
    cout << "--- 1. Testing Constructors ---" << endl;
    HasPtr h1;             // 默认构造
    HasPtr h2("Hello");    // 带参构造
    h1.show("h1");
    h2.show("h2");

    // 2. 测试拷贝构造函数（深拷贝验证）
    cout << "\n--- 2. Testing Copy Constructor (Deep Copy) ---" << endl;
    HasPtr h3 = h2;        // 拷贝构造
    h2.show("h2");
    h3.show("h3");
    // 期望结果：h2 和 h3 的 Value 相同，但 String Addr 不同（说明深拷贝成功，各自独立）

    // 3. 测试拷贝赋值运算符（深拷贝与旧内存释放验证）
    cout << "\n--- 3. Testing Copy Assignment Operator ---" << endl;
    h1 = h3;               // 拷贝赋值
    h1.show("h1");
    h3.show("h3");
    // 期望结果：h1 和 h3 的 Value 相同，String Addr 不同。
    // 并且从析构信息可以看到，h1 原来指向的空字符串内存被正确释放了。

    cout << "\n--- 调用testSelfAssignment(h1) 触发拷贝构造函数 ---" << endl;
    // 4. 测试自赋值 (h1 = h1)
    // 注意：这里采用值传递调用函数，是为了在函数内部安全地测试自赋值，
    // 同时观察函数结束时局部对象的析构。
    testSelfAssignment(h1);

    // 5. 测试局部对象的析构顺序
    cout << "\n--- 5. Testing Destructor Order (Leaving main scope) ---" << endl;
    // 当 main 函数结束时，h1, h2, h3 会按照构造的逆序析构。
    // 如果深拷贝没做好（浅拷贝），这里一定会报 Double Free 的崩溃。
    // 现在你的代码是安全的，不会有内存泄漏和双释放。

    std::cout << "\n[========== main function ending ==========]" << "\n";

    return 0;
}
