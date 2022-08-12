/*从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。注意不是前序遍历*/

#include <vector>
#include <iostream>
#include <queue>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
// class Solution {//这个实现的是前序遍历
// public:
//     vector<int> out;
//     //levelOrder就是存入当前节点的值,然后遍历左子树，再遍历右子树
//     vector<int> levelOrder(TreeNode* root) {//递归最重要的就是了解当前函数的作用
//         if (!root)//节点为空,直接返回
//         {
//             return vector<int>{};
//         }
//         out.push_back(root->val);
//         levelOrder(root->left);
//         levelOrder(root->right);
//         return out;
//     }
// };
/*广度优先算法BFS，广度优先算法通常利用队列的先入先出特性来实现*/
class Solution
{
public:
    vector<int> out;
    vector<int> levelOrder(TreeNode *root)
    {
        if (root == nullptr)
        {
            return vector<int>{}; //根节点为空，返回空列表
        }
        queue<TreeNode *> q;
        if (root)
            q.push(root);
        while (!q.empty())
        {
            int size = q.size();
            //层序遍历
            TreeNode *node;
            for (size_t i = 0; i < size; ++i) //这个size就决定是只循环当前层的节点，后续添加的不影响size
            {
                node = q.front();
                out.push_back(node->val); //
                q.pop();
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
        }
        return out;
    }
};
int main()
{
    TreeNode a(1), a1(2), a2(3), a3(4), a4(5);
    a.left = &a1;
    a.right = &a2;
    a1.left = &a3;
    a1.right = &a4;
    Solution plan;
    vector<int> out = plan.levelOrder(&a);
    for (size_t i = 0; i < out.size(); ++i)
    {
        cout << out[i] << " , ";
    }
    cout << endl;
    return 0;
}
