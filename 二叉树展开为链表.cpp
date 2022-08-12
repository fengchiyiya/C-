// 给你二叉树的根结点 root ，请你将它展开为一个单链表：
// 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，
//而左子指针始终为 null。 展开后的单链表应该与二叉树 先序遍历 顺序相同。
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
/*利用先序遍历，再根据前序遍历的结果依次连接
非递归的先序遍历，有两种方法，其中先遍历完左子树的是个双重循环*/
#include <stack>
#include <vector>
using namespace std;
class Solution
{
public:
    void flatten(TreeNode *root)
    {
        stack<TreeNode *> stk;
        vector<TreeNode *> v;
        TreeNode *node = root;
        // root指针作为条件时，if(root)，表明希望指针存在，反之希望不存在
        while (node || !stk.empty())
        {
            while (node)
            {
                stk.push(node);
                v.push_back(node);
                node = node->left;
            }
            node = stk.top();
            stk.pop();
            node = node->right;
        }
        int n = v.size();
        for (int i = 1; i < n; i++)
        {
            auto pre = v[i - 1];
            auto cur = v[i];
            pre->right = cur;
            pre->left = nullptr;
        }
    }
};
/*先序遍历使用非递归算法的另一种方法,*/
// class Solution
// {
// public:
//     vector<int> preorderTraversal(TreeNode *root)
//     {
//         vector<int> v;
//         stack<TreeNode *> stk;
//         if(root)
//             stk.push(root);
//         while (!stk.empty())
//         {
//             auto node=stk.top();
//             stk.pop();
//             v.push_back(node->val);
//             if(node->right)
//                 stk.push(node->right);
//             if(node->left)
//                 stk.push(node->left);
//         }
//         return v;
//     }
// };
/*在先序遍历的过程中，依次展开连接
一次循环的先序遍历，整体逻辑有点类似与层序遍历*/
class Solution
{
public:
    void flatten(TreeNode *root)
    {
        if (!root)
            return;
        stack<TreeNode *> stk;
        TreeNode *prev = nullptr;
        stk.push(root);
        while (!stk.empty())
        {
            auto node = stk.top();
            stk.pop();
            if (prev) //开始展开
            {
                prev->left = nullptr;
                prev->right = node;
            }
            //注意因为栈的特性，先插入右边的
            if (node->right)
                stk.push(node->right);
            if (node->left)
                stk.push(node->left);

            prev = node;
        }
    }
};
/*寻找前驱节点
前两种方法都借助的前序遍历，利用栈存储节点，
空间复杂度是O(1)的做法是寻找前驱节点.
解题的关键是：左子树的最下最右的节点，是右子树的父节点.
直接将当前节点的右子树，移接到左子树的最下最右的节点.*/
class Solution
{
public:
    void flatten(TreeNode *root)
    {
        TreeNode *cur = root;
        while (cur)
        {
            if (cur->left)
            {    
                auto next = cur->left; //记录原来的左节点
                auto prev = next;//prev记录此时左节点的值
                while (prev->right)    //寻找最下最右的节点
                {
                    prev = prev->right;
                }
                prev->right = cur->right;
                cur->left = nullptr;
                cur->right = next;
            }
            cur=cur->right;
        }
    }
};