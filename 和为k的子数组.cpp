// 给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的连续子数组的个数 。
#include <vector>
#include <algorithm>
using namespace std;
/*深度优先搜素，这是讲究连续关系的不能先排序，超时，深度优先搜索类似暴力搜索哦*/
class Solution
{
public:
    int cnt = 0;
    void dfs(vector<int> &nums, int pos, int target, int length)
    {
        if (pos >= length) // 越界
            return;
        if ((target - nums[pos]) == 0)
            ++cnt;

        dfs(nums, pos + 1, target - nums[pos], length);
    }
    int subarraySum(vector<int> &nums, int k)
    {
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            dfs(nums, i, k, n);
        }
        return cnt;
    }
};
/*如何优化时间呢？动态规划？是前缀和+哈希表
先求和，判断前后差是否为K
定义sum[i]为0~i之间的所有数的和，则sum[i]可以由sum[i-1]递推而来
sum[i]=sum[i-1]+num[i]
前缀和作为key，出现次数为value
sum[j-1]==sum[i]-k
原因是：mp[sum-k]是之前的子数组和，mp[sum]是当前的数组和.
mp[sum-k]的个数，代表了以前位置到当前位置的数组和为k的个数
*/
#include <unordered_map>
class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> mp;
        mp[0] = 1; //这个是防止k=从下标0开始的子数组和
        int sum = 0, cnt = 0;
        for (auto &n : nums)
        {
            sum += n;
            if (mp.find(sum - k) != mp.end())
            {
                cnt += mp[sum - k];
            }
            mp[sum]++;
        }
        return cnt;
    }
};