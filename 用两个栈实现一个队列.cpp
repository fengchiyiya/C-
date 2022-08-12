#include<stack>
#include<iostream>
using namespace std;
class CQueue {
public:
    CQueue() {

    }

    void appendTail(int value) {//输入栈,尾插法对于输入栈就是push
            q2.push(value);
    }

    int deleteHead() {
        if (q1.empty())
        {
            if(q2.empty())//q1,q2空了，代表之前没有尾插
                return -1;
            while (!q2.empty())//输出栈为空，当前输入栈的数据传递到输出栈
            {
                int q = q2.top();
                q1.push(q);
                q2.pop();
            }//q2空了
            int d = q1.top();
            q1.pop();
            return d;
        }
        else
        {
            int d = q1.top();
            q1.pop();
            return d;
        }
    }
private:
    stack<int> q1;//输出
    stack<int> q2;//输入
};

/**
注意，当容器尺寸改变时，不能用size()作为判断条件
 */
int main()
{
    
    CQueue c;
    c.appendTail(4);
    c.appendTail(3);
    c.appendTail(2);
    c.appendTail(1);

    int d=c.deleteHead();
    cout << "d = " << d << endl;    
    d = c.deleteHead();
    cout << "d = " << d << endl;
    c.appendTail(5);
    return 0;
}