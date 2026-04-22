#include <iostream>
#include <fstream>
#include <cstring>

/**
 * 自定义MyString实现
 */
class MyString {
public:
    // 一组重载的构造函数
    // 提供自动初始化功能
    // String str1;
    MyString();
    // String str2("this is mystring")
    MyString(const char* str);
    // String str3(str2);
    MyString(const MyString& str);

    // 析构函数
    ~MyString();

    // 一组重载的赋值操作符
    // str1 = str2
    MyString& operator=(const MyString& str);
    // str3 = "a string literal"
    MyString& operator=(const char* str);

    // 一组重载的等于操作符
    // str1 == str2;
    // str3 == a string literal ;
    bool operator==( const MyString& str);
    bool operator==( const char* str);

    // 重载下标操作符
    char& operator[](int index);

    // 成员访问函数
    int size() {
        return _size;
    }

    char* c_str() {
        return _string;
    }

private:
    int _size;
    char *_string;
};

// 实现两个字符串对象的比较，str1 == str2
inline bool MyString::operator==(const MyString &rhs) {
    if (_size != rhs._size) {
        return false;
    }
    return strcmp(_string, rhs._string) ? false : true;
}

int main() {

}
