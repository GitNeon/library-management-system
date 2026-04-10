#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <cstdint>

class Book {
private:
    std::string m_id;                       // 图书编号（唯一）
    std::string m_name;                     // 书名
    std::string m_author;                   // 作者
    std::string m_publisher;                // 出版社
    std::string m_publish_date;             // 出版日期 
    uint16_t m_total;                       // 总册数，MAX = 65536
    uint16_t m_available;                   // 可借册数，MAX = 65536

public:
    Book();
    Book(const std::string& id, const std::string& name, const std::string& author, 
         const std::string& publisher, const std::string& publishDate, uint16_t total);
    ~Book() = default; // 显式声明使用默认析构函数（C++11规范）

    // ================= Getter 方法 =================
    // 对于不修改对象状态的函数，必须在末尾加 const
    std::string getId() const;
    std::string getName() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    std::string getPublishDate() const;
    uint16_t getTotal() const;
    uint16_t getAvailable() const;

    // ================= Setter 方法 =================
    // 字符串参数使用 const std::string& 避免深拷贝开销
    void setId(const std::string& id);
    void setName(const std::string& name);
    void setAuthor(const std::string& author);
    void setPublisher(const std::string& publisher);
    void setPublishDate(const std::string& date);
    
    // 基本数据类型(int, uint16_t等)直接按值传递，比传引用效率更高
    void setTotal(uint16_t total);
    void setAvailable(uint16_t num);

    // ================= 业务方法 =================
    // 同样属于不修改对象逻辑状态的方法，加 const
    void showInfo() const;
};

#endif