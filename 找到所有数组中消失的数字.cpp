// 给你一个含 n 个整数的数组 nums ，其中 nums[i] 在区间 [1, n] 内。
// 请你找出所有在 [1, n] 范围内但没有出现在 nums 中的数字，并以数组的形式返回结果。
// 你能在不使用额外空间且时间复杂度为 O(n) 的情况下解决这个问题吗? 你可以假定返回的数组不算在额外空间内。
#include <vector>
using namespace std;
/*先排序，再然后一次遍历,但是排序会超时，或者使用哈希表记录*/

/*本题可以利用数组代替哈希表统计，方法很巧妙
具体来说，遍历 nums，每遇到一个数 x，就让 nums[x−1] 增加 n。由于 nums 中所有数均在 [1,n] 中，增加以后，这些数必然大于 n。
最后我们遍历 nums，若 nums[i] 未大于 n，就说明没有遇到过数 i+1。这样我们就找到了缺失的数字。
注意，当我们遍历到某个位置时，其中的数可能已经被增加过，因此需要对 n 取模来还原出它本来的值。
*/
class Solution
{
public:
    vector<int> findDisappearedNumbers(vector<int> &nums)
    {
        int n = nums.size();
        for (size_t i = 0; i < n; i++)
        {
            // 取模还原本来值，-1得到下标索引值
            int x = (nums[i] - 1) % n; // -操作，最好放在%之前，因为nums[i]-1后再取值不会出现负数
            nums[x] += n;
        }
        vector<int> ans;
        for (size_t i = 0; i < n; i++)
        {
            if (nums[i] <= n)
                ans.emplace_back(i + 1);
        }
        return ans;
    }
};
#include <iostream>
int main()
{
    int a = -1;
    int b = a % 8;
    // 负数对正数取余依旧是负数
    cout << "b = " << b << endl;
}