//给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。
//数组中的每个元素代表你在该位置可以跳跃的最大长度。
//判断你是否能够到达最后一个下标。
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
/*贪心，这里似乎不太好用递归，因为需要返回值，但是又不像链表那样，最后返回的根节点或者叶子节点
对于数组中任意一个位置y，我们如何判断它是否可以到达？根据目的描述，
只要存在一个位置x，它本身可以到达，并且它跳跃的最大长度为x+nums[x],这个值＞=y,那么y就是可以达到的*/
class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int n = nums.size(), rightMax = 0; //目前为止的最大长度
        for (int i = 0; i < n; ++i)
        {
            if (i <= rightMax)
            {
                rightMax = max(i + nums[i],rightMax);//目前为止的最大长度
                if (rightMax >= n - 1)
                    return true;
            }
        }
        return false;
    }
};