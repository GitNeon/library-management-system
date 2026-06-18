#include <functional>
#include <iostream>
#include <string>
#include <windows.h>
#include <memory>
#include <typeinfo>

using namespace std;

// 1. 定义对象的结构
struct UserProfile {
    std::string name;
    int age;
    bool isActive;
};

// 2. 在函数中创建并返回
UserProfile createUser() {
    // 在栈上创建局部对象
    UserProfile user;
    user.name = "Alice";
    user.age = 25;
    user.isActive = true;

    return user; // 直接按值返回
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    // 接收返回的对象
    const UserProfile myUser = createUser();

    std::cout << "Name: " << myUser.name << ", Age: " << myUser.age << std::endl;
    return 0;
}
