#include <iostream>
#include <string>
#include <windows.h>
#include <memory>
#include <cstdlib>

using namespace std;

// 重载全局的operator new
void* operator new(size_t size) {
    std::cout << "自定义 operator new 被调用，请求分配字节数: " << size << std::endl;

    // 标准 new 要求即使申请 0 字节也要返回有效的非空指针
    if (size == 0) {
        size = 1;
    }

    void* ptr = malloc(size);

    // C++ 标准：如果内存分配失败，new 应该抛出 std::bad_alloc 异常
    // 而 malloc 失败时返回 nullptr
    if (ptr == nullptr) {
        cout << "malloc failed" << endl;
        throw std::bad_alloc();
    }

    return ptr;
}

void operator delete(void* ptr) noexcept {
    std::cout << "自定义 operator delete 被调用，释放内存地址: " << ptr << std::endl;
    free(ptr);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "--- 开始分配 int 类型的内存 ---" << std::endl;
    int* p = new int(42);
    std::cout << "分配成功，*p = " << *p << std::endl;

    std::cout << "\n--- 开始释放 int 类型的内存 ---" << std::endl;
    delete p;

    std::cout << "\n--- 开始分配自定义类的内存 ---" << std::endl;
    struct MyClass { double a; char b; };
    MyClass* pc = new MyClass{3.14, 'X'};
    std::cout << "分配成功，pc->a = " << pc->a << ", pc->b = " << pc->b << std::endl;
    
    std::cout << "\n--- 开始释放自定义类的内存 ---" << std::endl;
    delete pc;

    return 0;
}
