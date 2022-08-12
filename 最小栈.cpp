// 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
// 实现 MinStack 类:
// MinStack() 初始化堆栈对象。
// void push(int val) 将元素val推入堆栈。
// void pop() 删除堆栈顶部的元素。
// int top() 获取堆栈顶部的元素。
// int getMin() 获取堆栈中的最小元素。
#include <stack>
using namespace std;
//发现stack内部是用deque实现的;同时注意top时，需要考虑容器是否为空
/*利用辅助栈将当前的最小值存储起来
将该题和利用两个栈翻转的某一题混淆了*/
class MinStack
{
public:
    stack<int> minStack; //存最小值的,栈顶最小
    stack<int> mStack;   //正常存放元素的
    int minVal;//这个可以不用
    MinStack()
    {
    }

    void push(int val)
    {
        if(mStack.empty())
        {
            minVal=val;
        }
        mStack.push(val);
        if(minVal>=val)
            minVal=val;
        minStack.push(minVal);
    }

    void pop()
    {
        if(mStack.empty())
            return;
        mStack.pop();
        minStack.pop();
        if(!minStack.empty())
            if(minVal<minStack.top())
                minVal=minStack.top();
    }

    int top()
    {
        if(mStack.empty())
            return -1;
        return mStack.top();
    }

    int getMin()
    {
        return minVal;
    }
};
class MinStack
{
public:
    stack<int> minStack; //存最小值的,栈顶最小
    stack<int> mStack;   //正常存放元素的
    MinStack()
    {
        minStack.push(INT_MAX);
    }

    void push(int val)
    {
        mStack.push(val);
        if(minStack.top()>=val)
            minStack.push(val);
        else
            minStack.push(minStack.top());
    }

    void pop()
    {
        if(mStack.empty())
            return;
        mStack.pop();
        minStack.pop();
    }

    int top()
    {
        if(mStack.empty())
            return -1;
        return mStack.top();
    }

    int getMin()
    {
        return minStack.top();
    }
};