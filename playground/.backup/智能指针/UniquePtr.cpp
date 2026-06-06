#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <memory>

template <typename T>
class UniquePtr {
private:
    T* m_ptr;

public:
    explicit UniquePtr(T* ptr = nullptr) : m_ptr(ptr) {}
    ~UniquePtr() { delete m_ptr; }

    // 禁用拷贝
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // 移动构造：合法转移所有权
    UniquePtr(UniquePtr&& other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr; // 转移后原对象置空
    }

    // 移动赋值
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete m_ptr;       // 释放自己现有的资源
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    T* get() const { return m_ptr; }

    // 增加释放所有权的方法
    T* release() {
        T* tmp = m_ptr;
        m_ptr = nullptr;
        return tmp;
    }

    // 重置资源
    void reset(T* ptr = nullptr) {
        if (m_ptr != ptr) {
            delete m_ptr;
            m_ptr = ptr;
        }
    }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    UniquePtr<int> p1(new int(20));
    // UniquePtr<int> p2 = p1; // 编译报错！禁用了拷贝

    UniquePtr<int> p2 = std::move(p1); // 显式移动，p1 变为 nullptr，p2 接管资源
    std::cout << *p2 << std::endl;     // 正常

    return 0;
}
