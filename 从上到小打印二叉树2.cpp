/*从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。*/
#include<vector>
#include<iostream>
#include<queue>
using namespace std;
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) :val(x), left(nullptr), right(nullptr){}
};
/*BFS*/
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>out;
        queue<TreeNode*>q;
        if (root == nullptr)//当前节点为空，返回空容器
            return vector<vector<int>>{};
        if (root)//节点不为空
        {
            vector<int> temp;
            q.push(root);
        }
        while (!q.empty())
        {
            int size = q.size();
            vector<int> tmp;
            for (size_t i = 0; i < size; i++)//巧妙利用了size,这样子就是只循环本层的节点
            {
                TreeNode* node = q.front();
                q.pop();
                tmp.push_back(node->val);
                if (node->left)
                {
                    q.push(node->left);                   
                }
                if (node->right)
                {
                    q.push(node->right);
                }
            }
            out.push_back(tmp);
        }
        return out;
    }
};