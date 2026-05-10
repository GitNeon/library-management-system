#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

class HasDefault {
public:
    int val;
    HasDefault() : val(20) {
        std::cout << "HasDefault 默认构造函数被调用, val = " << val << std::endl;
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // 情况 1
    // 当你定义一个数组并提供了部分初始值时，剩下的元素不会保持未初始化状态，而是会被值初始化（内置类型置零，类类型调用默认构造函数）
    {
        std::cout << "--- 情况 1：数组初始值数量不足 ---" << std::endl;
        int arr[5] = {10, 20};
        std::cout << "arr[0]=" << arr[0] << ", arr[2]=" << arr[2] << std::endl;

        HasDefault classArr[3] = { HasDefault() };
    }

    // 情况 2
    // 局部变量默认是默认初始化的（垃圾值），但如果是 static 局部变量，且未提供初始值，它会被值初始化。因为静态变量存在于程序整个生命周期，必须保证有确定的初始状态。
    {
        std::cout << "\n--- 情况 2：局部静态变量 ---" << std::endl;
        int normal_int;
        static int static_int;

        std::cout << "普通局部变量 normal_int 的值(未定义): " << normal_int << std::endl;
        std::cout << "局部静态变量 static_int 的值(值初始化): " << static_int << std::endl;
    }

    // 情况 3
    // 这是最显式的值初始化方式。T() 告诉编译器：“给我创建一个 T 类型的临时对象，并把它值初始化”。vector 只提供大小不提供初始值时，内部元素也是值初始化。
    {
        std::cout << "\n--- 情况 3：显式请求值初始化 T() 及 vector ---" << std::endl;
        int zero_val = int();
        std::cout << "int() 的值: " << zero_val << std::endl;

        std::string empty_str = std::string();
        std::cout << "string() 的内容和长度: \"" << empty_str << "\", " << empty_str.length() << std::endl;

        std::vector<int> vec(5);
        std::cout << "vector<int>(5) 的内容: ";
        for (int v : vec) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
