#include <vector>
#include <iostream>

using namespace std;

class IStack {

public:
    IStack(int capacity): _top(0), _stack(capacity) {};

    int size();

    bool pop(int &value);
    bool push(int value);

    bool full();
    bool isEmpty();

    void display();

private:
    int _top;   // 当前栈顶索引,_top的当前值反映了栈中元素的个数
    vector<int> _stack;
};

inline int IStack::size() {
    return _top;
};

inline bool IStack::isEmpty() {
    /**
     *  return _top ? false : true; （下乘：逻辑绕弯，过度使用三元运算符）
        return static_cast<bool>(_top); （中乘：符合规范，意图明确，但略显啰嗦）
        return !_top; 或 return _top == 0; （上乘：最符合直觉，极简，没有多余符号）
     */
    return static_cast<bool>(_top);
};

inline bool IStack::full() {
    return static_cast<size_t>(_top) == _stack.size() - 1;
}

bool IStack::pop(int &top_value){
    if(isEmpty()) {
        return false;
    }

    top_value = _stack[--_top];
    std::cout << "iStack::pop(): " << top_value << endl;

    return true;
}

bool IStack::push(int value) {
    if (full()) {
        return false;
    }

    cout << "iStack::push( " << value << " )\n";

    _stack[ _top++ ] = value;
    return true;
}

void IStack::display() {
 if ( !size() ){
    cout << "( 0 )\n"; return;
 }

 cout << "(size =  " << size() << " )( bot: ";

 for ( int ix = 0; ix < _top; ++ix ) {
     cout << _stack[ ix ] << " ";
 }

 cout << " :top )\n";
}

int main(){
    IStack stack( 32 );

    stack.display();
    for ( int ix = 1; ix < 51; ++ix ) {
        if ( ix % 2 == 0 ) {
            stack.push( ix );
        }

        if ( ix % 5 == 0 ) {
            stack.display();
        }

        if ( ix % 10 == 0) {
            int dummy;
            stack.pop( dummy ); stack.pop( dummy );
            stack.display();
        }
    }
}
