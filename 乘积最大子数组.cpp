// 给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续子数组（该子数组中至少包含一个数字），
// 并返回该子数组所对应的乘积。测试用例的答案是一个 32-位 整数。
// 子数组 是数组的连续子序列。
#include <vector>
using namespace std;
/*动态规划+滚动数组
本题与最大子数组的和不同，乘积还需要考虑负数的情况，因为负负得正。
维护两个数组，一个代表当前的最大乘积，一个代表当前的最小乘积。
分类讨论：
fmax(i)=max(fmax(i-1)*nums[i],fmin(i-1)*nums[i])
fmin(i)=min(fmax(i-1)*nums[i],fmin(i-1)*nums[i])
*/
class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        int n=nums.size();
        //滚动数组
        int fmax=nums[0],fmin=nums[0],ans=nums[0];
        for (size_t i = 1; i < n; i++)
        {
            int mx=fmax,mn=fmin;//需要临时存一下，因为后续会发生变化
            //当nums[i]=0时，fmax=fmin=0。这一步比较巧妙
            fmax=max({mx*nums[i],mn*nums[i],nums[i]});//{}可以连续取最值
            fmin=min({mx*nums[i],mn*nums[i],nums[i]});
            ans=max(fmax,ans);
        }
        return ans;
    }
};