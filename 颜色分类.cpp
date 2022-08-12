//给定一个包含红色、白色和蓝色、共n个元素的数组nums，原地对它们进行排序，
//使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
//我们使用整数0、1和2分别表示红色、白色和蓝色。
//必须在不使用库的sort函数的情况下解决这个问题。
#include <vector>
#include <iostream>
using namespace std;
/*快速排序,注意快速排序不会保持相对关系不变
将比分界值的小的放在左边，大于等于分界值得放在右边
当选取最左边的元素为基准元素时，先移动的指针一定要是右边的指针。*/
class Solution
{
public:
    void quickSort(vector<int> &arr, int left, int right)
    {
        if(left>=right)
            return;
        int i=left,j=right;
        int key=arr[left];
        while (i<j)
        {
            while(i<j&&arr[j]>=key)//右边找小于key的数
                --j;
            while (i<j&&arr[i]<=key)//左边找大于key的数
                ++i;
            if(i<j)
                swap(arr[i],arr[j]);
        }
        swap(arr[i],arr[left]);//将基准值放入原来的位置
        quickSort(arr,left,i-1);
        quickSort(arr,i+1,right);
    }

    void sortColors(vector<int> &nums)
    {
        quickSort(nums, 0, nums.size() - 1);
    }
};

/*双指针，因为本题只有3种颜色，可以使用这个
一个指向开头，一个指针指向结尾，
当元素为2时，直接与结尾指针交换，结尾指针--
当元素为0时，直接与开头指针交换。开头指针++*/
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int p0 = 0, p2 = n - 1;
        for (int i = 0; i <= p2; ++i) {
            while (i <= p2 && nums[i] == 2) {
                swap(nums[i], nums[p2]);
                --p2;
            }
            if (nums[i] == 0) {
                swap(nums[i], nums[p0]);
                ++p0;
            }
        }
    }
};