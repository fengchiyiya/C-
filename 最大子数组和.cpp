//给你一个整数数组nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
//子数组 是数组中的一个连续部分。
#include <vector>
using namespace std;
/*一次遍历法*/
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int maxSum = INT_MIN, currSum = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            if (currSum <= 0) //如果当前和小于0了，从当前点开始重新计数
            {
                currSum = nums[i];
                maxSum = max(maxSum, currSum);
                continue;
            }
            currSum += nums[i];
            maxSum = max(maxSum, currSum);
        }
        return maxSum;
    }
};
/*动态规划
f(i)=max{f(i-1)+nums[i],nums[i]}
*/
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int curSum = 0, maxSum = INT_MIN;
        for (auto &n : nums)
        {
            curSum=max(curSum+n,n);
            maxSum=max(maxSum,curSum);
        }
        return maxSum;
    }
};
/*分治
利用4个量(l,r)
从左端点l开始的最大字段和
从右端点r开始的最大字段和
(l,r)区间内的最大字段和
(l,r)的区间和
*/