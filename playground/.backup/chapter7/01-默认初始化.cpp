#include <iostream>
#include <string>
#include <windows.h>

#include <iostream>
#include <string>

class HasDefault {
public:
    int val;
    HasDefault() : val(20) {
        std::cout << "HasDefault 默认构造函数被调用, val = " << val << std::endl;
    }
};

class NoDefault {
public:
    int val;
    NoDefault(int v) : val(v) {}
};

// 情况 2
class ClassWithMember {
public:
    HasDefault hd_member;
    int built_in_member;
};

// 情况 3
class ClassWithExplicitConstructor {
public:
    HasDefault hd_member;
    int built_in_member;
    ClassWithExplicitConstructor(int v) : built_in_member(v) {
        std::cout << "ClassWithExplicitConstructor 构造函数被调用" << std::endl;
    }
};

// 该程序演示了内置类型和类类型默认初始化的情况
int main() {
    // 情况 1
    {
        std::cout << "--- 情况 1：块作用域内的默认初始化，不使用任何初始值 ---" << std::endl;
        int num;    // 产生垃圾值
        HasDefault hd; // 自动调用默认构造函数
        std::cout << "内置类型 num 的值(未定义): " << num << std::endl;
    }

    // 情况 2
    {
        std::cout << "\n--- 情况 2：使用合成的默认构造函数 ---" << std::endl;

        // ClassWithMember类没有默认构造函数(使用合成的默认构造函数)
        // ClassWithMember类包含另一个类成员，合成的默认构造函数执行过程中，被默认初始化
        // 即这个类成员也会调用自己的默认构造函数。
        ClassWithMember obj;
        std::cout << "内置成员的值(未定义): " << obj.built_in_member << std::endl;
    }

    // 情况 3
    {
        std::cout << "\n--- 情况 3：初始化列表中遗漏成员 ---" << std::endl;

        // 这次类有自己的构造函数，但在构造函数的初始化列表中，遗漏了某个类类型成员的初始化。
        // 此时，这个被遗漏的成员依然会被默认初始化。
        ClassWithExplicitConstructor obj(100);
        std::cout << "内置成员的值: " << obj.built_in_member << std::endl;
    }

    return 0;
}



int main() {
    SetConsoleOutputCP(CP_UTF8);

    return 0;
}
