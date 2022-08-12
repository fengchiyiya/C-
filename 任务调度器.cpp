// 给你一个用字符数组 tasks 表示的 CPU 需要执行的任务列表。其中每个字母表示一种不同种类的任务。
// 任务可以以任意顺序执行，并且每个任务都可以在 1 个单位时间内执行完。
// 在任何一个单位时间，CPU 可以完成一个任务，或者处于待命状态。
// 然而，两个 相同种类 的任务之间必须有长度为整数 n 的冷却时间，
// 因此至少有连续 n 个单位时间内 CPU 在执行不同的任务，或者在待命状态。
// 你需要计算完成所有任务所需要的 最短时间 。
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <numeric>
using namespace std;
/*这类问题在于如何选择。
参考桶思想，建立大小为n+1的桶子，个数为任务数量最多的那个任务，等待时间n=2；
我们可以建立6个桶子，每个容量为3;
把一个桶子看做一轮任务。
没有其他任务，完成任务A所需的时间为（6-1）*(n+1)+1
有其他任务，总的排队时间=（桶个数-1）*（n+1)+最后一桶的任务数
如果桶满了，但是任务还没排完，可以临时扩充某些桶的大小
此时，总的排队时间为tasks.size()。因为此时不可能会有空闲时间。*/
/*static_cast静态类型转换：比较安全，除了内置类型，还可用于父类转子类
dynamic_cast动态类型转换：用于子类转父类，不可用于内置类型转换
 */
class Solution
{
public:
    int leastInterval(vector<char> &tasks, int n)
    {
        unordered_map<char, int> mp;
        for (const auto &c : tasks)
        {
            mp[c]++;
        }
        // 统计最多的执行次数
        // 这种unorder_map存放的元素类型，不知道怎么描述用auto就行
        // max_element返回的是迭代器
        int cnt = max_element(mp.begin(), mp.end(), [](const auto &u, const auto &v)
                              { return u.second < v.second; })
                      ->second;
        //统计最多的任务的种类
        // lambda的[=],是因为acc吗，acc代表之前的和
        int maxCount = accumulate(mp.begin(), mp.end(), 0, [=](int acc, const auto &u)
                                  { return acc + (u.second == cnt); });
        return max((cnt - 1) * (n + 1) + maxCount, static_cast<int>(tasks.size()));
    }
};
