//给你二叉树的根节点root，返回其节点值的层序遍历。（即逐层地，从左到右访问所有节点）。
#include <vector>
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
/*广度优先搜索 层序遍历*/
class Solution
{
public:
    void BFS(vector<vector<int>> &ans, TreeNode *root)
    {
        queue<TreeNode *> stk;
        stk.push(root);
        while (!stk.empty())
        {
            int size = stk.size();
            vector<int> v;
            for (size_t i = 0; i < size; i++)
            {
                auto x = stk.front();
                stk.pop();
                v.push_back(x->val);
                if (x->left)
                    stk.push(x->left);
                if (x->right)
                    stk.push(x->right);
            }
            ans.push_back(v);
        }
    }
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> ans;
        if(!root)
            return ans;
        BFS(ans, root);
        return ans;
    }
};