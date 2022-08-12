//给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。
#include <string>
#include <stack>
#include <vector>
#include <iostream>
using namespace std;
//一般最长，最短，最多这种问题可以考虑动态规划方法
//动态规划：想到这个方法，但是思路错了 应该是一维的动态规划
// dp[i]表示以下标i字符结尾的最长有效括号的长度，即i必须处于有效位置
//因此我们可以知道以'('结尾的子串的dp值必定为0，因为不是合法子串，
//情况1：如果dp[i]=')',并且dp[i-1]='('则配对，dp[i]=dp[i-2]+2
//情况2：如果dp[i]=')',并且dp[i-1]=')',判断s-dp[i-1]-1是否为'(',是的话，则配对又成功
// dp[i]=dp[i-1]+2,注意i-dp[i-1]-1和i组成的有效括号对，这将是一段独立的有效的括号序列
//需要加上dp[i-dp[i-1]-2]的部分
// class Solution
// {
// public:
//     int longestValidParentheses(string s)
//     {
//         int maxSize = 0;
//         int size = s.size();
//         vector<int> dp(size, 0);
//         for (size_t i = 1; i < size; ++i) //直接从1，开始就行
//         {
//             if (s[i] == '(')
//                 dp[i] == 0;
//             if (s[i] == ')')
//                 if (s[i - 1] == '(')
//                 {
//                     dp[i] = (i > 2 ? dp[i - 2] : 0) + 2;
//                 }
//                 else if (s[i - 1] == ')')
//                 {
//                     //注意保证索引不越界，比如（））和（（））情况，索引还是有可能越界的
//                     if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') // i与i-dp[i-1]-1配对，是独立的一个子串
//                     {

//                         dp[i] = dp[i - 1] + 2 + (i - dp[i - 1] > 2 ? dp[i - dp[i - 1] - 2] : 0); // dp[i-dp[i-1]-2]代表之前是否有配对的
//                     }
//                 }
//             maxSize = max(maxSize, dp[i]);
//         }
//         return maxSize;
//     }
// };
/*使用栈,自己也想到了用栈这种左右匹配的问题，用栈比较好，但是没调试好代码
具体做法是我们始终保持栈底元素为当前已遍历的元素中最后一个没有被匹配的右括号下标
对于遇到的每个'(',我们将它的下标放入栈中
对于遇到的每个')',我们先弹出栈顶元素表示匹配了当前右括号:
    如果栈为空，说明当前的右括号为没有匹配的右括号，我们将其下标放入栈中来更新我们之前提到的最后一个没有匹配的右括号的下标
    如果栈不为空，当前右括号
*/
// class Solution
// {
// public:
//     int longestValidParentheses(string s)
//     {
//         int maxans = 0;
//         stack<int> stk;
//         stk.push(-1);
//         for (int i = 0; i < s.size(); ++i)
//         {
//             if (s[i] == '(')
//                 stk.push(i);
//             else
//             {
//                 //如果是')'，会弹出，再存储，因此不会出现连续存储')'的情况
//                 //始终保持栈底元素为当前已遍历的元素中最后一个没有被匹配的右括号下标
//                 stk.pop();
//                 if (stk.empty()) //空说明遇到了连续的')'
//                 {
//                     stk.push(i);
//                 }
//                 else
//                 {
//                     maxans = max(maxans, i - stk.top());
//                 }
//             }
//         }
//         return maxans;
//     }
// };
/*两遍遍历
 */
class Solution
{
public:
    int longestValidParentheses(string s)
    {
        int maxans = 0;
        int left = 0, right = 0;
        //统计右括号比左括号多时的合法字符串
        for (size_t i = 0; i < s.size(); ++i)
        {
            if (s[i] == '(')
                left++;
            else
                right++;
            if (left == right)
                maxans = max(maxans, 2*left);
            if (right > left)
                left = right = 0;
        }
        //统计左括号比右括号多时的合法字符串
        left = right = 0;
        for (int i = s.length() - 1; i >= 0; --i)//这里不能使用size_t，size_t没有负数
        {
            if (s[i] == '(')
                left++;
            else
                right++;
            if (left == right)
                maxans = max(maxans, 2*left);
            if (left > right)
                left = right = 0;
        }
        return maxans;
    }
};
int main()
{
    string s = ")()())";
    Solution plan;
    auto n = plan.longestValidParentheses(s);
    cout << "n = " << n << endl;
    return 0;
}