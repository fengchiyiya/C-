// 给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。
// 这条路径可能穿过也可能不穿过根结点。
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *_left, TreeNode *_right) : val(x), left(_left), right(_right) {}
};
/*深度优先搜索
需要理解路径的概念，直径是最大路径，路径是节点数-1
回溯时，求左右子树的最大路径*/
#include <iostream>
#include <algorithm>
class Solution
{
public:
    int ans = 0;
    int dfs(TreeNode *root)
    {
        if (!root)
            return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);
        ans = max(ans, l + r); //求最大路径，节点的边数
        return max(l, r) + 1;  //返回该节点的深度(高度)
    }
    int diameterOfBinaryTree(TreeNode *root)
    {
        dfs(root);
        return ans;
    }
};
