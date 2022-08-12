// 给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积 。
// 题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。
// 请不要使用除法，且在 O(n) 时间复杂度内完成此题。
#include <vector>
using namespace std;
/*不使用除法，这怎么做，构造前缀和后缀的组合？但是这样需要两次遍历+一些动态规划*/
class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        int length = nums.size();
        vector<int> L(length, 1);
        vector<int> R(length, 1);
        // 填充前缀 利用动态规划 L[i]存放着到i-1为止的前缀和
        for (size_t i = 1; i < length; i++)
        {
            L[i] = nums[i - 1] * L[i - 1];
        }
        // 填充后缀 R[i]存放着从后到i+1的后缀和
        for (int i = length - 2; i >= 0; i--)
        {
            R[i] = nums[i + 1] * R[i + 1];
        }
        for (size_t i = 0; i < length; i++)
        {
            nums[i] = L[i] * R[i];
        }
        return nums;
    }
};

/*空间复杂度为O（1）的做法,少了一重循环，同时更快了*/
class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        int length = nums.size();
        vector<int> ans(length, 1);
        for (int i = 1; i < length; i++)
        {
            ans[i] = nums[i - 1] * ans[i - 1];
        }
        int R = 1; //用来记录后缀和
        for (int i = length - 1; i >= 0; --i)
        {
            ans[i] *= R;
            R *= nums[i];
        }
        return ans;
    }
};