//给定一个不含重复数字的数组nums,返回其所有可能的全排列。你可以按任意顺序返回答案。
#include <vector>
#include <queue>
using namespace std;
/*递归
如何保证数组中每个元素只选取了一次呢,在原数组基础上直接交换!*/
class Solution
{
public:
    void backTrack(vector<vector<int>> &ans, vector<int> nums, int first, int len)
    {
        if (first==len)
        {
            ans.emplace_back(nums);
            return;
        }
        for (size_t i = first; i < len; ++i)
        {
            //对first和i位置的交换，可以理解为循环用剩下的值填入到当前i的位置,考虑了所有的组合
            swap(nums[i],nums[first]);
            backTrack(ans,nums,first+1,len);//first+1,位置+1，递归填下一个数
            swap(nums[first],nums[i]);
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<vector<int>> ans;
        backTrack(ans,nums,0,(int)nums.size());
        return ans;
    }
};