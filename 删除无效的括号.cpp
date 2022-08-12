// 给你一个由若干括号和字母组成的字符串 s ，删除最小数量的无效括号，使得输入的字符串有效。
// 返回所有可能的结果。答案可以按 任意顺序 返回。
#include <vector>
#include <string>
using namespace std;
/*回顾一下做过的题，判断括号的合法性。
将左括号入栈，遇到右括号时，弹出，最后判断是否合法
最长有效括号：难题
    两遍循环，一边从左往右，一遍从右往左
*/
/* 题目要我们删除括号使得剩下的括号匹配，可以使用回溯算法，尝试遍历所有可能的去除非法括号的方案（类似暴力法）
 */
class Solution
{
public:
    vector<string> res;
    bool isVaild(string s)
    {
        int cnt = 0;
        for (auto &ch : s)
        {
            if (ch == '(')
            {
                ++cnt;
            }
            else if (ch == ')')
            {
                --cnt;
                if (cnt < 0)
                    return false;
            }
        }
        return cnt == 0;
    }
    vector<string> removeInvalidParentheses(string s)
    {
        int lremove = 0, rremove = 0;
        for (char c : s)
        {
            if (c == '(')
                ++lremove;
            else if (c == ')')
            {
                if (lremove == 0)
                    ++rremove;
                else
                    --lremove;
            }
        }
        helper(s, 0, lremove, rremove);
        return res;
    }
    // 这里不需要传引用，因为s在传入时已经被改变了
    void helper(string s, int start, int lremove, int rremove)
    {
        if (lremove == 0 && rremove == 0)
        {
            if (isVaild(s))
                res.push_back(s);
            return;
        }
        for (int i = start; i < s.size(); i++) // 注意i从start开始
        {
            // 连续遇到相同的括号，跳过，删除效果是一样的
            if (i != start && s[i] == s[i - 1]) // i!=start 跳过开头
                continue;
            // 剩余的字符串长度小于要删除的括号数
            // s.size()-i包含了s[i]这个位置,此时还没开始删除，所以剩余的长度应该包括s[i]
            if (lremove + rremove > s.size() - i)
                return;
            // 尝试去掉左括号
            if (s[i] == '(' && lremove > 0)
            {
                // s.substr(0,i)+s.substr(i+1) （起始位置，长度）
                helper(s.substr(0, i) + s.substr(i + 1), i, lremove - 1, rremove);
            }
            // 尝试去掉右括号
            if (s[i] == ')' && rremove > 0)
                helper(s.substr(0, i) + s.substr(i + 1), i, lremove, rremove - 1);
        }
    }
};
#include <unordered_set>
/*广度优先搜索
广度优先搜索，二重循环，遍历每一种可能，同时使用哈希表去除重复结果
*/
class Solution
{
public:
    bool isValid(string str)
    {
        int count = 0;

        for (char c : str)
        {
            if (c == '(')
            {
                count++;
            }
            else if (c == ')')
            {
                count--;
                if (count < 0)
                {
                    return false;
                }
            }
        }

        return count == 0;
    }
    vector<string> removeInvalidParentheses(string s)
    {
        vector<string> ans;
        unordered_set<string> currSet;
        currSet.insert(s);
        while (true)
        {
            unordered_set<string> nextSet;
            for (auto &str : currSet)
            {
                if (isValid(str))
                    ans.emplace_back(str);
            }
            // 找到了删除最小数量的有效括号
            if (ans.size() > 0)
                return ans;
            for (auto &str : currSet)
            {
                for (size_t i = 0; i < str.size(); i++)
                {
                    if (i != 0 && str[i] == str[i - 1])
                        continue;
                    if (str[i] == '(' || str[i] == ')')
                        nextSet.insert(str.substr(0, i) + str.substr(i + 1));
                }
            }
            currSet = nextSet;
        }
    }
};
class Solution
{
public:
    bool isValid(string str)
    {
        int count = 0;

        for (char c : str)
        {
            if (c == '(')
            {
                count++;
            }
            else if (c == ')')
            {
                count--;
                if (count < 0)
                {
                    return false;
                }
            }
        }

        return count == 0;
    }

    vector<string> removeInvalidParentheses(string s)
    {
        vector<string> ans;
        unordered_set<string> currSet;

        currSet.insert(s);
        while (true)
        {
            for (auto &str : currSet)
            {
                if (isValid(str))
                    ans.emplace_back(str);
            }
            if (ans.size() > 0)
            {
                return ans;
            }
            unordered_set<string> nextSet;
            for (auto &str : currSet)
            {
                for (int i = 0; i < str.size(); i++)
                {
                    if (i > 0 && str[i] == str[i - 1])
                    {
                        continue;
                    }
                    // 对每一个括号都剔除尝试
                    if (str[i] == '(' || str[i] == ')')
                    {
                        nextSet.insert(str.substr(0, i) + str.substr(i + 1, str.size()));
                    }
                }
            }
            currSet = nextSet;
        }
    }
};
