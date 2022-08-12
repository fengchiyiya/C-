// 给你一个二叉树的根节点root，判断其是否是一个有效的二叉搜索树
// 有效二叉搜索树定义如下：
// 节点的左子树只包含小于当前节点的数。
// 节点的右子树只包含大于当前节点的数。
// 所有左子树和右子树自身必须也是二叉搜索树。
#include <limits>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/*递归，可惜还差一点点，需要加个上下限帮助判断,以根节点的值作为分界值*/
class Solution
{
public:
    bool check(TreeNode *root, long long high, long long low)
    {
        if (!root) //默认返回true
            return true;
        if (root->val >= high || root->val <= low)
            return false;
        //这里一旦出现false不会被刷新掉，而是会一直保持，这种return A&B的形式，可以学习一下，简洁明了
        return check(root->left, root->val, low) && check(root->right, high, root->val);
    }
    bool isValidBST(TreeNode *root)
    {
        return check(root, LONG_MAX, LONG_MIN);
    }
};
/*中序遍历，想到了，但是还是理解不够深刻，改成了递归的形式但是还是可惜，差一点
二叉搜索树【中序遍历】得到的值一定是升序排列的*/
#include <stack>
class Solution {
public:
    bool isValidBST(TreeNode* root) 
    {
        stack<TreeNode*> stk;
        long long pre=LONG_MIN;
        while (root||!stk.empty())
        {
            while (root)
            {
                stk.push(root);
                root=root->left;
            }
            root=stk.top();
            stk.pop();
            // 如果中序遍历得到的节点的值小于等于前一个inorder，说明不是二叉搜索树
            if(root->val<=pre)
                return false;
            pre=root->val;
            root=root->right;
        }
        return true;
    }
};