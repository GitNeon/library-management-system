#include <iostream>
#include <string>
#include <windows.h>
#include <memory>
#include <typeinfo>

using namespace std;

class Base { }; // 非多态类
class Derived : public Base { };

class PolyBase { public: virtual void foo() {} }; // 多态类
class PolyDerived : public PolyBase { };

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // 1. 非多态情况
    Derived d;
    Base* pb = &d;

    std::cout << "非多态 - typeid(pb): " << typeid(pb).name() << std::endl;   // 输出: P4Base (指针类型)
    std::cout << "非多态 - typeid(*pb): " << typeid(*pb).name() << std::endl;  // 输出: 4Base   (静态解引用，丢失了Derived信息)

    // 2. 多态情况
    PolyDerived pd;
    PolyBase* ppb = &pd;

    std::cout << "多态 - typeid(ppb): " << typeid(ppb).name() << std::endl;   // 输出: P8PolyBase (指针类型)
    std::cout << "多态 - typeid(*ppb): " << typeid(*ppb).name() << std::endl;  // 输出: 11PolyDerived (动态解引用，获取了真实类型)

    cout << "-------------------------------------------" << endl;

    return 0;
}
