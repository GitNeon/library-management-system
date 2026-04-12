#ifndef BORROW_RECORED_H
#define BORROW_RECORED_H

#include <string>

class BorrowRecord {
private:
    std::string bookId;
    std::string bookName;
    std::string userName;       // 借阅人姓名
    std::string borrowDate;     // 借阅日期
    std::string returnDate;     // 归还日期

public:
    BorrowRecord();

    BorrowRecord(const std::string& bookId, const std::string& bookName, 
                 const std::string& userName, const std::string& borrowDate);

    // ==================== Getter 方法 (加 const) ====================
    std::string getBookId() const;
    std::string getBookName() const;
    std::string getUserName() const;
    std::string getBorrowDate() const;
    std::string getReturnDate() const; // 新增：获取还书日期

    // ==================== Setter 方法 (用 const 引用) ====================
    // 一般借书记录生成后，书名、借阅人是不会改的，最常用的是修改还书日期
    void setReturnDate(const std::string& returnDate); // 新增：设置还书日期（还书时调用）

    // ==================== 业务方法 ====================
    // 判断这本书有没有还回来
    bool isReturned() const;
};

#endif