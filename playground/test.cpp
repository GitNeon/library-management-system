#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template <class elemType>
class example1 {
    example1(elemType min, elemType max);

    example1(const elemType *array, int size);

    elemType& operator[](int index);

    bool operator==(const example1&) const;
};

int main() {


    return 0;
}