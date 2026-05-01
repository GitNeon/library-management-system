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

/**
 * 请写一个程序 使它接受下列定义
 * int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
 * list<int> ilist( ia, ia+11 );
 * 用单个 iterator 形式的 erase()删除 ilist 中所有奇数位置的元素
 */
// int main() {
//     //           0  1  2  3  4  5  6  7   8   9   10
//     int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
//     list<int> ilist(ia, ia + 11);

//     list<int>::iterator iter = ilist.begin();
//     int index = 0; // 用于记录当前位置（下标从0开始）

//     while (iter != ilist.end()) {
//         // 奇数位置：如果下标从0开始，奇数位置的下标是 1, 3, 5...
//         if (index % 2 != 0) {
//             // 关键点1：接收 erase 返回的新迭代器，解决迭代器失效问题
//             iter = ilist.erase(iter);
//             // 关键点2：删除元素后，后面的元素会往前挤，所以当前位置 index 不变
//         } else {
//             // 没有删除时，迭代器后移，位置后移
//             iter++;
//         }
//         index++;
//     }

//     cout << "result list = ";
//     print_list(ilist);
//     cout << endl;

//     return 0;
// }


// 方式2，不依赖index变量
int main() {
    int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
    list<int> ilist(ia, ia + 11);

    list<int>::iterator iter = ilist.begin();

    while (iter != ilist.end()) {
        // 每次进到这里，iter 都指向“偶数位置”（第0、2、4...个）
        // 我们先把它往后挪一步，让它指向“奇数位置”（第1、3、5...个）
        iter++;

        if (iter != ilist.end()) {
            // 此时 iter 指向奇数位置，直接删除
            // erase 会返回下一个元素的迭代器（也就是下一个偶数位置）
            iter = ilist.erase(iter);
        }
    }

    cout << "result list = [";
    print_list(ilist);
    cout << "]" << endl;

    return 0;
}
