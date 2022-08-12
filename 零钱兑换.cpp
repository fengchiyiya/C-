// 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
// 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
// 你可以认为每种硬币的数量是无限的。
#include <vector>
#include <queue>
using namespace std;
/*很明显的广度优先搜索,但是超时！！！
动态规划好像也可以，如果差距为硬币面值直接+1即可
 */
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        queue<int> targets;
        targets.push(amount);
        int cnt = 0;
        while (!targets.empty())
        {
            int n = targets.size();
            targets.pop();
            for (int i = 0; i < n; i++)
            {
                int target = targets.front();
                if (target == 0)
                    return cnt;
                for (int j = 0; j < coins.size(); j++)
                {
                    if (target - coins[j] >= 0)
                        targets.push(target - coins[j]);
                }
            }
            ++cnt;
        }
        return -1;
    }
};

/*记忆化搜索，记忆化搜索也是一种动态规划的思想
F(S):组成金额所需的最少硬币数量
    F(S)=F(S-C)+1;
因为找的是最少数量，最大值的设置有点小技巧，硬币的数量不会比金额多。
这题的递推方程还是比较好求的。
*/
class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        if (amount == 0)
            return 0;
        int Max = amount + 1; // 这里的Max设置的很巧妙,设置INT_Max，+1时会超出范围，注意观察题目的边界条件
        vector<int> F(amount + 1, Max);
        F[0] = 0;
        for (int i = 1; i <= amount; i++)
        {
            for (int j = 0; j < coins.size(); j++)
            {
                if (i - coins[j] >= 0)
                    F[i] = min(F[i - coins[j]] + 1, F[i]);
            }
        }
        return F[amount] > amount ? -1 : F[amount];
    }
};