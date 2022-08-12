//整数数组 nums 按升序排列，数组中的值 互不相同 。
//在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，
//使数组变为[nums[k],nums[k+1], ...,nums[n-1],nums[0],nums[1],...,nums[k-1]]（下标从0开始计数）。
//例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
//给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。
#include <vector>
#include <iostream>
using namespace std;
/*二分法
将数组一分为二，其中一定有一个是有序的，另一个可能是有序，也能是部分有序。
此时有序部分用二分法查找。无序部分再一分为二，其中一个一定有序，另一个可能有序，可能无序。就这样循环.
二分法当begin=end时，就退出循环了，需要在循环外面单独判断一下，或者循环时加个等号
*/
/*复习一下二分法查找旋转数组的最小值
最小值左侧的元素肯定大于等于最后一个元素；最小值右侧的元素肯定小于等于最后一个元素
1.当中点大于终点元素时，中点位于最小值左侧元素，则放弃中点左侧元素
2.当中点小于终点元素时，中点位于最小值右侧元素，则放弃中点右侧元素
3.当中点等于终点元素，将中点与终点前一个元素比较（因为终点元素已经有了替代品）。
*/
class Solution
{
public:
    int minArray(vector<int> &nums)
    {
        int begin = 0, end = nums.size() - 1;
        while (begin < end)
        {
            int mid = begin + (end - begin) / 2; //避免溢出
            if (nums[mid] > nums[end])           //中点大于终点，中点位于最小值左侧，最小值位于[mid+1,end]
            {
                begin = mid + 1; //因为nums[mid]>nums[end],mid不可能是最小值的索引
            }
            else if (nums[mid] < nums[end]) //中点小于终点，中点位于最小值右侧，最小值位于[0,mid]
            {
                end = mid;
            }
            else if (nums[mid] == nums[end]) //中点和终点相等，将终点前移，缩小范围
            {
                end = end - 1;
            }
        }
        return begin;
    }
    //每次都数组一分为2，其中一定有一组是有序的，一组是无序的
    //此时有序部分用二分法查找，无序部分再一分为2.
    int binarySearch(vector<int> &nums, int begin, int end, int target)
    {
        if (nums[begin] > target || nums[end] < target)
        {
            return -1;
        }
        while (begin <= end) //这里不加等号，则循环结束时，需要单独判断一下，能不能加等号，需要斟酌一下
        {
            int mid = begin + (end - begin) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[mid] < target) // target可能在[mid+1,end]
                begin = mid + 1;
            else // target可能在[begin,mid]
                end = mid;
        }
        // if(nums[begin]==target)
        //     return begin;
        return -1;
    }
    int search(vector<int> &nums, int target)
    {
        int begin = 0, end = nums.size() - 1;
        if (begin == end) //只有一个元素
        {
            if (nums[begin] == target)
                return begin;
        }
        while (begin < end) //这里不加等号，则循环结束时，需要单独判断一下
        {
            // cout<<"search"<<endl;
            // cout<<"begin = "<<begin<<endl;
            // cout<<"end = "<<end<<endl;
            int mid = begin + (end - begin) / 2;
            if (nums[mid] < nums[end]) //中点位于最小值右侧，即中点右侧是有序数组
            {
                auto x = binarySearch(nums, mid, end, target);
                if (x != -1)
                    return x;
                end = mid;
            }
            else if (nums[mid] > nums[end]) //中点位于最小值左侧，即中点左侧是有序数组
            {
                auto x = binarySearch(nums, begin, mid, target);
                if (x != -1)
                    return x;
                begin = mid + 1;
            }
            else
                end = end - 1;
        }
        if (nums[begin] == target)
            return begin;
        return -1;
    }
};
class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        int n = nums.size();
        if (!n)
            return -1;
        if (n == 1)
            return (nums[0] == target ? 0 : -1);
        int l = 0, r = n - 1;
        while (l<=r)
        {
            int mid=(l+r)>>1;
            if(nums[mid]==target)
                return mid;
            if(nums[0]<=nums[mid])//中值大于起点，中值位于最小值左侧
            {
                if(nums[0]<=target&&nums[mid]>target)
                {
                    r=mid-1;
                }
                else
                {
                    l=mid+1;
                }
            }
            else//中值小于起点，中值位于最小值右侧
            {
                if(nums[mid]<=target&&nums[n-1]>target)//target可能在[mid+1,n-1]之间
                {
                    l=mid+1;
                }
                else
                {
                    r=mid-1;
                }
            }
        }
        return -1;
    }
};
int main()
{
    // vector<int> v{4, 5, 6, 7, 0, 1, 2};
    vector<int> v{3, 1};
    Solution plan;
    int target = 1;
    auto n = plan.search(v, target);
    cout << "n =" << n << endl;
    return 0;
}