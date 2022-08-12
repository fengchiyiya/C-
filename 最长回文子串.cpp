//给你一个字符串s，找到s中最长的回文子串。
#include<string>
#include<iostream>
#include<vector>
using namespace std;
/*快慢指针好像解决不了回文的问题,acbba这种不是回文子串，回文子串是左右对称的*/

/*动态规划:空间换取时间，将之前的计算结果存储起来
动态规划的状态转移方程：从长度较短的字符串向长度较长的字符串进行转移*/
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n < 2)//一个字符或0个字符直接返回
            return s;
        int begin = 0;
        int maxLen = 1;
        //dp[i][j]=true,代表[i,j]是回文子串
        vector<vector<bool>> dp(n, vector<bool>(n,0));//存储计算结果
        //枚举长度 注意是从2开始的，所以递推的表达式没有长度为1的情况，用长度为3的情况代替
        for (int L = 2; L <=n; ++L)
        {
            //枚举左边界起点
            for (int i = 0; i < n; ++i)
            {
                //右边界 j-i+1=L
                int j = L + i - 1;
                if (j >= n)//越界
                    break;
                if (s[i] != s[j])
                {
                    continue;
                }
                else//s[i]==s[j]
                {
                    //如果长度小于等于3，则直接判断，不进行递推
                    if (L-1 < 3)//为什么是L-1？因为枚举长度从2开始，用长度3的回文串代替长度1的回文串
                    {
                        //cout << "L = " << L << endl;
                        dp[i][j] = true;
                    }
                    else//如果是回文串并且长度大于2，那么将首尾两个字母去除之后，它仍然是个回文串
                    {
                        dp[i][j] = dp[i + 1][j - 1];//长度为3由长度为1递推得到，长度为4由长度为2递推得到
                    }
                }
                //dp[i][j]是回文串，并且比上一个长度大
                if (dp[i][j] && j - i + 1 > maxLen)
                {
                    begin = i;
                    maxLen = j - i + 1;
                }
            }
        }
        return s.substr(begin,maxLen);
    }
};
/*中心扩展算法*/
class Solution {
public:
    pair<int, int> extend(const string& s, int left, int right)
    {
        while (left>=0&&right<s.size()&&s[left]==s[right])//如果传入的子串满足回环，开始向外扩展
        {
            left--;
            right++;
        }
        //返回pair
        return { left + 1,right-1 };//返回最后满足回文的左右边界
    }
    string longestPalindrome(string s) {
        int begin = 0, end = 0;
        for (size_t i = 0; i < s.size(); ++i)
        {
            auto [left1,right1]=extend(s, i, i);//单个字符传入
            auto [left2,right2]=extend(s, i, i+1);//两个字符传入 只有两个字符都相等才会返回正确值
            if (right1 - left1 > end - begin)
            {
                begin = left1;
                end = right1;
            }
            if (right2 - left2 > end - begin)
            {
                begin = left2;
                end = right2;
            }
        }
        return s.substr(begin, end - begin + 1);
    }
};
int main()
{
    string s = "cbbbd";
    //string s = "babad";
    Solution plan;
    auto sub=plan.longestPalindrome(s);
    cout << "sub = " << sub << endl;
    return 0;
}