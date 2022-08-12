//以数组intervals表示若干个区间的集合，其中单个区间为intervals[i] = [starti, endi] 。
//请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
/*感觉需要先排序，再经过一次遍历
和我想的差不多，但是没写出来！！
如何确定区间重合，需要插入和修改配合使用！
首先，我们将列表中的区间按照左端点升序排序。然后我们将第一个区间加入 merged 数组中，
并按顺序依次考虑之后的每个区间：如果当前区间的左端点在数组merged中最后一个区间的右端点之后，
那么它们不会重合，我们可以直接将这个区间加入数组merged的末尾；
否则，它们重合，我们需要用当前区间的右端点更新数组merged中最后一个区间的右端点，
将其置为二者的较大值。*/
class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        int n = intervals.size();
        if (n == 0)
            return {};
        vector<vector<int>> ans;
        sort(intervals.begin(), intervals.end()); //基础类型即使放在容器里，STL也可以直接比较大小
        for (size_t i = 0; i < n; i++)
        {
            int L = intervals[i][0], R = intervals[i][1];
            if (ans.empty()|| ans.back()[1] < L)//如果容器为空或者上一区间的结尾小于下一区间的开头
            {
                ans.push_back({L, R});
            }
            else//上一区间的结尾大于等于下一区间的开头
            {
                ans.back()[1]=max(ans.back()[1],R);//修改区间结尾为两者中最大的，因为是按开头排序的，后面的开头一定大于等于前面的区间开头
            }
        }
        return ans;
    }
};
int main()
{
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    Solution plan;
    plan.merge(intervals);
    return 0;
}