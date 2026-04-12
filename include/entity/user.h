#ifndef USER_H
#define USER_H

#include <string>

class User {
private:
    std::string username; // 登录账号
    std::string password; // 密码
    std::string realName; // 真实姓名（借阅人用）
    bool isAdmin;         // 是否为管理员（true表示管理员，false表示借阅人）

public:
    // 无参构造函数
    User();
    
    // 注意2：参数使用 const std::string& （常量引用），提高效率
    User(const std::string& username, const std::string& password, 
         const std::string& realName, bool isAdmin);

    ~User() = default;

    // 注意3：获取数据的函数后面加 const，表示“我只读取，不修改数据”
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getRealName() const;
    bool getIsAdmin() const;

    // 修改数据的函数（Setter）不需要加 const，参数也用 const 引用
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setRealName(const std::string& realName);
    void setIsAdmin(bool isAdmin);
};

#endif
