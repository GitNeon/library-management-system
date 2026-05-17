#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <memory>

using namespace std;

class StrBlob {
public:
    typedef vector<string>::size_type vec_size_t;

    StrBlob();

    StrBlob(initializer_list<string> ilist);

    vec_size_t size() const {
        return data->size();
    };

    bool empty() {
        return data->empty();
    };

    void push_back(const string &str) {
        data->push_back(str);
    };

    void pop_back();

    string& front();

    string& back();

    // 重载输出运算符，方便测试（声明为友元）
    friend ostream& operator<<(ostream& os, const StrBlob& blob);

private:
    shared_ptr<vector<string>> data;
    void check(vec_size_t index, const string &msg) const;
};

StrBlob::StrBlob() : data(make_shared<vector<string>>()){};

StrBlob::StrBlob(initializer_list<string> ilist) : data(make_shared<vector<string>>(ilist)){};

void StrBlob::check(vec_size_t index, const string &msg) const {
    if (index >= data->size()) {
        throw out_of_range(msg);
    }
};

string& StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back() {
    check(0, "back on empty StrBlob");
    data->pop_back();
}

// 友元函数实现
ostream& operator<<(ostream& os, const StrBlob& blob) {
    os << "[";
    if (blob.data) {
        for (size_t i = 0; i < blob.data->size(); ++i) {
            os << (*blob.data)[i] << (i == blob.data->size() - 1 ? "" : ", ");
        }
    }
    os << "]";
    return os;
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::cout << "TEST OUTPUT" << "\n";

    // b1 拥有数据
    StrBlob b1 = {"hello", "world"};
    cout << "b1: " << b1 << endl; // 输出: b1: [hello, world]

    // b2 共享 b1 的数据（浅拷贝，引用计数从 1 变为 2）
    StrBlob b2 = b1;

    // 修改 b2，实际上修改的是它们共同指向的 vector
    b2.push_back("C++");

    // b1 也能看到变化！
    cout << "b1: " << b1 << endl; // 输出: b1: [hello, world, C++]
    cout << "b2: " << b2 << endl; // 输出: b2: [hello, world, C++]

    // b3 重新赋值，b3 指向新数据
    StrBlob b3;
    b3 = b1;

    // b1 被销毁，但底层数据不释放，因为 b2 和 b3 还在使用（引用计数为 2）
    // 直到 b2 和 b3 也都销毁，底层数据才会自动释放
    return 0;
}
