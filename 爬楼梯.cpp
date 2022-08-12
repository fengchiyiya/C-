//假设你正在爬楼梯。需要n阶你才能到达楼顶。
//每次你可以爬1或2个台阶。你有多少种不同的方法可以爬到楼顶呢？
#include <vector>
#include <iostream>
using namespace std;
/*动态规划配合滚动数组*/
class Solution
{
public:
    int climbStairs(int n)
    {
        if (n == 0)
            return 0;
        vector<int> dp(3);
        dp[0] = 1; //初值为1
        for (size_t i = 1; i < n + 1; ++i)
        {
            if (i == 1)
                dp[1] = dp[0];
            else
            {
                dp[2] = dp[0] + dp[1];
                dp[0]=dp[1];
                dp[1]=dp[2];
            }          
        }
        return dp[1];
    }
};