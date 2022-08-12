// 给定一个未排序的整数数组nums，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
// 请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
#include <vector>
#include <queue>
using namespace std;
/*优先队列:默认从大到小排序
priority_queue<int,vector<int>,greater<int> > q;改为从小到大排列*/
class Solution
{
    priority_queue<int> q;

public:
    int longestConsecutive(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        for (const auto &n : nums)
        {
            q.push(n);
        }
        int maxLength = 1, subLength = 1;
        auto prev = q.top();
        q.pop(); //从头开始的pop
        while (!q.empty())
        {
            auto curr = q.top();
            q.pop();
            if (curr == prev - 1)
                subLength++;
            else if (curr == prev)
                prev = curr;
            else
                subLength = 1;
            maxLength = max(maxLength, subLength);
            prev = curr;
        }
        return maxLength;
    }
};
/*哈希表和优先队列的耗费时间差不多*/
#include <unordered_set>
class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        unordered_set<int> nums_set;
        for (const auto &num : nums)
        {
            nums_set.insert(num);
        }
        int maxLength = 0;
        for (const auto &c : nums_set)
        {
            // c-1不存在，需要重新计数,如果存在，内部循环也已经执行过了，直接不做任何操作
            if (!nums_set.count(c - 1)) 
            {
                int currentNum = c;//记录当前值
                int currL = 1;
                while (nums_set.count(currentNum + 1))
                {
                    ++currL;
                    ++currentNum;
                }
                maxLength = max(maxLength, currL);
            }
        }
        return maxLength;
    }
};
class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        unordered_set<int> num_set;
        for (const int &num : nums)
        {
            num_set.insert(num);
        }

        int longestStreak = 0;

        for (const int &num : num_set)
        {
            if (!num_set.count(num - 1))
            {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.count(currentNum + 1))
                {
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = max(longestStreak, currentStreak);
            }
        }
        return longestStreak;
    }
};
