// 给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
// 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。
// 设计一个算法来计算你所能获取的最大利润。
// 返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
#include <vector>
using namespace std;
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        //需要一个变量记录目前为止的最小值，另一个变量实时更新最大利润
        int minPri=prices[0],maxPro=0;
        int n=prices.size();
        for (size_t i = 1; i <n ; i++)
        {
            minPri=min(minPri,prices[i]);
            maxPro=max(maxPro,prices[i]-minPri);
        }
        return maxPro;
    }
};