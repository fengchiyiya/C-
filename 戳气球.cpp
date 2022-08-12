// 有 n 个气球，编号为0 到 n - 1，每个气球上都标有一个数字，这些数字存在数组 nums 中。
// 现在要求你戳破所有的气球。戳破第 i 个气球，你可以获得 nums[i - 1] * nums[i] * nums[i + 1] 枚硬币。 
// 这里的 i - 1 和 i + 1 代表和 i 相邻的两个气球的序号。如果 i - 1或 i + 1 超出了数组的边界，那么就当它是一个数字为 1 的气球。
// 求所能获得硬币的最大数量。
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <iostream>
using namespace std;
/*暴力法：搜索每一种情况,广度优先搜索
stl标准函数max_elems快速寻找顺序容器中的最大值
advance将索引变迭代器（实际为迭代器指针移动n个元素）
distance迭代器变索引
超时了，但是感觉算法是对的
也复习了一下广度优先搜索的流程
*/
class Solution
{
public:
    int maxCoins(vector<int> &nums)
    {
        int maxCoins = 0;
        int n = nums.size();
        queue<vector<int>> q;
        deque<int> sum;
        q.push(nums);
        sum.push_back(0);
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++) // vector的个数
            {
                auto x = q.front();
                auto currSum = sum.front();
                q.pop();
                sum.pop_front();
                for (int j = 0; j < x.size(); j++) // vector长度
                {
                    int n1 = j > 0 ? x[j - 1] : 1;
                    int n2 = j < x.size() - 1 ? x[j + 1] : 1;
                    sum.push_back(currSum + n1 * n2 * x[j]);
                    auto v = x;
                    auto index = v.begin();
                    advance(index, j);
                    v.erase(index);
                    q.push(v);
                }
                if (x.size() == 1) // 只有1个元素，代表搜索结束
                    maxCoins = *max_element(sum.begin(), sum.end());
            }
        }
        return maxCoins;
    }
};

/*记忆化搜索（分治法），感觉有点难理解，将戳气球变为每次添加一个气球
rec记录着left到right所能获得的最大值
solve(i,j)表示将开区间(i,j)内的位置全部填满气球能够得到的最多硬币数*/
class Solution
{
public:
    vector<vector<int>> res; //存放结果
    vector<int> rec;         //存放气球值
public:
    int solve(int left, int right)
    {
        // left和right之间没有空隙插入
        if (left >= right - 1)
            return 0;
        // 代表(left,right)之间的最大硬币数已经求过
        if (res[left][right] != -1)
            return res[left][right];
        for (int i = left + 1; i < right; i++)
        {
            int sum = rec[left] * rec[i] * rec[right];
            // 为什么第二段区间不是i+1?因为将i作为新的边界，如果第二段使用i+1作为边界，则边界不对了，就少了一个插入的位置
            sum += solve(left, i) + solve(i, right);
            res[left][right] = max(res[left][right], sum);
        }
        return res[left][right];
    }
    int maxCoins(vector<int> &nums)
    {
        int n = nums.size();
        rec.resize(n + 2, 1);
        for (size_t i = 0; i < n; i++)
        {
            rec[i + 1] = nums[i];
        }
        res.resize(n + 2, vector<int>(n + 2, -1));
        return solve(0, n + 1);
    }
};

/*动态规划
令dp[i][j]表示填满开区间(i,j)能得到的最多硬币数，那么边界条件是i>=j-1，此时dp[i][j]=0;
dp[i][j]=max{val[i]*val[k]*val[j]+dp[i][k]+dp[k][j]}
注意i从n-1开始，否则会出现未知量
*/
class Solution
{
public:
    int maxCoins(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> dp(n + 2, vector<int>(n + 2)); //初值都设为0;
        vector<int> val(n + 2, 1);
        for (size_t i = 0; i < n; i++)
        {
            val[i + 1] = nums[i];
        }
        // 为什么i从结尾部分先开始？因为从开头开始动态规划，j会直接增长到结尾，从而会出现很多未知量
        // 从结尾开始时，j增长的范围是慢慢增长的，不会出现未知量。
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = i + 2; j < n + 2; j++)
            {
                for (int k = i + 1; k < j; k++)
                {
                    int sum = val[i] * val[j] * val[k];
                    sum += dp[i][k] + dp[k][j];
                    dp[i][j] = max(dp[i][j], sum);
                }
            }
        }
        return dp[0][n + 1];
    }
};

int main()
{
    vector<int> v{3, 1, 5, 8};
    Solution plan;
    auto n = plan.maxCoins(v);
    cout << "n = " << n << endl;
}