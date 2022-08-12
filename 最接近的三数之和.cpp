//给你一个长度为n的整数数组nums和一个目标值target。
//请你从nums中选出三个整数，使它们的和与target 最接近。返回这三个数的和。
//假定每组输入只存在恰好一个解。
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/*双指针+排序
* 只不过这次得第二重循环不能简单得直接使用for循环，需要使用while循环，手动控制索引的增长
* 双指针的用法和寻找最大的水箱用法类似
* 因为是寻找最接近的，所有对每次索引变化情况，都需要进行求和判断
*/
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        int difference = INT_MAX;
        int sum = 0;
        sort(nums.begin(), nums.end());
        for (size_t first=0; first <n ; ++first)
        {
            //first得与前一个first值不同
            if (first > 0 && nums[first] == nums[first - 1])
                continue;
            int third = n - 1;
            int dis= INT_MAX;
            int second = first + 1;
            while (second<third)
            {
                if (second > first + 1 && nums[second] == nums[second - 1])
                {
                    second++;
                    continue;
                }
                int _sum = nums[first] + nums[second] + nums[third];
                dis = abs(target - _sum);
                cout << "second = " << second << " ,third = " << third << endl;
                if (difference > dis)
                {
                    cout << nums[first] << " , " << nums[second] << " , " << nums[third] << endl;
                    difference = dis;
                    sum = _sum;
                }
                if (_sum >= target)
                {
                    third--;
                    continue;
                }
                if (second == third)
                    break;
                if (difference == 0)
                    break;
                second++;
            }
            if (difference == 0)
                break;
        }
        return sum;
    }
};
int main()
{
    //vector<int> v{ -1,2,1,-4 };
    //vector<int> v{ -1,0,1,2,-1,-4 };
    //vector<int> v{ 1,1,-1,-1,3 };
    vector<int> v{ 1,1,1,1 };
    int target = 4;
    Solution plan;
    auto x = plan.threeSumClosest(v, target);
    cout << "x = " << x << endl;
    return 0;
}