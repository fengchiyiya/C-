//给你一个二叉树的根节点root，检查它是否轴对称。
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
/*双指针递归
开始时都指向根节点，随后p右移，q左移；p左移，q右移
每次检查当前p和q结点的值是否相等，相等则继续向下判断*/
class Solution
{
public:
    bool check(TreeNode *left, TreeNode *right)
    {
        if (!left && !right)
        {
            return true;
        }
        else if (!left || !right)
            return false;
        return (left->val == right->val) && check(left->left, right->right) && check(left->right, right->left);
    }
    bool isSymmetric(TreeNode *root)
    {
        return check(root, root);
    }
};
/*使用栈迭代
将递归程序改写为迭代代码，经常使用栈容器*/
#include <stack>
using namespace std;
class Solution
{
public:
    bool isSymmetric(TreeNode *root)
    {
        stack<TreeNode *> stk;
        stk.push(root);
        stk.push(root);
        while (!stk.empty())
        {
            auto u=stk.top();stk.pop();
            auto v=stk.top();stk.pop();
            if(!u&&!v)//两个结点都不存在，继续
                continue;
            else if(!u||!v||(u->val!=v->val))//只有一个结点不存在，或者值不相等
                return false;
            stk.push(u->left);
            stk.push(v->right);
            stk.push(u->right);
            stk.push(v->left);
        }
        return true;
    }
};