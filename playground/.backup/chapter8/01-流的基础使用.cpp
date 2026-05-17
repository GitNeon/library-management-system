#include <iostream>
#include <string>
#include <windows.h>

// 返回流的引用，可以链式使用该流
std::istream& readAndPrint(std::istream& input) {
    std::string content = "";

    while (input >> content) {
        std::cout << "the content = " << content << " ";
    }

    std::cout << std::endl;

    input.clear();

    return input;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "请输入一些文字（按 Ctrl+D 或 Ctrl+Z 结束第一次输入）：" << std::endl;

    readAndPrint(std::cin);

    return 0;
}
