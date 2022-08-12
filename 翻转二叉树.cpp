// 给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。
class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *_left, TreeNode *_right) : val(x), left(_left), right(_right) {}
};
/*递归
翻转二叉树：以前没发现子树的节点依旧是子树的节点，只是位置换了，知道这点就好写了*/
class Solution
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        if (!root) // root为空指针
            return root;
        TreeNode *node = root->left;
        root->left = root->right;
        root->right = node;
        root->left = invertTree(root->left); // 将左右节点传进去继续翻转
        root->right = invertTree(root->right);
        return root; //返回递归传进去的节点
    }
};