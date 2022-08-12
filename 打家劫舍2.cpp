// 小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 root 。
// 除了 root 之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，
// 聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果 两个直接相连的房子在同一天晚上被打劫 ，房屋将自动报警。
// 给定二叉树的 root 。返回在不触动警报的情况下 ，小偷能够盗取的最高金额 。
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
#include <unordered_map>
#include <algorithm>
using namespace std;
/*想到了动态规划，但是不知道动态规划如何与结合
二叉树不适合拿数组当缓存，使用哈希表存储结果
f(i)表示选择i节点的情况下，i节点的子树上被选择的节点的最大权值和；
g(i)表示不选择i节点的情况下，i节点的子树上被选择的节点的最大权值和。
当i被选中时，i的直接子树都不能被选中，i节点的最大权值和等于不选择左、右子树的最大权值和l和r,f(i)=g(l)+g(r)+val
当i不被选中时，i的左右孩子可以被选中，也可以不被选中。对于i的具体的孩子x，它对i的贡献是取两种情况的最大值。
g(i)=max{f(l),g(l)}+max{f(r),g(r)}
*/
/*本题关键的是：动态规划与二叉树结合时，存储缓存应该选用哈希表结构，而不是数组；
同时循环遍历应该改为深度优先搜索这种结构。*/
class Solution
{
public:
    // f存放选择当前节点所能获得的最大金钱；g代表不选择当前节点所能获得的最大金钱
    unordered_map<TreeNode *, int> f, g;

public:
    void dfs(TreeNode *node)
    {
        if (!node)
            return;
        dfs(node->left);
        dfs(node->right);
        f[node] = node->val + g[node->left] + g[node->right];
        g[node] = max(f[node->left], g[node->left]) + max(f[node->right], g[node->right]);
    }
    int rob(TreeNode *root)
    {
        dfs(root);
        return max(f[root], g[root]);
    }
};
