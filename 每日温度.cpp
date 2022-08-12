// 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，
// 下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。
#include <vector>
#include <stack>
#include <iostream>
using namespace std;
/*单调栈  单调栈问题一般用来解决找左边、右边满足条件的最近值
本题应该是从栈顶到栈底单调递增的栈
重点是找到右边的最近的更高点，有点类似接雨水
数组的最后一个值一定为0.
草，知道思路，不知道怎么写单调栈
好好学习一下，如何写单调栈
入栈放在while循环外，出栈放在循环内
*/
class Solution
{
public:
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        int n = temperatures.size();
        vector<int> ans(n);
        stack<int> stk;
        for (int i = 0; i < n; i++)
        {
            // s.top记录的是前面的序列
            // 注意中间是与，不然空栈也可能会参与循环
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()])
            {
                ans[stk.top()] = i - stk.top();
                stk.pop();
            }
            // push操作单独放在while外面，省事
            // temperatures[i]<=temperatures[s.top]入栈，此时i>s.top()
            stk.push(i);
        }
        return ans;
    }
};