// 假设有打乱顺序的一群人站成一个队列，数组 people 表示队列中一些人的属性（不一定按顺序）。
// 每个 people[i] = [ hi, ki ] 表示第 i 个人的身高为 hi ，前面 正好 有 ki 个身高大于或等于 hi 的人。
// 请你重新构造并返回输入数组 people 所表示的队列。返回的队列应该格式化为数组 queue ，
// 其中 queue[j] = [ hj, kj ] 是队列中第 j 个人的属性（queue[0] 是排在队列前面的人）。
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
/* 题意实际就是按照编号排列
从高到低考虑：按照hi为第一关键字降序，ki为第二关键字升序。
我们可以采用「插空」的方法，依次给每一个人在当前的队列中选择一个插入的位置。
也就是说，当我们放入第 i 个人时，只需要将其插入队列中，使得他的前面恰好有 ki个人即可。
思路好巧妙啊，有了思路几行代码就行了。
*/
class Solution
{
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
    {
        //排序
        sort(people.begin(), people.end(), [](const vector<int> &u, const vector<int> &v)
             { return u[0] > v[0] || (u[0] == v[0] && u[1] < v[1]); });
        vector<vector<int>> ans;
        for (const auto &person : people) // 外层 O(n)
        {
            //在中间的插入删除操作，还会造成内存块的拷贝，同时还会使迭代器失效
            ans.insert(ans.begin() + person[1], person); // 内层插入最坏的情况下为O(n)
        }
        return ans;
    }
};
