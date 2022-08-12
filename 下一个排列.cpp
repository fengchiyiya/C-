//整数数组的一个排列就是将其所有成员以序列或线性顺序排列。
//例如，arr=[1,2,3],以下这些都可以视作arr的排列：[1,2,3],[1,3,2],[3,1,2],[2,3,1]
//整数数组的下一个排列是指整数的下一个字典序更大的排列。
//例如arr[1,2,3]的下一个排列是[1,3,2]
//必须原地修改,找出nums的下一个排列
#include <vector>
using namespace std;
/*两遍扫描法
我们希望下一个数比当前数大，这样才满足“下一个排列”的定义。因此只需要将后面的大数与前面的小数交换
我们还希望下一个数增加的幅度尽可能的小，我们需要
1.在尽可能靠右的低位进行交换，需要从后向前查找
2.将一个尽可能小的大数与前面的小数交换
3.将大数换到前面后，需要将大数后面的所有数重置为升序，升序排列就是最小的排列
*/

class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        //从后往前找第一个不满足降序排列的数,nums[i]>=nums[i+1]降序
        int i = nums.size() - 2;
        while (i >= 0 && nums[i] >= nums[i + 1])
        {
            i--;
        }
        //从后往前找第一个大于nums[i]的数
        if (i >= 0)//注意i可能为0
        {
            int j = nums.size() - 1;
            while (j >= 0 && nums[j] <= nums[i])
            {
                j--;
            }
            swap(nums[i], nums[j]);
        }
        reverse(nums.begin() + i + 1, nums.end());
    }
};