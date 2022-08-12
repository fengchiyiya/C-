// 给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），
// 使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。
// 提醒一下，二叉搜索树满足下列约束条件：
// 节点的左子树仅包含键 小于 节点键的节点。
// 节点的右子树仅包含键 大于 节点键的节点。
// 左右子树也必须是二叉搜索树。
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *_left, TreeNode *_right) : val(x), left(_left), right(_right) {}
};
/*回溯没搞定，因为需要算父节点的值，所以应该先算右节点的值
根节点的右侧值
右侧右节点      =节点的当前值+右子树的和
右侧左节点      =节点的父节点的和
根节点的左侧的值
左侧右节点=节点的父节点的和-父节点的值+根节点的右子树的和=节点当前值+根节点的右子树的和+当前节点的右子树的和
左侧左节点=父节点的和+当前节点的值+当前节点的右子树的和
*/

/*反序中序遍历
我看到题目给的先序遍历结果，第一时间以为遍历搞不定！失策了，同时也是自己忘了中序遍历
中序遍历的迭代写法：利用栈先将左节点入栈，到底后再出栈压入右节点
        递归写法：先递归左节点，插入当前节点值，再插入右节点值
二叉搜索树的中序遍历是一个单调递增的有序序列。
*/
class Solution
{
public:
    int sum = 0; //记录比当前节点大的值
    TreeNode *convertBST(TreeNode *root)
    {
        if (root)
        {
            // 反序中序 先遍历右节点  这样得到的是递减的序列
            convertBST(root->right);
            sum += root->val;
            root->val = sum;
            convertBST(root->left);
        }
        return root;
    }
};
