#include <iostream>
#include <string>
#include <cctype>

using namespace std;

/**
 * find_first_of():查找与被搜索字符串中任意一个字符相匹配的第一次出现,并返回它的索引位置
 * find_first_not_of(): 查找第一个不与要搜索字符串的任意字符相匹配的字符
 */
int main() {
    string str = "ab2c3d7R4E6";
    string digits = "0123456789";

    cout << "orginal str = " << str << endl;

    // 查找所有数字
    string::size_type pos = 0;

    while ((pos = str.find_first_of(digits, pos)) != std::string::npos) {
        cout << "in position [" << pos << "], find number: " << str[pos] << endl;
        ++pos;
    }

    cout << "--------------------" << endl;

    // 查找所有字母
    pos = 0;
    while ((pos = str.find_first_not_of(digits, pos)) != std::string::npos) {
        if (isalpha(str[pos])) {  // 确保是字母字符
            cout << "in position [" << pos << "], find letter: " << str[pos] << endl;
        }
        ++pos;
    }



    return 0;
}
