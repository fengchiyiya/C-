/*把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
给你一个可能存在 重复 元素值的数组 numbers ，它原来是一个升序排列的数组，
并按上述情形进行了一次旋转。请返回旋转数组的最小元素。
例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一次旋转，该数组的最小值为 1。  
注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。
*/
#include<vector>
#include<iostream>
using namespace std;
//class Solution {
//public:
//    int minArray(vector<int>& numbers) {
//        int min = numbers[0];
//        for (size_t i = 1; i < numbers.size(); ++i)
//        {
//            if (numbers[i] < min)
//                min = numbers[i];
//        }
//        return min;
//    }
//};
//二分查找
/*排序数组的查找问题首先考虑使用二分法解决，其可将遍历法的线性级别时间复杂度降低至对数级别。
* 初始化： 声明 i, j 双指针分别指向 numsnums 数组左右两端；
循环二分： 设 m = (i + j) / 2m=(i+j)/2 为每次二分的中点（ "/" 代表向下取整除法，因此恒有 i \leq m < ji≤m<j ），可分为以下三种情况：
当 nums[m] > nums[j]nums[m]>nums[j] 时： m 一定在 左排序数组 中，即旋转点x一定在 [m + 1, j][m+1,j] 闭区间内，因此执行 i = m + 1=m+1；
当 nums[m] < nums[j]nums[m]<nums[j] 时： m 一定在 右排序数组 中，即旋转点x一定在[i, m][i,m] 闭区间内，因此执行 j = m=m；
当 nums[m] = nums[j]nums[m]=nums[j] 时： 无法判断 m 在哪个排序数组中，即无法判断旋转点x在 [i, m][i,m] 还是 [m + 1, j][m+1,j] 区间中。解决方案： 执行 j = j - 1j=j−1 缩小判断范围。
*/
class Solution {
public:
    int minArray(vector<int>& numbers) {
        int begin = 0;
        int end = numbers.size() - 1;
        while (begin<end)
        { 
            int middle = (begin + end) / 2;
            if (numbers[middle] > numbers[end])//middle比end大，说明最小值x在[m+1,j]闭区间
                begin = middle+1;//确定middle不是最小值，可以直接+1
            else if(numbers[middle]<numbers[end])//middle比end小，说明最小值x在[i,m]闭区间   
            {
                end = middle;//为什么不是middle-1
                //当middle是最小值时，middle-1会错过最小值。
            }
            else if(numbers[middle] == numbers[end])//要么[begin,middle]为相同元素，要么[middle,end]为相同元素
            {
                end = end - 1;
            }
        }
        return numbers[begin];
    }
};
int main()
{
    //vector<int> numbers{ 3,4,5,1,2 };
    vector<int> numbers{ 3,1,3 };
    //vector<int> numbers{ 2,2,2,0,1 };
    Solution plan;
    int res = plan.minArray(numbers);
    cout << "res = " << res << endl;
    return 0;
}