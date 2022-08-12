// 给定一个整数数组prices，其中第  prices[i] 表示第 i 天的股票价格 。​
// 设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票） :
// 卖出股票后，你无法在第二天买入股票(即冷冻期为 1 天)。 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
// 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
#include <vector>
using namespace std;
// 没有想法！这道题可以重点看看
/*动态规划  对于不同状态的问题的动态规划是二维数组的问题！
股票类型的问题，一种常用的方法是将买入和卖出分开考虑。
利用动态规划维护在股市中每一天结束后可以获得的累计最大收益。
因为会有冷冻期，并且只能在卖出之后才能买新的股票，因此会有不同的状态
需要二维数组的动态规划。
我们目前持有一支股票，对应的累计最大收益记为f[i][0];
我们目前不持有任何股票，并且处于冷冻期中，对应的累计最大收益记为f[i][1];第i天刚卖
我们目前不持有任何股票，并且不处于冷冻期中，对应的累计最大收益记为f[i][2];
f[i][0]=max{f[i-1][0],f[i-1][2]-prices[i]}
f[i][1]=f[i-1][0]+prices[i];
f[i][2]=max{f[i-1][1],f[i-1][2]}
然后动态规划问题，一般都可以使用动态数组进一步优化空间复杂度。

将第0天的情况，作为边界条件：
    f[0]=-price[0];
    f[1]=0;
    f[2]=0;
*/
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        if (prices.empty())
            return 0;
        int f0 = -prices[0];
        int f1 = 0;
        int f2 = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            // f[0]当天持有股票=前一天的持有股票或前一天刚卖完，并过了冷冻期
            // f[1]当天卖出股票，并且当天是冷冻期=前一天持有股票+今天的股票卖出价
            // f[2]当天不是冷冻期，且没有买入=前一天的非冷冻期+前一天刚卖出股票的冷冻期
            tie(f0, f1, f2) = make_tuple(max(f0, f2 - prices[i]), f0 + prices[i], max(f2, f1));
        }
        return max(f1, f2);
    }
};
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        if (prices.empty())
        {
            return 0;
        }

        int n = prices.size();
        int f0 = -prices[0];
        int f1 = 0;
        int f2 = 0;
        for (int i = 1; i < n; ++i)
        {
            tie(f0, f1, f2) = make_tuple(max(f0, f2 - prices[i]), f0 + prices[i], max(f1, f2));
        }

        return max(f1, f2);
    }
};