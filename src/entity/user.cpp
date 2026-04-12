#include "entity/user.h"

// 无参构造函数，可以给一些默认值
User::User() {
    isAdmin = false; // 默认是普通借阅人
}

// 有参构造函数：推荐使用“初始化列表”（冒号后面的部分），效率更高
User::User(const std::string& username, const std::string& password, 
           const std::string& realName, bool isAdmin) 
    : username(username), password(password), realName(realName), isAdmin(isAdmin) {
    // 构造函数体留空即可，上面冒号部分已经完成赋值了
}

// 下面是 Getter 函数的实现
// 注意：头文件里声明加了 const，这里的实现也必须加 const
std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

std::string User::getRealName() const {
    return realName;
}

bool User::getIsAdmin() const {
    return isAdmin;
}

// 下面是 Setter 函数的实现
// 这里用到了 this 指针：因为参数名和成员变量名一样，用 this-> 代表“当前对象自己的变量”
void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setPassword(const std::string& password) {
    this->password = password;
}

void User::setRealName(const std::string& realName) {
    this->realName = realName;
}

void User::setIsAdmin(bool isAdmin) {
    this->isAdmin = isAdmin;
}
