// 路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。
// 同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
// 路径和是路径中各节点值的总和。
// 给你一个二叉树的根节点 root ，返回其最大路径和 。
class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/*广度优先搜索不行，因为题目要求从任意节点出发*/
#include <stack>
using namespace std;
// class Solution
// {
// public:
//     int maxPathSum(TreeNode *root)
//     {
//         int maxSum=INT_MIN;
//         stack<TreeNode*> stk;
//         stack<int> v;
//         v.push(root->val);
//         stk.push(root);
//         while (!stk.empty())
//         {
//             int size=stk.size();
//             for (int i = 0; i < size; i++)
//             {
//                 int curr=v.top();v.pop();
//                 auto node=stk.top();stk.pop();
//                 if(curr<0)
//                     curr=0;
//                 maxSum=max(maxSum,curr);
//                 if(node->left)
//                 {
//                     stk.push(node->left);
//                     v.push(curr+node->left->val);
//                 }
//                 if(node->right)
//                 {
//                     stk.push(node->right);
//                     v.push(curr+node->right->val);
//                 }
//             }
//         }
//         return maxSum;
//     }
// };
/*递归
考虑实现一个简化的函数maxGain(node),该函数计算二叉树的一个节点的最大贡献值，具体而言，就是在以
该节点为根节点的子树中寻找以该节点为起点的一条路径，使得该路径上的节点值之和最大。
感觉该思想有点类似分治的思想，将复杂的问题划分为小问题*/
class Solution
{
private:
    int maxSum = INT_MIN;

public:
    int maxGain(TreeNode *root)
    {
        if (!root)
            return 0;
        int maxLeft=max(maxGain(root->left),0);
        int maxRight=max(maxGain(root->right),0);//递归到叶子节点，然后开始回溯
        int price=root->val+maxLeft+maxRight;
        //maxSum和返回值的区别在哪？maxSum代表最大路径和，返回值仅代表到当前节点的贡献值
        //maxSum包含两个子节点的贡献加本身，返回值仅包含自身和最大的子节点
        maxSum=max(maxSum,price);//连续数字求最值,用{}
        //返回当前节点的贡献值
        return root->val+max(maxLeft,maxRight);
    }
    int maxPathSum(TreeNode *root)
    {
        maxGain(root);
        return maxSum;
    }
};