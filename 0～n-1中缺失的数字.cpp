/*一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。
在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。
*/
#include<vector>
#include<iostream>
using namespace std;
//二分法：注意如何寻找判断条件。数组是递增且数字唯一的，可以判断是否相等。
//如果数组的数组递增，且不唯一，可以判断是否大于等于等。
class Solution {
public:
    //注意递增排序数组中是从0开始的
    int missingNumber(vector<int>& nums) {
        if (nums.size() == 0)//空容器直接返回
            return 0;
        int begin = 0;
        int end = nums.size() - 1;
        if (nums[end] == (nums[begin] + end))//数组是否连续
        {
            if (nums[begin] != 0)//开头不为0，直接返回0
                return 0;
            return nums[end] + 1;//连续且开头没丢失
        }
        while (begin <= end)
        {
            int middle = (begin + end) / 2;
            if (nums[middle] == middle)//[begin,middle]之间没有缺失,缺失范围还在右边
                begin = middle + 1;
            else//缺失范围在[begin,middle]之间
                end = middle - 1;
        }
        return nums[0]+begin;
    }
};
/*简单方法：循环判断n[i]是否等于i*/
int main()
{
    vector<int> nums = {0,1,2,3,4,5,6,7,9};
    //vector<int> nums = { 0,1, 2 };
    Solution plan;
    int s = plan.missingNumber(nums);
    cout << "miss is = " << s << endl;
    return 0;
}