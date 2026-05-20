#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <memory>
#include <set>

using namespace std;

/*
 * Message 和 Folder 拷贝控制示例：
 * 这个示例的核心难点在于：如何维护两个类之间的双向关联关系，并保证在对象拷贝、赋值和销毁时，这种关联关系始终一致，不会出现悬垂指针或重复关联。
 *
 * 一、 设计思路
    1. 核心需求
    一个 Message 可以存在于多个 Folder 中。
    一个 Folder 可以包含多个 Message。
    这是一种多对多的关系。
    2. 数据结构选择
    由于一个 Message 或 Folder 的地址是唯一的，我们使用指针集合来维护这种关系。
    Message 中有一个 std::set<Folder*>，保存指向包含该消息的 Folder 的指针。
    Folder 中有一个 std::set<Message*>，保存指向该文件夹内 Message 的指针。
    3. 拷贝控制的挑战（核心考点）
    当我们拷贝一个 Message 时，不仅要拷贝消息的文本内容，还必须拷贝它的关联关系（即新 Message 也要出现在原来那些 Folder 中）。

    拷贝构造：创建新对象，并将新对象添加到原有 Folder 中。
    析构：对象销毁前，必须从所有包含它的 Folder 中将自己移除，否则 Folder 中就会出现悬垂指针。
    拷贝赋值：最复杂。将左侧对象从其原有的 Folder 中移除，更新内容，再将左侧对象添加到右侧对象所在的 Folder 中。必须考虑自赋值和异常安全（通常采用先拷贝右侧状态，再销毁左侧状态的拷贝并交换技巧，或手动按安全顺序操作）。
    4. 辅助函数
    由于 Message 和 Folder 互相需要修改对方的私有成员（set），我们需要将它们互设为友元，并设计私有的工具函数：

    Message::add_to_Folders(const Message&)：将本消息添加到参数 m 所在的所有 Folder 中。
    Message::remove_from_Folders()：将本消息从其所在的所有 Folder 中移除。
    Folder 类也需要类似的 addMsg 和 remMsg。

  二、启发
    Message 和 Folder 案例的本质，是教你当你的类跨越了纯粹的值语义，带有网络拓扑或关联状态时，如何用 C++ 的拷贝控制机制来维持这个世界的物理法则不崩塌。
 */

// ====================== 1. 关键：前向声明 ======================
class Folder;
class Message;

// 交换函数声明
void swap(Folder& f1, Folder& f2) noexcept;
void swap(Message& m1, Message& m2) noexcept;



// ====================== 2. Folder 类声明（只有声明，无函数体） ======================
class Folder {
    friend class Message;
    friend void swap(Folder& f1, Folder& f2) noexcept;

public:
    Folder() = default;
    Folder(const Folder&);          // 拷贝构造
    Folder& operator=(const Folder&);// 赋值
    ~Folder();                     // 析构

    void print(const string& name) const;

private:
    set<Message*> _messages;

    void addMsg(Message* m);
    void remMsg(Message* m);
    void add_to_Messages(const Folder& f);
    void remove_from_Messages();
};

// ====================== 3. Message 类声明（只有声明，无函数体） ======================
class Message {
    friend class Folder;
    friend void swap(Message& m1, Message& m2) noexcept;

public:
    explicit Message(const string& msg = "");
    Message(const Message& m);
    Message& operator=(const Message& rhs);
    ~Message();

    void save(Folder& folder);
    void remove(Folder& f);
    void print() const;

private:
    string _msg_content;
    set<Folder*> _folders;

    void remove_from_folders();
    void add_to_folders(const Message& m);
};



// ====================== 4. 最后：统一实现所有函数 ======================
// Folder 函数实现
void Folder::addMsg(Message* m) {
    _messages.insert(m);
}

void Folder::remMsg(Message* m) {
    _messages.erase(m);
}

void Folder::add_to_Messages(const Folder& f) {
    for (auto msg : f._messages) {
        msg->_folders.insert(this);
    }
}

void Folder::remove_from_Messages() {
    for (auto msg : _messages) {
        msg->_folders.erase(this);
    }
}

Folder::~Folder() {
    remove_from_Messages();
}

Folder::Folder(const Folder& f) : _messages(f._messages) {
    add_to_Messages(f);
}

Folder& Folder::operator=(const Folder& rhs) {
    remove_from_Messages();
    _messages = rhs._messages;
    add_to_Messages(rhs);
    return *this;
}

void Folder::print(const string& name) const {
    std::cout << "Folder [" << name << "] has " << _messages.size() << " messages.\n";
}

void swap(Folder& f1, Folder& f2) noexcept {
    using std::swap;
    swap(f1._messages, f2._messages);
}



// Message 函数实现
Message::Message(const string& msg) : _msg_content(msg) {}

Message::~Message() {
    remove_from_folders();
}

void Message::remove_from_folders() {
    for (Folder* f : _folders) {
        f->remMsg(this);
    }
}

void Message::add_to_folders(const Message& m) {
    for (Folder* f : m._folders) {
        f->addMsg(this);
    }
}

Message::Message(const Message& m)
    : _msg_content(m._msg_content), _folders(m._folders) {
    add_to_folders(m);
}

Message& Message::operator=(const Message& rhs) {
    remove_from_folders();
    _msg_content = rhs._msg_content;
    _folders = rhs._folders;
    add_to_folders(rhs);
    return *this;
}

void Message::save(Folder& folder) {
    folder.addMsg(this);
    _folders.insert(&folder);
}

void Message::remove(Folder& f) {
    _folders.erase(&f);
    f.remMsg(this);
}

void Message::print() const {
    cout << "Message: [" << _msg_content << "] in " << _folders.size() << " folders.\n";
}

void swap(Message& m1, Message& m2) noexcept {
    using std::swap;
    swap(m1._msg_content, m2._msg_content);
    swap(m1._folders, m2._folders);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "[========== main function running ==========]" << "\n\n";

    Folder f1, f2;
    Message m1("Hello");
    Message m2("World");

    // 1. 测试 save
    m1.save(f1); // m1 存入 f1
    m1.save(f2); // m1 存入 f2
    m2.save(f1); // m2 存入 f1

    f1.print("f1"); // 期望: 2 messages
    f2.print("f2"); // 期望: 1 message
    m1.print();     // 期望: in 2 folders
    m2.print();     // 期望: in 1 folders

    std::cout << "--------------------\n";

    // 2. 测试拷贝构造
    Message m3 = m1; // m3 应该出现在 f1 和 f2 中
    f1.print("f1"); // 期望: 3 messages
    f2.print("f2"); // 期望: 2 messages

    std::cout << "--------------------\n";

    // 3. 测试拷贝赋值
    m2 = m1; // m2 原本在 f1 中，赋值后应该从 f1 移除，并出现在 f1, f2 中（和 m1 一样）
    f1.print("f1"); // 期望: 3 messages (m1, m3, 新m2)
    f2.print("f2"); // 期望: 3 messages (m1, m3, 新m2)

    std::cout << "--------------------\n";

    // 4. 测试析构 (离开作用域)
    {
        Message m4("Temp");
        m4.save(f1);
        f1.print("f1"); // 期望: 4 messages
    } // m4 析构
    f1.print("f1");     // 期望: 3 messages (m4 被自动移除，无悬垂指针)

    std::cout << "\n[========== main function ending ==========]" << "\n";

    return 0;
}
