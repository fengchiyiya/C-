// 给你一个整数数组nums，数组中的元素互不相同。返回该数组所有可能的子集（幂集）。
// 解集不能包含重复的子集。你可以按任意顺序返回解集。
#include <vector>
using namespace std;
/*递归，大致思路有了，但是还是有些细节有问题，本次递归不能在循环里递归，循环会有重复数字，
循环递归的结果是所有数字的不同组合（包含所有数字的组合，只是顺序不同）
直接利用id，当id=nums.size,退出
递归过程考虑取不取当前id的元素*/
class Solution
{
public:
    //利用id保证不会重复
    void searchSubsets(vector<vector<int>> &ans, vector<int> &temp, vector<int> &nums, int id)
    {
        if (id == nums.size())
        {
            ans.push_back(temp);
            return;
        }
        temp.push_back(nums[id]);
        searchSubsets(ans, temp, nums, id + 1); //递归取nums[id]
        temp.pop_back();
        searchSubsets(ans, temp, nums, id + 1); //递归不取nums[id]
    }
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> ans;
        vector<int> temp;
        searchSubsets(ans, temp, nums, 0);
        return ans;
    }
};
/*迭代法实现子集枚举
0/1序列对应的二进制数正好从0到2^n-1。
0~2^n-1正好是容器的排列组合的个数
*/
class Solution
{
public:
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> ans;
        int n=nums.size();
        for (int mask = 0; mask <(1<<n); ++mask)
        {
            vector<int> temp;
            for (int i = 0; i < n; i++)
            {
                if(mask&(1<<i))//检查一共有几个1
                    temp.push_back(nums[i]);
            }
            ans.push_back(temp);
        }
        return ans;
    }
};