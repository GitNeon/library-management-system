#include <iostream>
#include <string>

#ifdef _WIN32
#define NOMINMAX // 防止 windows.h 定义 max/min 宏，避免与标准库冲突
#include <windows.h>
#endif


int main() {
#ifdef _WIN32
    SetConsoleCP(65001);       // 设置控制台输入编码为 UTF-8
    SetConsoleOutputCP(65001); // 设置控制台输出编码为 UTF-8
#endif
    
    std::string word;

    while (std::cin >> word) {
        std::cout << "word read is:" << word << '\n';
    }
    
    std::cout << "ok: nor more word to read! \n";

    return 0;
}