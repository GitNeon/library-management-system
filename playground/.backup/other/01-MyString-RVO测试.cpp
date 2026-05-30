#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <memory>
#include <set>

using namespace std;

class MyString {
public:
    char* data;
    size_t len;

    // 1. 构造函数
    explicit MyString(const char* str = "") {
        len = strlen(str);
        data = new char[len + 1];
        strcpy(data, str);
        std::cout << "Constructor called: " << data << std::endl;
    }

    // 2. 拷贝构造函数 - Rule of 3 必需
    MyString(const MyString& other) {
        len = other.len;
        data = new char[len + 1];
        strcpy(data, other.data);
        std::cout << "Copy Constructor called: " << data << std::endl;
    }

    // 3. 拷贝赋值运算符 - Rule of 3 必需
    MyString& operator=(const MyString& other) {
        std::cout << "Copy Assignment called: " << other.data << std::endl;
        if (this == &other) return *this; // 自赋值检测

        // 1. 分配新内存
        char* new_data = new char[other.len + 1];
        strcpy(new_data, other.data);

        // 2. 释放旧内存
        delete[] data;

        // 3. 更新指针和长度
        data = new_data;
        len = other.len;

        return *this;
    }

    // 4. 移动构造函数 - Rule of 5 补充
    MyString(MyString&& other) noexcept {
        data = other.data;
        len = other.len;
        other.data = nullptr;
        other.len = 0;
        std::cout << "Move Constructor called" << std::endl;
    }

    // 5. 移动赋值运算符 - Rule of 5 补充
    MyString& operator=(MyString&& other) noexcept {
        std::cout << "Move Assignment called" << std::endl;
        if (this == &other) return *this; // 自赋值检测

        // 释放当前对象的资源
        delete[] data;

        // 窃取 other 的资源
        data = other.data;
        len = other.len;

        // 将 other 置于有效但空的状态
        other.data = nullptr;
        other.len = 0;

        return *this;
    }

    // 6. 析构函数 - Rule of 3 必需
    ~MyString() {
        // 打印时要注意 data 是否为空（移动后可能为空）
        if (data) {
            std::cout << "Destructor called: " << data << std::endl;
            delete[] data;
        } else {
            std::cout << "Destructor called (null)" << std::endl;
        }
    }
};

// ==================== 测试用例：辅助函数 ====================

// 案例 1: 返回局部具名对象 (测试 NRVO)
MyString returnNamedObject() {
    MyString temp("NRVO_Test");
    return temp;
}

// 案例 2: 返回临时对象 (测试 URVO / Copy Elision)
MyString returnTemporary() {
    return MyString("URVO_Test");
}

// 案例 3: 复杂分支逻辑 (测试 RVO 失效，回退到移动语义)
MyString returnConditional(bool flag) {
    MyString s1("OptionA");
    MyString s2("OptionB");
    if (flag)
        return s1;
    else
        return s2;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "========== Test 1: 直接构造 ==========" << std::endl;
    {
        MyString s1("Direct Init");
    } // s1 离开作用域，析构
    std::cout << std::endl;

    std::cout << "========== Test 2: 拷贝初始化 (Lvalue) ==========" << std::endl;
    {
        MyString s1("Source");
        std::cout << "--- Creating s2 from s1 ---" << std::endl;
        MyString s2 = s1; // 调用拷贝构造函数
    } // s2 析构，s1 析构
    std::cout << std::endl;

    std::cout << "========== Test 3: 移动初始化 (Rvalue/std::move) ==========" << std::endl;
    {
        MyString s1("Move_Source");
        std::cout << "--- Creating s2 via std::move(s1) ---" << std::endl;
        MyString s2 = std::move(s1); // 调用移动构造函数
        // 注意：s1 现在处于有效但未定义的状态（data 为 nullptr）
    } // s2 析构，s1 析构
    std::cout << std::endl;

    std::cout << "========== Test 4: NRVO (具名返回值优化) ==========" << std::endl;
    {
        std::cout << "--- Calling returnNamedObject() ---" << std::endl;
        MyString s = returnNamedObject();
        // 预期：只有一次 Constructor，没有 Copy/Move Constructor (开启优化时)
    }
    std::cout << std::endl;

    std::cout << "========== Test 5: URVO (未具名返回值优化) ==========" << std::endl;
    {
        std::cout << "--- Calling returnTemporary() ---" << std::endl;
        MyString s = returnTemporary();
        // 预期：只有一次 Constructor，没有 Copy/Move Constructor (C++17 强制)
    }
    std::cout << std::endl;

    std::cout << "========== Test 6: RVO 失效回退到移动语义 ==========" << std::endl;
    {
        std::cout << "--- Calling returnConditional(true) ---" << std::endl;
        MyString s = returnConditional(true);
    }
    std::cout << std::endl;

    std::cout << "========== Test 7: 赋值运算 (非初始化) ==========" << std::endl;
    {
        MyString s1("Old_Value");
        std::cout << "--- Assigning result of returnTemporary() ---" << std::endl;
        // 这里不是初始化！s1 已经存在。
        // RVO 对赋值无效。
        // 预期：调用 Move Assignment Operator
        s1 = returnTemporary();
    } // s1 析构
    std::cout << std::endl;

    return 0;
}
