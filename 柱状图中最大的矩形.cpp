//给定n个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为1 。
//求在该柱状图中，能够勾勒出来的矩形的最大面积。
#include <vector>
#include <stack>
using namespace std;
/*单调栈 接水等问题，容易想到单调栈，主要是怎么找到边界
单调栈的模型是在一维数组中对每一个数找到第一个满足某种条件的数。
*/
class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int n = heights.size();
        //分别寻找i左侧、右侧小于其高度的柱子位置
        vector<int> left(n), right(n);
        stack<int> stk;
        for (int i = 0; i < n; ++i)
        {
            while (!stk.empty() && heights[stk.top()] >= heights[i])
            {
                stk.pop();
            }
            left[i] = (stk.empty() ? -1 : stk.top());
            stk.push(i);
        }
        stk = stack<int>(); //快速清空栈
        for (int i = n - 1; i >= 0; --i)
        {
            while (!stk.empty() && heights[stk.top()] >= heights[i])
            {
                stk.pop();
            }
            right[i] = (stk.empty() ? n : stk.top());
            stk.push(i);
        }
        int maxArea = -1;
        //-1和n为虚拟柱，代表宽度，不会影响结果，因为肯定可以延申出去
        for (size_t i = 0; i < n; ++i)
        {
            maxArea = max((right[i] - left[i] - 1) * heights[i], maxArea);
        }
        return maxArea;
    }
};
/*单调栈+常数优化
一次遍历，在入栈时确定左边界，出栈时确定右边界
这里求的是小于等于，最右侧的那根柱子是可以求出正确的右边界*/
class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        int n = heights.size();
        //右边界的元素不一定会被填满，没填的都是n，所以用n初始化
        vector<int> left(n), right(n, n);

        stack<int> mono_stack;
        for (int i = 0; i < n; ++i)
        {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i])
            {
                right[mono_stack.top()] = i;//如果栈顶的高度大于i的高度，那么栈顶的元素的右边界一定为i
                mono_stack.pop();
            }
            left[i] = (mono_stack.empty() ? -1 : mono_stack.top());//保证栈底元素为-1
            mono_stack.push(i);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
        }
        return ans;
    }
};