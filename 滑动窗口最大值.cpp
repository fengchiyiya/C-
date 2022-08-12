// 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。
// 滑动窗口每次只向右移动一位。返回 滑动窗口中的最大值 。
#include <vector>
#include <queue>
using namespace std;
/*需要注意滑动窗口内的最大值和下标，下标出了滑动窗口需要重新计算*/
/*优先队列  这种数组的最值问题，可以使用优先队列解决
不用手动寻找局部最大值
 */
class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int length = nums.size();
        priority_queue<pair<int, int>> q; // 存放元素和下标
        for (size_t i = 0; i < k; i++)
        {
            q.emplace(nums[i], i);
        }
        vector<int> ans;
        ans.push_back(q.top().first);
        for (size_t i = k; i < length; i++)
        {
            q.emplace(nums[i], i);
            if (q.top().second <= i - k)
                q.pop();
            ans.push_back(q.top().first);
        }
        return ans;
    }
};

/*单调队列
这种问题，记录下标更管用*/
class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> ans;
        // 从前往后将下标值按照从大到小排列
        deque<int> q;
        for (int i = 0; i < k; i++)
        {
            while (!q.empty() && nums[i] >= nums[q.back()])
                q.pop_back();
            q.push_back(i);
        }
        ans.push_back(nums[q.front()]);
        for (size_t i = k; i < n; i++)
        {
            while (!q.empty() && nums[i] >= nums[q.back()])
                q.pop_back();
            q.push_back(i);
            while (!q.empty() && q.front() <= i - k)
            {
                q.pop_front();
            }
            ans.push_back(nums[q.front()]);
        }
        return ans;
    }
};
/*分块+预处理*/
class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> prefix(n), suffixMax(n);
        vector<int> ans(n - k + 1);
        // 分组存放前缀和
        for (size_t i = 0; i < n; i++)
        {
            if (i % k == 0) // 以窗口的起点区分
                prefix[i] = nums[i];
            else
                prefix[i] = max(prefix[i - 1], nums[i]);
        }
        // 分组存放后缀和
        for (int i = n - 1; i >= 0; --i)
        {
            if (i == n - 1 || (i + 1) % k == 0) // 以窗口的后边界区分,注意%符号的优先级比+高，先运算
                suffixMax[i] = nums[i];
            else
                suffixMax[i] = max(nums[i], suffixMax[i + 1]);
        }
        // 这样划分，保证了前缀和后缀分组一样
        // i 代表滑动窗口的起点。
        // i 如果不为k的整数倍，则局部最大值，一定是上一数组i,j-1的后缀最大值和j,i+k-1的前缀之间
        for (size_t i = 0; i <= n - k; i++)
        {
            ans[i] = max(suffixMax[i], prefix[i + k - 1]);
        }
        return ans;
    }
};
