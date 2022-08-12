// 给你一个整数数组 nums ，你需要找出一个 连续子数组 ，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。
// 请你找出符合题意的 最短 子数组，并输出它的长度。
// 进阶：你可以设计一个时间复杂度为 O(n) 的解决方案吗？
#include <vector>
#include <iostream>
using namespace std;
/*可以先排好序，再一次遍历找子数组的起点终点，但是时间复杂度超了*/
/*两边遍历可以吗？可以！！！ 独立想出来了
从左往右找终点：当前点比之间的最大值小；
从右往左找起点：当前点比之间的最小值大*/
class Solution
{
public:
    int findUnsortedSubarray(vector<int> &nums)
    {
        int n = nums.size();
        if (n < 2)
            return 0;
        int end = 0, begin = n - 1;
        int minVal = nums[n - 1], maxVal = nums[0];
        //从左往右找终点：当前点比之间的最大值小
        for (int i = 1; i < n; i++)
        {
            // 更新最大值
            if (nums[i] >= maxVal)
            {
                maxVal = nums[i];
            }
            else
                end = i;
        }
        // 从右往左找起点：当前点比之间的最小值大
        for (int i = n - 2; i >= 0; i--)
        {
            // 更新最小值
            if (nums[i] <= minVal)
            {
                minVal = nums[i];
            }
            else
                begin = i;
        }
        cout << "begin = " << begin << " , end = " << end << endl;
        return (end - begin + 1) > 0 ? (end - begin + 1) : 0;
    }
};