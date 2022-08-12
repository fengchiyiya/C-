// 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，
// 满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
// 没有思路，但是哈希表应该能想到的
/*递归，深度优先搜索*/
class Solution
{
public:
    TreeNode *ans = nullptr;
    bool dfs(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (!root)
            return false;
        bool lson = dfs(root->left, p, q);
        bool rson = dfs(root->right, p, q);
        // lson、rson代表左右子树是否包含p和q;或者当前节点是p,q中的一个，另一个在当前节点的子树中
        if ((lson && rson) || ((root->val == p->val) || (root->val == q->val) && (lson || rson)))
        {
            ans = root;
        }
        // 这个return 好巧妙，代表着一旦为true，将一直为true
        return lson || rson || root->val == p->val || root->val == q->val;
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        dfs(root, p, q);
        return ans;
    }
};

/*哈希表存储父节点，这种找明显对应关系的题，应该第一时间想到哈希表的
递归法很多时候，看起来很秀，但是时间和空间复杂度很高的，因为要一直入栈出栈*/
#include <unordered_map>
using namespace std;
class Solution
{
private:
    // 题目保证了节点值互不相同
    unordered_map<int, TreeNode *> fa; //存放当前节点的父节点
    unordered_map<int, bool> vis;      // 存放节点是否被访问过

public:
    void dfs(TreeNode *root)
    {
        if (!root)
            return;
        if (root->left)
        {
            fa[root->left->val] = root;
            dfs(root->left);
        }
        if (root->right)
        {
            fa[root->right->val] = root;
            dfs(root->right);
        }
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        dfs(root);
        fa[root->val] = nullptr; // 根节点的情况也要考虑
        while (p)
        {
            vis[p->val] = true; // 因为节点值不相同，所以这里将初始节点赋值为true，不影响结果
            p = fa[p->val];     // p=父节点
        }
        while (q)
        {
            if (vis[q->val])
                return q;
            q = fa[q->val];
        }
        return nullptr;
    }
};