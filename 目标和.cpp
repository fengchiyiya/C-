// 给你一个整数数组 nums 和一个整数 target 。
// 向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：
// 例如，nums = [ 2, 1 ] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
// 返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。
#include <vector>
using namespace std;
/*第一想法：深度优先搜索或者广度优先搜索*/
class Solution
{
public:
    int cnt = 0;

public:
    void dfs(vector<int> &nums, int length, int pos, int sum, int target)
    {
        if (pos >= length)
            return;
        if ((pos == length - 1) && (sum + nums[pos] == target))
            ++cnt;
        if ((pos == length - 1) && (sum - nums[pos] == target)) // 注意这里不能使用else if
            ++cnt;
        dfs(nums, length, pos + 1, sum + nums[pos], target);
        dfs(nums, length, pos + 1, sum - nums[pos], target);
    }
    int findTargetSumWays(vector<int> &nums, int target)
    {
        int n = nums.size();
        dfs(nums, n, 0, 0, target);
        return cnt;
    }
};

/*动态规划，比较难想
dp[i][j]表示在数组nums中前i个数中选取元素，使得这些元素之和等于j的方案数。
是选取添加‘-’的元素和为j，最终是要变-j的。如果j<nums[i]，选中nums[i]的话，添加-号后溢出了
假设数组nums的长度为n,则最终答案为dp[n][neg]
dp[i][j]=dp[i-1][j],                        j<nums[i];// 如果选择了nums[i],dp[i][j]=dp[i-1][j]+dp[i-1][j-nums[i]]越界了
        =dp[i-1][j]+dp[i-1][j-nums[i]],     j>=nums[i]。
*/
class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    {
        int sum = 0;
        for (int &num : nums)
        {
            sum += num;
        }
        int diff = sum - target;
        if (diff < 0 || diff % 2 != 0) // diff是2的倍数，就不会直接返回，代表neg是个整数!
        {
            return 0;
        }
        int n = nums.size(), neg = diff / 2;
        vector<vector<int>> dp(n + 1, vector<int>(neg + 1));
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++)
        {
            int num = nums[i - 1];
            for (int j = 0; j <= neg; j++)
            {
                dp[i][j] = dp[i - 1][j];
                if (j >= num)
                {
                    dp[i][j] += dp[i - 1][j - num];
                }
            }
        }
        return dp[n][neg];
    }
};
/*虽然dp的规模从二维变为了1维，但是依旧还是需要二重循环
dp[i][j]的更新，只依赖于上一行的状态*/
class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    {
        // 非负和整数两个条件判断
        int sum = 0;
        for (const auto &num : nums)
        {
            sum += num;
        }
        int diff = sum - target;
        if (diff < 0 || diff % 2 != 0) //负数和不是整数直接退出
            return 0;
        int neg = diff / 2;
        // 用滚动数组的方式降低空间复杂度
        vector<int> dp(neg + 1);
        dp[0] = 1;
        for (int &num : nums) // 外层有种按行往下推的感觉
        {
            for (int j = neg; j >= num; j--) // 选若干个数和为j。
            {
                dp[j] += dp[j - num];
            }
        }
        return dp[neg];
    }
};