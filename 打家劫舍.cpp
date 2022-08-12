// 你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
// 影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，
// 系统会自动报警。给定一个代表每个房屋存放金额的非负整数数组，计算你不触动警报装置的情况下，
// 一夜之内能够偷窃到的最高金额。
#include <vector>
#include <iostream>
using namespace std;
/*
动态规划+滚动数组
dp[i]=dp[i-2]
对题意的理解还是不够深刻，在每个时刻只需要存储前两间房屋的最高总金额就行，
因为相邻的关系，两间房不能连续，second = max(first + nums[i], second);比较巧妙
*/
class Solution
{
public:
    int rob(vector<int> &nums)
    {
        if(nums.empty())
        return 0;
        if(nums.size()==1)
            return nums[0];
        int n=nums.size();
        int first=nums[0],second=max(nums[0],nums[1]);
        //first记载非相邻的屋子的最大金额
        for (int i = 2; i < n; i++)
        {
            int temp=second;
            second=max(first+nums[i],second);
            first=temp;
        }
        return second;
    }
};
int main()
{
    // vector<int> v={2,1,1,2};
    vector<int> v = {1, 3, 1, 3, 100};
    Solution plan;
    int n = plan.rob(v);
    cout << "n = " << n << endl;
    return 0;
}