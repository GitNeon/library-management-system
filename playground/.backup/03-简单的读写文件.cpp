#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

    string word;

    // 创建一个名叫 outFile 的文件输出流对象，并且让它自动打开文件 out_file
    ofstream outFile("out_file.txt");

    ifstream inFile("in_file.txt");

    while (inFile >> word) {
        outFile << word << '\n';
    }

    return 0;
}