// 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n），可知至少存在一个重复的整数。
// 假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。
// 你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。
// 提示：
// 1 <= n <= 105
// nums.length == n + 1
// 1 <= nums[i] <= n
// nums 中 只有一个整数 出现 两次或多次 ，其余整数均只出现 一次
#include <vector>
using namespace std;
// 排序 + 一次编列？ 快速排序或者堆排序  但是都不是这道题的最好解决办法
/*快慢指针
对nums数组建图，因为只有一个元素值重复，但是可以重复多次,则链表必然存在环
并且下标长度 >= 元素的最大值
*/
class Solution
{
public:
    int findDuplicate(vector<int> &nums)
    {
        int fast = 0, slow = 0;
        do
        {
            fast = nums[nums[fast]];
            slow = nums[slow];
        } while (slow != fast);
        // 两者第一相遇时，退出
        // 然后将快慢指针的速度调为一样的，将慢指针放回起点，两者再次相遇时，毕竟在环的入口处，简单的数学推导
        slow = 0;
        while (slow != fast)
        {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow; // 注意slow就是返回值，nums[slow]又迭代了一次
    }
};
/*二分查找法
 */
class Solution
{
public:
    int findDuplicate(vector<int> &nums)
    {
        int n = nums.size();
        int l = 1, r = n - 1, ans = -1;
        // 因为l从1开始，所以允许l==r(两个元素时，l==r)；从1开始是因为元素值规定了>=1
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            int cnt = 0; // 统计小于等于mid下标值的个数
            for (size_t i = 0; i < n; i++)
            {
                cnt += 1 ? nums[i] <= mid : 0;
            }
            if (cnt <= mid) // 代表mid之前的数都没问题
            {
                l = mid + 1;
            }
            else // mid有问题，细分确定值
            {
                r = mid - 1;
                ans = mid;
            }
        }
        return ans;
    }
};