// 给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。
// 路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *_left, TreeNode *_right) : val(x), left(_left), right(_right) {}
};
/*最先想到的是深度优先搜索,但是没有想出来，本来想在dfs里面选择是否对target进行减去当前节点的值，
但是这样会误判，左右节点都会判断一次上个节点的结果值。应该采用和题解一样的判断，是判断当前节点值=target.
我是想一次进入dfs函数求出所有结果，通过不选择当前节点值想走入下一个节点，但是写的不对！不能这么做，逻辑有错误。
题解是：判断从每个节点出来满足路径总和为target的数目。即每个节点都进入一个dfs函数
他不会出现误判是对当前节点值进行判断，判断当前节点是否是target
*/
#include <iostream>
using namespace std;
/*分节点递归,最后把每个节点可能的情况加起来,但是会int会溢出，需要使用long long*/
class Solution
{
public:
    int dfs(TreeNode *node, int target)
    {
        if (!node)
            return 0;
        int ret = 0;
        if (node->val == target)
            ret++;
        ret += dfs(node->left, target - node->val);
        ret += dfs(node->right, target - node->val);
        return ret;
    }
    int pathSum(TreeNode *root, int targetSum)
    {
        if (!root)
            return 0;
        int ret = dfs(root, targetSum);
        ret += pathSum(root->left, targetSum);
        ret += pathSum(root->right, targetSum);
        return ret;
    }
};
#include <unordered_map>
/*前缀和
定义节点的前缀和为：从根节点到当前节点的路径上所有节点的和。
利用先序遍历二叉树，记录下根节点root到当前节点p的路径上除当前节点以外的所有节点的前缀和，
在保存的路径前缀和中查找是否存在前缀和等于当前节点到根节点的前缀和curr-targetSum
这个是深度优先，但不是回溯
递归之前的操作*/
class Solution
{
public:
    unordered_map<long long, int> prefix; // val,cnt

public:
    int dfs(TreeNode *root, long long curr, int targetSum)
    {
        if (!root)
        {
            return 0;
        }
        curr += root->val;
        int ret = 0;
        if (prefix.count(curr - targetSum))
        {
            ret = prefix[curr - targetSum];
        }
        prefix[curr]++; // cnt=1
        ret += dfs(root->left, curr, targetSum);
        ret += dfs(root->right, curr, targetSum);
        prefix[curr]--; // 这步恢复状态，是个好习惯,不然会一直增加
        return ret;
    }
    int pathSum(TreeNode *root, int targetSum)
    {
        prefix[0] = 1; // 这个是必须的，保证了从根节点出发，前缀和刚好为targetSum的值时也被记录到。
        return dfs(root, 0, targetSum);
    }
};