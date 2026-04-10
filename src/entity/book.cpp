#include "entity/book.h"
#include <iostream> // showInfo 需要

// 无参构造函数
Book::Book() 
    : m_id("")
    , m_name("")
    , m_author("")
    , m_publisher("")
    , m_publish_date("")
    , m_total(0)
    , m_available(0)
{
}

// 有参构造函数（完美使用初始化列表）
Book::Book(const std::string& id, const std::string& name, const std::string& author, 
           const std::string& publisher, const std::string& publishDate, uint16_t total)
    : m_id(id)
    , m_name(name)
    , m_author(author)
    , m_publisher(publisher)
    , m_publish_date(publishDate)
    , m_total(total)
    , m_available(total) // 初始可借数等于总册数
{
}

// ================= Getter 实现 =================
std::string Book::getId() const { return m_id; }
std::string Book::getName() const { return m_name; }
std::string Book::getAuthor() const { return m_author; }
std::string Book::getPublisher() const { return m_publisher; }
std::string Book::getPublishDate() const { return m_publish_date; }
uint16_t Book::getTotal() const { return m_total; }
uint16_t Book::getAvailable() const { return m_available; }

// ================= Setter 实现 =================
void Book::setId(const std::string& id) { m_id = id; }
void Book::setName(const std::string& name) { m_name = name; }
void Book::setAuthor(const std::string& author) { m_author = author; }
void Book::setPublisher(const std::string& publisher) { m_publisher = publisher; }
void Book::setPublishDate(const std::string& date) { m_publish_date = date; }

void Book::setTotal(uint16_t total) { m_total = total; }
void Book::setAvailable(uint16_t num) { m_available = num; }

// ================= 业务方法实现 =================
void Book::showInfo() const {
    std::cout << "图书编号: " << m_id 
              << "\n书名: " << m_name 
              << "\n作者: " << m_author
              << "\n出版社: " << m_publisher 
              << "\n出版日期: " << m_publish_date
              << "\n库存/总量: " << static_cast<int>(m_available) << "/" << static_cast<int>(m_total) 
              << std::endl;
}
