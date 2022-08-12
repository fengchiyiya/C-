//给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
// 有效字符串需满足：
// 左括号必须用相同类型的右括号闭合。
// 左括号必须以正确的顺序闭合。
#include <string>
#include <stack>
using namespace std;
//利用栈的特性:这种按顺序的对称的匹配问题，一般可以利用栈的特性
/*遇到左括号入栈，右括号出栈*/
class Solution
{
public:
    bool isValid(string s)
    {
        int size = s.size();
        stack<char> sta;
        for (size_t begin = 0; begin < size; ++begin)
        {
            if (s[begin] == '{' || s[begin] == '(' || s[begin] == '[')
                sta.push(s[begin]);
            else
            {
                if(sta.empty())//没有输入右括号，也是false
                    return false;
                char c = sta.top();
                if (s[begin] == ')' && c == '(')
                    sta.pop();
                else if (s[begin] == ']' && c == '[')
                    sta.pop();
                else if (s[begin] == '}' && c == '{')
                    sta.pop();
                else
                    return false;
            }
        }
        if (sta.size() > 0)
            return false;
        return true;
    }
};