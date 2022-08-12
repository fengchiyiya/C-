// 给定一个二叉树，找出其最大深度。
// 二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
// 说明: 叶子节点是指没有子节点的节点。
#include <queue>
using namespace std;
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
/*广度优先搜索*/
class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        queue<TreeNode *> q;
        q.push(root);
        if (!root)
            return 0;
        int ans = 0;
        while (!q.empty())
        {
            int size = q.size();
            for (size_t i = 0; i < size; i++)
            {
                auto n = q.front();
                q.pop();
                if (n->left)
                    q.push(n->left);
                if (n->right)
                    q.push(n->right);
            }
            ans++;
        }
        return ans;
    }
};
/*深度优先搜索，递归*/
class Solution
{
public:
    int maxDepth(TreeNode *root)//递归+回溯
    {
        if (!root)
            return 0;
        return max(maxDepth(root->left),maxDepth(root->right))+1;
    }
};
class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};