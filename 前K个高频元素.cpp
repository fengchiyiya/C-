// 给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
/*比较容易想到哈希表+优先队列
优先队列默认是从小到大排列的,使用大根堆
问题在于优先队列如何存储,好像需要两遍循环，一遍循环不能存储优先队列
仿函数的几种用法：
    1.在类内重载符号函数,类内形参必须声明const
    2.定义比较大小的函数，使用双形参
    3.使用lambda表达式
    4.使用function文件定义仿函数
    5.使用函数指针
    其中lambda和函数指针，需要使用decltype获得类型值
    */

/*关于priority,如果使用了自定义的仿函数
那么在函数类型时，需要定义3个形参：元素的类型值，存储元素的容器类型，仿函数类型(decltype获取)
*/
class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> map; // val,count;
        auto Cmp = [&map](const int &a, const int &b)
        { return map[a] >= map[b]; };
        for (int i = 0; i < nums.size(); i++)
        {
            map[nums[i]]++;
        }
        priority_queue<int, vector<int>, decltype(Cmp)> q(Cmp); // lambda的类型值使用decltype获取
        for (auto begin = map.begin(); begin != map.end(); begin++)
        {
            q.push(begin->first); // 存入元素值
        }

        vector<int> ans;
        for (size_t i = 0; i < k; i++)
        {
            auto n = q.top();
            q.pop();
            ans.emplace_back(n);
        }
        return ans;
    }
};