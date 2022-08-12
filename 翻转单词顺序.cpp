//输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。
//为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a student. "，则输出"student. a am I"。
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
/*先翻转整个字符串，然后再翻转恢复单词字符的顺序*/
class Solution {
public:
    string reverseWords(string s) {
        //翻转字符串
        reverse(s.begin(), s.end());
        cout << "s = " << s << endl;
        int idx = 0;
        int n = s.size();
        //begin 代表原始字符串位置
        //idx 代表修改后字符串的位置
        for (size_t begin = 0; begin < n; ++begin)
        {
            if (s[begin] != ' ')
            {
                if (idx != 0)//在寻找单词结尾时，end指向了单词结尾，并未指向空格，所以这里idx需要++               
                    s[idx++]=' ';
                int end = begin;
                while (end < n && s[end] != ' ')//寻找单词结尾,同时删除开头的空格，并将字符逐渐前移
                    s[idx++] = s[end++];
                reverse(s.begin() + idx - (end - begin), s.begin() + idx);
                begin = end;//begin此时指向单词结尾，但是循环结束后，begin需要+1
            }
        }
        s.erase(s.begin() + idx, s.end());//删除多余部分
        return s;
    }
};
int main()
{
    Solution plan;
    //string s = "the sky is blue";
    string s = "  hello world!  ";
    auto w=plan.reverseWords(s);
    cout << "w = " << w << endl;
}