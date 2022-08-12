// 给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。
// 完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。
// 例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。
// 第一时间想到贪心，但是贪心未必是最少数量
// 第二种方法应该是广度优先搜索，将1到根号n的整数的完全平方数列出来

#include <vector>
using namespace std;
/*动态规划 这种统计类的最值问题，通常可以用动态规划解决
f[i]存放，i需要的最少个数的完全平方数
*/
class Solution
{
public:
    int numSquares(int n)
    {
        vector<int> f(n + 1);
        for (size_t i = 1; i < n; i++)
        {
            int minCnt = INT_MAX; // 记录f[i]之前的最小平方数个数
            for (size_t j = 1; j * j <= i; i++)
            {
                minCnt = min(minCnt, f[i - j * j]); // 注意这里是i-j*j
            }
            f[i] = minCnt + 1;
        }
        return f[n];
    }
};