#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

class IntArray {
public:
    explicit IntArray(int sz = DefaultArraySize);

    IntArray(int *array, int array_size);

    IntArray(const IntArray &rhs);

    // 析构函数
    ~IntArray() {
        delete [] ia;
    }

    int size() const {
        return _size;
    }

    int& operator[](int index);

private:
    int _size;
    int *ia;    // 存储new表达式返回的地址

    static const int DefaultArraySize = 12;
};

// 在类外定义第一个构造函数
IntArray::IntArray(int sz) {
    _size = sz;
    ia = new int[_size];

    for (int i = 0; i < _size; ++i) {
        ia[i] = 0;
    }
    
}

// 定义第二个构造函数
IntArray::IntArray(int *array, int sz) {
    _size = sz;
    ia = new int[_size];

    for (int i = 0; i < _size; ++i) {
        ia[i] = array[i];
    }
    
}

// 第三个构造函数，拷贝构造函数
IntArray::IntArray(const IntArray &rhs) {
    _size = rhs._size;
    ia = new int[_size];

    for (int i = 0; i < _size; ++i) {
        ia[i] = rhs.ia[i];
    }
}

int& IntArray::operator[](int index) {
    assert(index > 0 && index < size());
    return ia[index];
}

int main() {

    IntArray Iarray[10];

    return 0;
}