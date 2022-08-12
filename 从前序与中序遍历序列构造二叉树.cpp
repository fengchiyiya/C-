// 给定两个整数数组preorder和inorder，其中preorder是二叉树的先序遍历，
// inorder是同一棵树的中序遍历，请构造二叉树并返回其根节点。
#include <vector>
#include <unordered_map>
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
//先序遍历：先输出当前节点，再输出左子节点，再输出右子节点
//[ 根节点, [左子树的前序遍历结果], [右子树的前序遍历结果] ]
//中序遍历：先输出左子节点，再输出当前节点，再输出右子节点，
//[ [左子树的中序遍历结果], 根节点, [右子树的中序遍历结果] ]
/*递归根据前序遍历结果，递归构造节点，难点就是根据前序遍历的根节点在中序遍历中确定左子树和右子树的数量
只要我们在中序遍历中定位到根节点，那么我们就可以分别知道左子树和右子树中的节点数目*/
class Solution
{
public:
    unordered_map<int, int> map;
    TreeNode *myBuild(vector<int> &preorder, vector<int> &inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right)
    {
        if (preorder_left > preorder_right) //什么条件退出呢？
            return nullptr;
        //创建节点
        TreeNode *node = new TreeNode(preorder[preorder_left]);
        int inorder_root = map[preorder[preorder_left]]; //当前树的根节点的索引
        int size = inorder_root - inorder_left;          //左子树的长度（不包括根节点）
        //左子树再递归连接,preorder_left+1代表跳过根节点，结尾是preorder_left+size，长度为size
        node->left = myBuild(preorder, inorder, preorder_left + 1, preorder_left + size, inorder_left, inorder_root - 1);
        //右子树再递归连接
        node->right = myBuild(preorder, inorder, preorder_left + size + 1, preorder_right, inorder_root + 1, inorder_right);
        return node; //最后返回，返回最外层的值
    }
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        //构造哈希映射
        int n = preorder.size();
        for (size_t i = 0; i < n; i++)
        {
            map[inorder[i]] = i; // key=元素，键=索引
        }
        return myBuild(preorder, inorder, 0, n - 1, 0, n - 1);
    }
};
#include <stack>
/*迭代法
我们用一个栈和一个指针辅助进行二叉树的构造。初始时栈中存放了根节点（前序遍历的第一个节点），
指针指向中序遍历的第一个节点；我们依次枚举前序遍历中除了第一个节点以外的每个节点。
如果index恰好指向栈顶节点，那么我们不断地弹出栈顶节点并向右移动index，
并将当前节点作为最后一个弹出的节点的右儿子；如果index和栈顶节点不同，我们将当前节点作为栈顶节点的左儿子；
无论是哪一种情况，我们最后都将当前的节点入栈。
比较难想，需要利用反证法
前序遍历的结果按照顺序，从最上层依次往下按照先中再左再右的结果
中序遍历的结果按照顺序，从最底层依次往上按照先左后中在右的结果
知道这个，才比较好想这道题
*/
class Solution
{
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        int n = preorder.size();
        if (n == 0)
            return nullptr;
        TreeNode *root = new TreeNode(preorder[0]); //根节点
        stack<TreeNode *> stk;
        stk.push(root);
        int inorderIdx = 0;
        for (int i = 1; i < n; ++i) //注意从1开始因为，根节点提前添加了
        {
            auto node = stk.top();
            if (node->val != inorder[inorderIdx])//根据栈顶点判断
            {
                node->left = new TreeNode(preorder[i]);
                stk.push(node->left);
            }
            else
            {
                /*栈中的节点的顺序和它们在前序遍历中出现的顺序是一致的，
                而且每一个节点的右儿子都还没有被遍历过，
                那么这些节点的顺序和它们在中序遍历中出现的顺序一定是相反的。*/
                while (!stk.empty() && stk.top()->val == inorder[inorderIdx])
                {
                    node = stk.top();
                    stk.pop();
                    ++inorderIdx;
                }
                node->right = new TreeNode(preorder[i]);
                stk.push(node->right);
            }
        }
        return root;
    }
};