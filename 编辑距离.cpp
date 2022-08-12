//给你两个单词word1和word2,请返回将word1转换成word2所使用的最少操作数。
//你可以对一个单词进行如下三种操作：
//插入一个字符
//删除一个字符
//替换一个字符
#include <string>
#include <vector>
#include <iostream>
using namespace std;
/*动态规划
dp[i][j]表示A的前i个字母变换到B的前j个字母之间的编辑距离
增，dp[i][j]=dp[i][j-1]+1 例如对A的增加，等效对B的删除
删，dp[i][j]=dp[i-1][j]+1 例如对A的删除，等效对A的增加
改，dp[i][j]=dp[i-1][j-1]+1 例如对A的修改，等效于对B的修改
dp[i][j]取上述三种操作的最小值
如果word1[i-1]=word2[j-1],dp[i][j]=dp[i-1][j-1]
需要考虑word1或word2一个字母都没有，即全增加/删除的情况，预留dp[0][j]和dp[i][0]
*/
class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int m = word1.length();
        int n = word2.length();
        if (m * n == 0) //判断两个数中任意一个为0，并返回那个数的简洁办法
            return m + n;
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        //边界状态初始化
        for (size_t i = 0; i < m + 1; ++i)
        {
            dp[i][0] = i;
        }
        for (size_t j = 0; j < n + 1; ++j)
        {
            dp[0][j] = j;
        }
        for (int i = 1; i < m + 1; ++i)
        {
            for (int j = 1; j < n + 1; ++j)
            {
                int add = dp[i][j - 1]+1;//对word1增加
                int del = dp[i - 1][j]+1;//对word1删除
                int change = dp[i - 1][j - 1];//对word1修改
                if (word1[i - 1] != word2[j - 1])//矩阵的下标比字符串的下标大1
                    change += 1;
                dp[i][j]=min({add,change,del});//连续取极值，{}
            }
        }
        return dp[m][n];
    }
};