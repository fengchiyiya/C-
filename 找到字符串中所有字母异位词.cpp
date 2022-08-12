// 给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
// 异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。
#include <vector>
#include <string>
using namespace std;
// 没有好的思路，看题解了
/*用每种字母的数量确定是否是异位词，这是个很好的想法。
使用滑动窗口每次框目前长度的字符串*/
class Solution
{
public:
    vector<int> findAnagrams(string s, string p)
    {
        int sLen = s.length(), pLen = p.length();
        if (sLen < pLen)
            return {};
        vector<int> ans;
        vector<int> sCount(26);
        vector<int> pCount(26);
        for (int i = 0; i < pLen; i++)
        {
            ++sCount[s[i] - 'a'];
            ++pCount[p[i] - 'a'];
        }
        if (sCount == pCount) //如果两者开头窗口长度内元素一样，注意vector重载了=符号
            ans.emplace_back(0);
        for (int i = 0; i < sLen - pLen; i++)
        {
            // 移除开头的元素，加入后一个元素
            --sCount[s[i] - 'a'];
            ++sCount[s[i + pLen] - 'a'];
            if (sCount == pCount)
                ans.emplace_back(i + 1); // 因为i被移除了，剩下的第一个元素是i+1
        }
        return ans;
    }
};