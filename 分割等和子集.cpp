// 给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
using namespace std;
/*先求出元素和，然后和为偶数才有可能划分，和为奇数不可能划分*/
/*和组合求和有点类似,和为偶数时，找到组合和为一半的组合
超时了，并且没有去重的操作，自己写的很垃圾*/
class Solution
{
public:
    bool findS = false;

public:
    void dfs(vector<int> &nums, int pos, int target)
    {
        if (pos >= nums.size())
            return;
        if (target < 0)
            return;
        if (target == 0)
        {
            findS = true;
            return;
        }
        // 选中当前节点
        dfs(nums, pos + 1, target - nums[pos]);
        // 未选中当前节点
        dfs(nums, pos + 1, target);
    }
    bool canPartition(vector<int> &nums)
    {
        if (nums.size() < 2)
            return false;
        int sum = accumulate(nums.begin(), nums.end(), 0);
        sort(nums.begin(), nums.end());

        if (sum & 1) // 奇数
            return false;
        else
        {
            int target = sum / 2;
            // 递归找和为target的子数组
            dfs(nums, 0, target);
        }
        return findS;
    }
};

/*动态规划，（深度优先搜索超时了）
创建二维数组dp，包含n行target+1列，其中dp[i][j]表示从数组的[0,i]下标范围选取若干个正整数，
是否存在一种选取方案使得被选取的正整数和等于j。初始时，dp中的元素都为false。
边界情况：
    如果不选取任何正整数，则被选取的正整数等于0。因此对于0<=i<n,都有dp[i][0]=true。
    i==0,只有一个nums[0]可以被选取，因此dp[0][nums[0]]=true
i>0且j>0时：
    j>=nums[i],则对于当前的数字nums[i]，可以选取也可以不选取，两种情况只要有一个true，就有dp[i][j]=true;
        不选取nums[i],则dp[i][j]=dp[i-1][j];
        如果选取nums[i],则dp[i][j]=dp[i-1][j-nums[i]]。
    j<nums[i],无法选取nums[i],则dp[i][j]=dp[i-1][j]

最终的动态规划方程：
    dp[i][j]=dp[i-1][j]|dp[i-1][j-nums[i]], j>=nums[i]
            =dp[i-1][j],                    j<nums[i]

但是可以发现在计算 \textit{dp}dp 的过程中，每一行的 dpdp 值都只与上一行的 dpdp 值有关，
因此只需要一个一维数组即可将空间复杂度降到O(target)。此时的转移方程为：
dp[j]=dp[j]|dp[j-nums[i]]
且需要注意的是第二层的循环我们需要从大到小计算，因为如果我们从小到大更新 dp 值，那么在计算 dp[j] 值的时候，
dp[j−nums[i]] 已经是被更新过的状态，不再是上一行的 dp 值。
行内正序递推的二维dp：内层for循环需要逆序遍历
即nums[i] <= j时，如果dp[j]的更新取决于上一时刻的dp[j-nums[i]]，这就需要逆序遍历。
因为如果顺序遍历的话，dp[j-nums[i]]先于dp[j]得到更新，dp[j]就会用当前时刻的dp[j-nums[i]]更新，导致错误
 */
class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 2)
            return false;
        int sum = 0, maxElem = 0;
        for (auto &num : nums)
        {
            sum += num;
            maxElem = max(num, maxElem);
        }
        if (sum & 1)
            return false;
        int target = sum >> 1;
        if (maxElem > target)
            return false;

        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int i = 0; i < n; i++)
        {
            int n = nums[i];
            for (int j = target; j >= n; j--)
            {
                dp[j] = dp[j] | dp[j - n]; // |=,是int类型的专属操作
            }
        }
        return dp[target];
    }
};