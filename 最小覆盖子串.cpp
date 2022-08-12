//给你一个字符串s、一个字符串t。返回s中涵盖t所有字符的最小子串。如果s中不存在涵盖t所有字符的子串，则返回空字符串"" 。
//注意：
//对于t中重复字符，我们寻找的子字符串中该字符数量必须不少于t中该字符数量。
//如果s中存在这样的子串，我们保证它是唯一的答案。
#include <string>
#include <unordered_map>
using namespace std;
/*利用双指针实现滑动窗口法,字符串相关问题（一维数组）常用滑动窗口
在滑动窗口类型的问题种都会有两个指针，一个用于[延伸]现有窗口的r指针，和一个用于[收缩]窗口的l指针
我们在s上滑动窗口，通过移动r指针不断扩张窗口。当窗口包含t全部所需的字符后，如果能收敛，
我们就收缩窗口直到得到最小窗口*/
class Solution
{
public:
    unordered_map<char, int> ori, cnt; // ori代表t中原字符组合，cnt代表s中子字符串的组合；存放的是字符和数量
    bool check()
    {
        for (const auto &c : ori)
        {
            if (c.second > cnt[c.first])
            {
                return false;
            }
        }
        return true;
    }
    string minWindow(string s, string t)
    {
        for (size_t i = 0; i < t.size(); ++i)
        {
            ++ori[t[i]];
        }
        int l = 0, r = -1;
        int ansL = -1, len = INT_MAX;
        while (r < (int)s.size())
        {
            // cnt添加字符
            if (ori.find(s[++r]) != ori.end()) //查询时，不能使用下标会自动插入的
                ++cnt[s[r]];
            while (check() && l <= r)
            {
                if (r - l + 1 < len)
                {
                    len = r - l + 1;
                    ansL = l;
                }
                //如果l指向的字符是t中字符，则前进时，需要将cnt中字符数量-1
                if (ori.find(s[l]) != ori.end())
                    --cnt[s[l]];
                ++l;
            }
        }
        return ansL == -1 ? string() : s.substr(ansL, len);
    }
};