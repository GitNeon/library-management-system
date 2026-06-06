#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <memory>

/**
 * AutoPtr 的核心思想是 RAII：在构造时获取资源，在析构时释放资源。
 * @tparam T 泛型
 */
template <typename T>
class AutoPtr {
private:
    T* m_ptr;

public:
    // 构造，获取所有权
    explicit AutoPtr(T* ptr = nullptr) : m_ptr(ptr) {}

    // 析构，释放所有权
    ~AutoPtr() {
        delete m_ptr;
    }

    // 拷贝构造，由于C++ 98版本没有移动语义,智能粗暴的夺取所有权
    AutoPtr(AutoPtr& other) {
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
    }

    // 拷贝赋值
    AutoPtr& operator=(AutoPtr& other) {
        if (this != &other) {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    // 重载操作符，像使用原生指针一样
    T& operator*() const {
        return *m_ptr;
    }
    T* operator->() const {
        return m_ptr;
    }
    // 获取原生指针
    T* get() const { return m_ptr; }
};

int main() {
    SetConsoleOutputCP(CP_UTF8);

    AutoPtr<int> p1(new int(10));
    AutoPtr<int> p2(new int(11));

    // 此时 p1 的所有权转移给了 p2，p1 变成了 nullptr
    // 触发拷贝构造
    AutoPtr<int> p3 = p1;

    // 触发拷贝赋值
    // p2 = p1;

    // 缺陷：如果两个 AutoPtr 指向同一个对象，或者原 AutoPtr 被剥夺所有权后仍被使用，会导致悬挂指针和多次释放。
    // std::cout << *p1 << std::endl; // 崩溃！p1 内部指针已经是 nullptr
    std::cout << *p2 << std::endl;   // 正常

    return 0;
}
