//给定一个二叉树的根节点root，返回它的中序遍历。

#include <vector>
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
//中序遍历就是先输出左结点的值，再输出本节点的值，最后输出右节点的值
class Solution
{
public:
    vector<int> v;
    void middle(TreeNode *root)
    {
        if (!root)
            return;
        middle(root->left);
        //只需要插入一次值，因为每个结点都会进入一次递归函数
        v.push_back(root->val); //递归函数后插入,这样会在递归函数返回最上层后，最上层先插入，最内层最后插入
        middle(root->right);
    }
    vector<int> inorderTraversal(TreeNode *root)
    {
        middle(root);
        return v;
    }
};
#include <stack>
/*迭代
方法一的递归函数我们也可以用迭代的方式实现，两种方式是等价的，
区别在于递归的时候隐式地维护了一个栈，而我们在迭代的时候需要显式地将这个栈模拟出来，
其他都相同，具体实现可以看下面的代码。*/
class Solution
{
public:
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> res;
        stack<TreeNode *> stk;
        while (root != nullptr || !stk.empty())
        {
            while (root != nullptr)
            {
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            res.push_back(root->val);
            root = root->right;
        }
        return res;
    }
};