#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

// 打印 list
template <typename T>
void print_list(const list<T>& lst) {
    cout << "[";
    bool first = true;
    for (const auto& elem : lst) {
        if (!first) cout << ", ";
        cout << elem;
        first = false;
    }
    cout << "]" << endl;
}

// 打印 vector
template <typename T>
void print_vec(const vector<T>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    int ia[] = {1, 5, 34};
    int ia2[] = { 1, 2, 3 };
    int ia3[] = { 6, 13, 21, 29, 38, 55, 67, 89 };

    /**
     * 用各种插入操作 以及 ia2 和 ia3 适当的值修改 ivec 使它拥有序列
     * { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 }
     */
    vector<int> ivec(1, 0);

    // 先放入一个0
    // 或者初始化时只有一个元素0
    // ivec.push_back(0);

    // 放入ia数组中的1,5元素
    ivec.insert(ivec.end(), ia, ia + 2);

    // 第2个位置后插入ia2的全部元素
    ivec.insert(ivec.begin() + 2, ia2, ia2 + 3);

    // 尾部追加一个8
    ivec.push_back(8);

    // 尾部插入
    ivec.insert(ivec.end(), ia3 + 1, ia3 + 3);

    // 找到55
    int* find_val_1 = find(&ia3[0], &ia3[7], 55);
    if (find_val_1 != &ia3[7]) {
        ivec.push_back(*find_val_1); // 找到了，安全地添加到 vector 中
    } else {
        // 没找到
        cout << "55 not found!" << endl;
    }

    ivec.push_back(ia3[7]);

    print_vec(ivec);

    return 0;
}
