//给定一个按照升序排列的整数数组nums，和一个目标值target。找出给定目标值在数组中的开始位置和结束位置。
//如果数组中不存在目标值target，返回[-1, -1]。
#include <vector>
#include <iostream>
using namespace std;
//题目要求时间复杂度为O(logn)的算法，优先想到二分法
class Solution
{
public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        vector<int> v{-1, -1};
        if (nums.empty())
            return v;
        if (nums.size() == 1)
        {
            if (nums[0] == target)
                v[0] = v[1] = 0;
            else
                return v;
        }
        int begin = 0, end = nums.size() - 1;
        while (begin < end)//二分法要注意，两端加起来是一个完整的整体，比如[0,m],[m+1,n]
        {
            int mid = (begin + end) >> 1;
            if (nums[mid]<target)
            begin=mid+1;
            else//nums[mid]>=target
            end=mid;
        }//退出循环时，begin=第一个位置
        if(nums[begin]==target)
        {
            v[0]=v[1]=begin;
            for (size_t i = begin+1; i < nums.size(); ++i)
            {
                if(nums[i]==target)
                v[1]=i;
            }
        }
        return v;
    }
};
int main()
{
    vector<int> v{1};
    int target = 0;
    Solution plan;
    auto n = plan.searchRange(v, target);
    cout << "n = " << n[0] << ", " << n[1] << endl;
    return 0;
}