#include <stack>
#include <iostream>
using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack():m(0) {

    }

    void push(int x) {
        if (s.empty())
            m = x;
        s.push(x);
        if (x <= m)
            m = x;
    }

    void pop() {
        //判断是否是最小值被弹出了
        if (s.top() == m)
        {
            s.pop();
            //重新寻找最小值

            m = top();//注意当栈中元素只有一个后，pop之后，会拿不到值，使用top要当心
            stack<int> temp;
            while (!s.empty())
            {
                int t = s.top();
                temp.push(t);
                s.pop();
                if (t < m)
                    m = t;
            }
            while (!temp.empty())
            {
                int t = temp.top();
                s.push(t);
                temp.pop();
            }
        }
        else
        {
            s.pop();
        }
    }

    int top() {
        if(!s.empty())
            return s.top();
        else
        {
            return -1;
        }
    }

    int min() {
        return m;
    }
private:
    int m;//存储当前最小值
    stack<int> s;
    
};

/**
方法1：见代码。其中使用栈的top时，要注意，判断栈是否为空。为空时，使用top会报错
方法2：使得每个元素 a 与其相应的最小值 m 时刻保持一一对应。因此我们可以使用一个辅助栈，与元素栈同步插入与删除，用于存储与每个元素对应的最小值。
当一个元素要入栈时，我们取当前辅助栈的栈顶存储的最小值，与当前元素比较得出最小值，将这个最小值插入辅助栈中；
当一个元素要出栈时，我们把辅助栈的栈顶元素也一并弹出；在任意一个时刻，栈内元素的最小值就存储在辅助栈的栈顶元素中。
 */
int main()
{
    MinStack m;
    m.push(2147483646);
    m.push(2147483646);
    m.push(2147483647);
    cout << m.top() << endl;
    m.pop();
    cout << m.min() << endl;
    m.pop();
    cout << m.min() << endl;
    m.pop();
    m.push(2147483647);
    cout << m.top() << endl;
    cout << m.min() << endl;
    m.push(-2147483648);
    cout << m.top() << endl;
    cout << m.min() << endl;
    m.pop();
    cout << m.min() << endl;
    return 0;
}