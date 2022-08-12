// 给定一个经过编码的字符串，返回它解码后的字符串。
// 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
// 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
// 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数k，例如不会出现像 3a 或 2[4] 的输入。
#include <string>
#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/*辅助栈，想到了可能会使用辅助栈，但是出栈的顺序是反的，所以想用队列完成栈的工作.
但是本题是用vector容器替代的栈
判断一个字符是否是数字，有内置函数isdigit();判断字符是否为字母isalpha();
思路差不多，但是string的内置函数不是很熟悉，这题可以用来学习string的一些内置函数；
*/
class Solution
{
public:
    //数字拼接，因为数字可能不止一位
    string getDigits(string &s, size_t &ptr)
    {
        string ret = "";
        while (isdigit(s[ptr]))
        {
            ret.push_back(s[ptr++]);
        }
        return ret;
    }
    // 将容器中字符串进行拼接
    string getString(vector<string> &v)
    {
        string ret;
        for (auto &s : v)
        {
            ret += s;
        }
        return ret;
    }
    //循环解码
    string decodeString(string s)
    {
        int n = s.length();
        vector<string> stk;
        size_t ptr = 0;
        while (ptr < n)
        {
            char cur = s[ptr];
            if (isdigit(cur)) //数字入栈
            {
                auto str = getDigits(s, ptr);
                stk.push_back(str);
            }
            else if (isalpha(cur) || cur == '[') // 字母或者左括号入栈
            {
                stk.push_back(string{cur});
                ++ptr;
            }
            else // ']'出栈;怎么处理两个']'这种情况,while控制的循环，遇到一个]就立刻先解码
            {
                vector<string> sub;
                while (stk.back() != "[") // 这里注意是判断已经入栈的序列,是否已经到了'['的位置
                {
                    sub.push_back(stk.back());
                    stk.pop_back();
                }
                reverse(sub.begin(), sub.end()); //翻转
                string t, o = getString(sub);
                stk.pop_back();             // 弹出左括号
                int rep = stoi(stk.back()); //重复的次数
                stk.pop_back();             // 数字出栈
                while (rep--)
                {
                    t += o;
                }
                stk.push_back(t);
                ++ptr; // 控制索引增长不能忘了
            }
        }
        return getString(stk);
    }
};
int main()
{
    string s = "3[a]2[bc]";
    Solution plan;
    auto ans = plan.decodeString(s);
    cout << "ans = " << ans << endl;
}
