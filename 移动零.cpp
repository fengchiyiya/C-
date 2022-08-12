// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
// 请注意 ，必须在不复制数组的情况下原地对数组进行操作。
#include <vector>
using namespace std;
/*本题使用双指针
自己的想法有点类似，因为题目要求在原数组操作，同时保持非零元素的相对位置。
将非0元素与右边不是0的元素一直交换
左指针指向已经处理号的序列的尾部，右指针指向待处理序列的头部
有点难理解，简单的，可以将非0数，依次前移，最后剩下的位置覆盖为0。
*/
class Solution
{
public:
    void moveZeros(vector<int> &nums)
    {
        int n = nums.size();
        int left = 0, right = 0;
        while (right < n)
        {
            // right 依次数组中的非0数
            // left 必然指向0
            // 如果left 不指向0，则意味着left和right之间必然还有个非0数，这是不对的
            // 正常情况下，right=left+1，两者发生交换，则0元素交换到right的位置
            // 如果，right=left+n,则中间n个元素必然为0，否则会发生交换
            if (nums[right])
            {
                swap(nums[right], nums[left]);
                left++;
            }
            right++;
        }
    }
};
