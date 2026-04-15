#include <iostream>

#ifdef _WIN32
#define NOMINMAX // 防止 windows.h 定义 max/min 宏，避免与标准库冲突
#include <windows.h>
#endif

int main() {
#ifdef _WIN32
    SetConsoleCP(65001);       // 设置控制台输入编码为 UTF-8
    SetConsoleOutputCP(65001); // 设置控制台输出编码为 UTF-8
#endif
    std::cout << "Hello, World!" << std::endl;

    std::cout << "使用预设宏变量: __FILE__ = " << __FILE__ << "\n"; 

    std::cout << "使用预设宏变量: __DATE__ = " << __DATE__ << "\n"; 

    std::cout << "使用预设宏变量: __TIME__ = " << __TIME__ << "\n"; 

    return 0;
}