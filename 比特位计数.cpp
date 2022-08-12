// 给你一个整数 n ，对于 0 <= i <= n 中的每个 i ，计算其二进制表示中 1 的个数 ，返回一个长度为 n + 1 的数组 ans 作为答案。
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;
/*第一时间想到的是暴力循环+遍历，但是时间复杂度太高了。好像可以利用动态规划
f(k)=f(i)+...,如果k不是2的幂次方，应该用贪心找到最接近的2的幂次方，然后迭代
f(k)=1,k是2的幂次方，如何判断是2的幂次方呢？log函数和(x&(x-1)) 后面的方法很巧妙，
log函数加判断整数可能会出错，数越大越容易出错

2的幂次方是1后面跟着一堆0，-1后，1会变为0，跟着的一堆0都会变为1，两者相遇，结果必为1
 */
/*我的动态规划还可以改进，对规律还是不够清晰；
dp[x]=dp[z]+1;z=x-y，y为x的最大整数幂
*/
class Solution
{
public:
    vector<int> countBits(int n)
    {
        vector<int> dp(n + 1, 0);
        if (n == 0)
            return {0};
        for (int i = 1; i <= n; i++)
        {
            // i是2的幂次方
            if (!(i & (i - 1)))
                dp[i] = 1;
            else
            {
                int target = i;
                while (target > 0)
                {
                    int s = 0;
                    for (int j = 0; s <= target; j++)
                    {
                        if (j == 0)
                            s = 1;
                        else
                            s *= 2;

                    } // 注意出循环时，s是比target大的
                    s /= 2;
                    dp[i] += dp[s];
                    target -= s; // 注意是target-s，i-s的话，会陷入死循环
                }
            }
        }
        return dp;
    }
};
/*自己方法的改进；dp[10]=dp[2]+1,并且因为是从小到大递推的，不会出现未知数；
原来的思想是找到dp[2]和dp[8],dp[10]=dp[2]+dp[8]，这样数越大时，越繁琐，对前面的数利用不够充分
dp[2],dp[8]也就只是个1*/
class Solution
{
public:
    vector<int> countBits(int n)
    {
        vector<int> dp(n + 1, 0);
        if (n == 0)
            return {0};
        for (int i = 1; i <= n; i++)
        {
            // i是2的幂次方
            if (!(i & (i - 1)))
                dp[i] = 1;
            else
            {
                int s = 0;
                for (int j = 0; s <= i; j++)
                {
                    if (j == 0)
                        s = 1;
                    else
                        s *= 2;

                } // 注意出循环时，s是比target大的
                s /= 2;
                dp[i] += dp[i - s] + 1;
            }
        }
        return dp;
    }
};
/*Brian Kernighan 算法 数学中的方法*/
class Solution2
{
public:
    int countOnes(int x)
    {
        int ones = 0;
        while (x > 0)
        {
            x &= (x - 1);
            ones++;
        }
        return ones;
    }

    vector<int> countBits(int n)
    {
        vector<int> bits(n + 1);
        for (int i = 0; i <= n; i++)
        {
            bits[i] = countOnes(i);
        }
        return bits;
    }
};

int main()
{
    Solution plan;
    auto ans = plan.countBits(2049);
    Solution2 plan2;
    auto ans2 = plan2.countBits(2049);
    if (ans.size() == ans2.size())
        cout << "size = " << ans.size() << endl;
    else
        return 0;
    for (int i = 0; i < ans.size(); i++)
    {
        if (ans[i] != ans2[i])
        {
            cout << " i = " << i << endl;
            cout << "ans = " << ans[i] << endl;
            cout << "ans2 = " << ans2[i] << endl;
        }
    }
}