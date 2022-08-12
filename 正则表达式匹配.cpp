//给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
//'.'匹配任意单个字符
//'*'匹配0个或者多个前面的那一个元素！ *a可以理解为匹配0个或者多个a
//所谓匹配，是要涵盖整个字符串s的，而不是部分字符串
#include<string>
#include<vector>
#include<iostream>
using namespace std;
/*动态规划：正则表达式的匹配是一个逐步匹配的过程，动态规划可以解决一众字符串匹配问题
状态dp[i][j]表示s的前i个是否能被p的前j个匹配
动态规划常与滚动数组一起使用，
当j指向的字符为'*‘时，有两种可能到达dp[i][j]的方法
第一种：S a b [b] b b c
               i
        P a [b *] d * c
               j
        dp[i][j]=dp[i-1][j]到达，只要p[j]='*',s[i]=p[j-1];
第二种：
        dp[i][j]=dp[i][j-2].匹配0次的情况下
*/
//class Solution {
//public:
//    bool isMatch(string s, string p) {
//        int m = s.size();
//        int n = p.size();
//        auto matcher = [&](int i, int j) {//i,j时矩阵的索引，比字符串的索引大1
//            if (i == 0)
//                return false;
//            if (p[j - 1] == '.')
//                return true;
//            return s[i - 1] == p[j - 1];
//        };
//        vector<vector<int>>dp(m + 1, vector<int>(n + 1));//矩阵的索引比字符串索引大1
//        dp[0][0] = true;//空字符串匹配时为true
//        for (size_t i = 0; i < m+1; ++i)
//        {
//            for (size_t j = 1; j < n + 1; ++j)
//            {
//                //注意：当j-1指向b*中的b时，虽然可能匹配是false，但是j如果为*和j-1状态无关，所以这里误判也没事。
//                if (p[j - 1] == '*')
//                {
//                    dp[i][j] |= dp[i][j - 2];//0次匹配
//                    //判断s[i-1]和p[j-2]是否相等
//                    //aaa与aa*的情况
//                    if (matcher(i, j - 1))//相等，代表不是0次匹配
//                        dp[i][j] |= dp[i - 1][j];//为什么采用或操作呢,因为dp[i][j] |= dp[i][j - 2];先赋值了
//                }
//                else
//                {
//                    if (matcher(i, j))
//                        dp[i][j] |= dp[i - 1][j - 1];
//                }
//            }
//        }
//        for (size_t i = 0; i <= m; ++i)
//        {
//            for (size_t j = 0; j <= n; ++j)
//            {
//                cout << dp[i][j] << " , ";
//            }
//            cout << endl;
//        }
//        cout << endl;
//        return dp[m][n];
//    }
//};
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        vector<vector<int>>dp(m + 1, vector<int>(n + 1));
        dp[0][0] = true;
        for (size_t i = 0; i <= m; ++i)
        {
            for (size_t j = 1; j <= n; ++j)
            {
                if (p[j - 1] == '*')
                    dp[i][j] = dp[i][j - 2] || (i != 0 && dp[i - 1][j] && (s[i-1] == p[j - 2] || p[j - 2] == '.'));
                else if(i!=0)
                {
                    dp[i][j] = dp[i - 1][j - 1] && (s[i-1] == p[j-1] || p[j-1] == '.');
                }
            }
        }
        return dp[m][n];
    }
};
int main()
{
    string s = "aaa";
    string p = "ab*a*c*a";
    Solution plan;
    auto x = plan.isMatch(s, p);
    cout << "x = " << x << endl;
    return 0;
}