#include <iostream>
#include <string>
#include <windows.h>
#include <memory>

using namespace std;

class A {
public:
    A() { cout << "A()" << endl; }
    virtual ~A() { cout << "~A()" << endl; } // 必须有虚函数！使得类成为多态类型
};

class B : public A {
public:
    B() { cout << "B()" << endl; }
    virtual ~B() { cout << "~B()" << endl; }
};

class C : public B {
public:
    C() { cout << "C()" << endl; }
    virtual ~C() { cout << "~C()" << endl; }
};

class D : public B, public A {
public:
    D() { cout << "D()" << endl; }
    virtual ~D() { cout << "~D()" << endl; }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // 测试（1）
    A* pa1 = new C;
    B* pb1 = dynamic_cast<B*>(pa1);
    cout << "测试(1) pb1: " << pb1 << (pb1 ? " 成功" : " 失败") << endl;
    delete pa1;

    cout << "------------------" << endl;

    // 测试（2）, 毫无疑问，失败了，因为B的指针实际指向B对象，B不是C的派生类，所以无法转换成功
    // 这个和测试1是有区别的，虽然C对象的指针是A，但是这个指针实际指向的对象是C对象，C是B的派生类，所以能转换成功！
    B* pb2 = new B;
    C* pc2 = dynamic_cast<C*>(pb2);
    cout << "测试(2) pc2: " << pc2 << (pc2 ? " 成功" : " 失败") << endl;
    delete pb2;

    // 测试（3）
    // A* pa3 = new D; // 取消注释这一行，直接导致编译错误！

    return 0;
}
