//给定n个非负整数表示每个宽度为1的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
#include <vector>
using namespace std;

//感觉和盛最多水的容器有点像
/*双指针法
不同于盛最多水的容器采用双指针是从同一位置出发，
本题双指针要从头尾出发，注意只有先高中低后高才能存雨水*/
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        int ans = 0;
        while (left < right)
        {
            rightMax = max(height[right], rightMax);
            leftMax = max(height[left], leftMax);
            /*对于左指针i，它右侧的真实的最大值可能>=rightMax，对于右指针j，它左侧的真实的最大值可能>=leftMax
            当leftMax<rightMax,左侧一定可以接雨水了，右侧同理*/
            /*if(height[left]<height[right])等效于height[left]<height[right]
            left和right会交替指向leftMax和rightMax中更大的值，谁指向了最大值，谁就不用动，
            移动另一个指针，直到另一个指针指向的值更大，或者两个指针重合
            left,right可以由以下两种情况获得
            如果移动的是left指针，则height[0,left-1]<height[right]=rightMax，如果height[left]<height[right]
            则从左到目前位置的leftMax肯定也是小于rightMax的
            如果上一轮移动的是right指针，则height[right-1,n-1]<=height[left]=leftMax,
            若height[left]=leftMax<=height[right],则leftMax肯定小于rightMax，且rightMax=height[max]
            */
            if (leftMax < rightMax) //最终两个指针将汇聚到最高的位置
            {
                ans += leftMax - height[left];
                ++left;
            }
            else // height
            {
                ans += rightMax - height[right];
                --right;
            }
        }
        return ans;
    }
};
/*动态规划
对下标i，下雨后水能到达的最大高度等于下标i两边的最大高度的最小值，
下标i处能接的雨水量等于下标i处的水能到达的最大高度减去height[i]
创建两个长度为n的数组leftMax和rightMax,leftMax[i]表示下标i及其左边的位置中，height的最大高度
rightMax[i]表示下标i及其右边的位置中，height的最大高度
*/
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int n = height.size();
        if (n == 0)
            return 0;
        vector<int> leftMax(n);
        leftMax[0] = height[0]; //注意动态规划给初值
        for (int i = 1; i < n; ++i)
        {
            leftMax[i] = max(leftMax[i - 1], height[i]);
        }
        vector<int> rightMax(n);
        rightMax[n - 1] = height[n - 1];
        for (int j = n - 2; j >= 0; --j) //当出现--时，不能使用size_t，这是无符号数，一直会大于0
        {
            rightMax[j] = max(rightMax[j + 1], height[j]);
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            // leftMax[i],rightMax[i]是不会出现小于height[i]的情况的，最多与height[i]相等
            ans += min(leftMax[i], rightMax[i]) - height[i];
        }
        return ans;
    }
};
/*单调栈,栈对处理反转，先减后增的情况等很有帮助，
当后面的柱子高度比前面的低时，是无法接住雨水的
当找到一根比前面高的柱子，就可以计算接到的雨水
对更低的柱子入栈，更低的柱子因为如果能找到高柱子，这里就能接到雨水，若以入栈把它保存起来*/
#include <stack>
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int ans = 0;
        stack<int> stk;
        int n=height.size();
        for (int i = 0; i < n; ++i)
        {
            //满足前高后低再高才能存水，所以栈从栈顶到栈底是递减的，
            //当遇到大于栈顶的元素时，意味着，可能有可以存水的空间
            while (!stk.empty()&&height[i]>height[stk.top()])
            {
                int top=stk.top();
                stk.pop();
                if(stk.empty())
                    break;
                int left=stk.top();//left指向的值肯定大于top指向的值
                int width=i-left-1;
                int h=min(height[left],height[i])-height[top];
                ans+=width*h;
            }
            stk.push(i);
        }
        return ans;
    }
};
