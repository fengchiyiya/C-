//给你二叉树的根节点 root 和一个整数目标和 targetSum ，
//找出所有从根节点到叶子节点 路径总和等于给定目标和的路径。叶子节点是指没有子节点的节点。
#include<vector>

using namespace std;
class TreeNode
{
public:
	TreeNode* left, * right;
	int val;
	TreeNode() :val(0), left(nullptr), right(nullptr){}
	TreeNode(int x) :val(x), left(nullptr), right(nullptr){}
	TreeNode(int x,TreeNode* _left,TreeNode* _right) :val(x), left(_left), right(_right){}
};

/*广度优先算法*/
//本题，先找到路径，再反向迭代求出父节点，利用哈希表存储父节点关系
//#include<queue>
//#include<unordered_map>
//class Solution {
//public:
//    vector<vector<int>> ret;
//    unordered_map<TreeNode*, TreeNode*> parent;//记录节点的父节点
//
//    void getPath(TreeNode* node) {
//        vector<int> tmp;
//        while (node != nullptr) {
//            tmp.emplace_back(node->val);
//            node = parent[node];
//        }
//        reverse(tmp.begin(), tmp.end());
//        ret.emplace_back(tmp);
//    }
//
//    vector<vector<int>> pathSum(TreeNode* root, int target) {
//        if (root == nullptr) {
//            return ret;
//        }
//
//        queue<TreeNode*> que_node;
//        queue<int> que_sum;
//        que_node.emplace(root);
//        que_sum.emplace(0);
//
//        while (!que_node.empty()) {
//            TreeNode* node = que_node.front();
//            que_node.pop();
//            int rec = que_sum.front() + node->val;
//            que_sum.pop();//弹出旧的求和记录
//            if (node->left == nullptr && node->right == nullptr) {
//                if (rec == target) {
//                    getPath(node);
//                }
//            }
//            else {
//                if (node->left != nullptr) {
//                    parent[node->left] = node;
//                    que_node.emplace(node->left);
//                    que_sum.emplace(rec);
//                }
//                if (node->right != nullptr) {
//                    parent[node->right] = node;
//                    que_node.emplace(node->right);
//                    que_sum.emplace(rec);
//                }
//            }
//        }
//        return ret;
//    }
//};
/*深度优先算法：就是递归和回溯
注意1如果要在递归中改变参数，需要将该参数作为形参或者返回值。
2该问题需要注意回溯时需要恢复到上一层路径。
3.使用emplace_back代替push_back。
*/
class Solution {
public:
    vector<int> temp;
    vector<vector<int>> path;
    void DFS(TreeNode* root, int target)
    {
        if (!root)
            return;
        target -= root->val;
        temp.emplace_back(root->val);
        if (!root->left && !root->right && target == 0)
            path.emplace_back(temp);
        DFS(root->left, target);
        DFS(root->right, target);
        temp.pop_back();
    }
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        DFS(root, target);
        return path;
    }
};
#include<queue>
#include<unordered_map>
/*广度优先算法：配合队列使用，一个while循环，一个for循环*/
class Solution {
public:
    vector<vector<int>> path;
    unordered_map<TreeNode*, TreeNode*>pathRealtion;
    void getPath(TreeNode* node)
    {
        vector<int> temp;
        temp.push_back(node->val);
        while(pathRealtion.count(node))//根节点没有作为键值，会退出循环
        {
            node=pathRealtion[node];
            temp.push_back(node->val);
        }
        reverse(temp.begin(), temp.end());
        path.emplace_back(temp);
    }
    vector<vector<int>> pathSum(TreeNode* root, int target)
    {
        if(!root)//空节点直接返回
            return path;
        queue<int> sum;//记录到每一层节点的路径和
        queue<TreeNode*> ret;
        ret.push(root);
        sum.push(root->val);
        while (!ret.empty())
        {
            int size = sum.size();
            for (size_t i = 0; i < size; ++i)
            {
                TreeNode* temp = ret.front();
                ret.pop();
                int s = sum.front();
                sum.pop();
                if (!temp->left && !temp->right && s == target)//是叶子节点，并满足条件
                {
                    getPath(temp);
                }
                if (temp->left)
                {
                    pathRealtion[temp->left] = temp;
                    ret.push(temp->left);
                    //注意不能直接改变s，右节点也需要用到父节点的和
                    sum.push(s+ temp->left->val);
                }
                if (temp->right)
                {
                    pathRealtion[temp->right] = temp;
                    ret.push(temp->right);
                    sum.push(s +temp->right->val);
                }
            }
        }
        return path;
    }
};