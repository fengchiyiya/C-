//输入一个递增排序的数组和一个数字s，在数组中查找两个数，使得它们的和正好是s。
//如果有多对数字的和等于s，则输出任意一对即可。
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int begin = 0, end = nums.size() - 1;
        if (nums[begin] >= target || nums.empty())//开头大于target或者数组为空，直接返回
            return nums;
        vector<int> temp;
        while (begin!=end)
        {
            end = nums.size() - 1;
            while (begin<end)
            {
                if (nums[begin] + nums[end] < target)//开头加结尾都小于target，说明当前开头没有满足的；
                {
                    begin++;
                    continue;
                }
                else if (nums[begin] + nums[end] == target)
                {
                    temp.push_back(nums[begin]);
                    temp.push_back(nums[end]);
                    return temp;
                }
                end--;
            }
            begin++;
        }
        return nums;
    }
};
/*对撞双指针*/
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int begin = 0, end = nums.size() - 1;
        vector<int> temp;
        while (begin!=end)
        {
            if (nums[begin] + nums[end] == target)
            {
                temp.push_back(nums[begin]);
                temp.push_back(nums[end]);
                return temp;
            }
            else if (nums[begin] + nums[end] > target)
            {
                end--;
            }
            else
            {
                begin++;
            }
        }
        return nums;
    }
};