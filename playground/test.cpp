#include <vector>
#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>

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

vector<string> getFileContent() {
    string fileName;
    cout << "please enter file name: ";
    cin >> fileName;

    ifstream infile(fileName);

    if (!infile.is_open()) {
        cout << "Failed to open file: " << fileName << endl;
        exit(-1);
    }

    vector<string> lines;

    string line;
    short line_num = 0;
    while (getline(infile, line)) {
        cout << "read line: " << line << '\n';
        lines.push_back(line);
        line_num++;
    }

    cout << "number of lines = " << line_num << endl;

    infile.close();
    return lines;
}

// 单词信息结构体
struct WordInfo {
    string word;          // 单词内容
    int line_number;      // 所在行号（从0开始）
    int word_col_pos;     // 单词在行中的起始列位置（从0开始）
};

// 将读到的文本内容进行单词分割
vector<WordInfo> separate_words(const vector<string>& text_vec) {
    vector<WordInfo> result;

    for (int line_number = 0; line_number < static_cast<int>(text_vec.size()); ++line_number) {
        string line_text = text_vec[line_number];
        string::size_type word_start_pos = 0;

        while (word_start_pos < line_text.size()) {
            // 跳过连续空格
            if (line_text[word_start_pos] == ' ') {
                ++word_start_pos;
                continue;
            }

            // 找到下一个空格作为单词结束位置
            string::size_type word_end_pos = line_text.find_first_of(' ', word_start_pos);

            // 提取单词
            string word;
            if (word_end_pos == string::npos) {
                word = line_text.substr(word_start_pos);
            } else {
                word = line_text.substr(word_start_pos, word_end_pos - word_start_pos);
            }

            // 存入结果
            result.push_back({word, line_number, static_cast<int>(word_start_pos)});

            // 移动到下一个单词起点
            if (word_end_pos == string::npos) {
                break;
            }
            word_start_pos = word_end_pos + 1;
        }
    }

    return result;
}

int main() {

    vector<string> text_vec = getFileContent();

    vector<WordInfo> words = separate_words(text_vec);

    // 输出所有单词信息
    cout << "\n--- Separate Words Result ---" << endl;
    cout << "Total words: " << words.size() << endl;
    for (const auto& w : words) {
        cout << "word: \"" << w.word
             << "\", line: " << w.line_number
             << ", col: " << w.word_col_pos
             << endl;
    }

    return 0;
}
