#include "entity/borrow_record.h"

// 无参构造
BorrowRecord::BorrowRecord() {
    // 默认都是空字符串，不需要额外写，std::string 默认就是空的
}

// 有参构造（使用初始化列表）
BorrowRecord::BorrowRecord(const std::string& bookId, const std::string& bookName, 
                           const std::string& userName, const std::string& borrowDate) 
    : bookId(bookId), 
      bookName(bookName), 
      userName(userName), 
      borrowDate(borrowDate) {
    // 注意：这里没有初始化 returnDate，它会自动变成空字符串 ""，代表还没还书
}

// ==================== Getter 实现 ====================
std::string BorrowRecord::getBookId() const {
    return bookId;
}

std::string BorrowRecord::getBookName() const {
    return bookName;
}

std::string BorrowRecord::getUserName() const {
    return userName;
}

std::string BorrowRecord::getBorrowDate() const {
    return borrowDate;
}

std::string BorrowRecord::getReturnDate() const {
    return returnDate;
}

// ==================== Setter 实现 ====================
void BorrowRecord::setReturnDate(const std::string& returnDate) {
    this->returnDate = returnDate; // this-> 区分同名的成员变量和参数
}

// ==================== 业务方法实现 ====================
// 如果还书日期是空的，说明没还；如果不是空的，说明还了
bool BorrowRecord::isReturned() const {
    return !returnDate.empty(); 
}
