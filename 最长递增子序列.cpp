// 给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
// 子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
// 例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
#include <vector>
#include <algorithm>
using namespace std;
/* 动态规划
第一想法就是动态规划，dp[i]存放以i结尾的递增子序列的长度
有问题，如果开头的第二个数太大了，就会错误计算递增
一重循环似乎不太行，需要二重循环
dp[j]=max{dp[i]}+1;
注意返回值不是dp[n-1],而应该是dp中最大值
*/
class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        vector<int> dp(n, 0);
        dp[0] = 1;
        for (size_t i = 1; i < n; i++)
        {
            int currMax = 0;
            for (size_t j = 0; j < i; j++)
            {
                if (nums[j] < nums[i])
                    currMax = max(currMax, dp[j]);
            }
            dp[i] = currMax + 1;
        }
        // max_element返回容器中最大元素的指针
        return *max_element(dp.begin(), dp.end());
    }
};
/*贪心+二分查找
贪心一直没怎么练习过，这道题使用贪心更好
设当前已求出的最长上升子序列的长度为len，从前往后遍历数组nums,在遍历到nums[i]时：
    如果nums[i]>d[len],则直接加入到d数组末尾，并更新len=len+1；
    否则，在d数组中二分查找，找到最大的比nums[i]小的数d[k],并更新d[k+1]=nums[i]
*/
class Solution
{
public:
    int lengthOfLIS(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        vector<int> dp(n + 1, 0); // dp从小到大排列的
        int len = 1;
        dp[1] = nums[0];
        for (size_t i = 1; i < n; i++)
        {
            if (nums[i] > dp[len])
            {
                dp[++len] = nums[i];
            }
            else //二分法找到最大的一个比i小的值
            {
                int l = 1, r = len, pos = 0; // 当没有找到时，需要pos将初始位置值改变
                while (l < r)
                {
                    int mid = (l + r) >> 1;
                    if (dp[mid] < nums[i]) // 注意是在dp里面寻找nums[i]，不是在nums里面寻找
                    {
                        pos = mid;
                        l = mid + 1;
                    }
                    else
                        r = mid - 1;
                }
                dp[pos + 1] = nums[i];
            }
        }
        return len;
    }
};