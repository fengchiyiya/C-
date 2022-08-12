// 给你两棵二叉树： root1 和 root2 。
// 想象一下，当你将其中一棵覆盖到另一棵之上时，两棵树上的一些节点将会重叠（而另一些不会）。
// 你需要将这两棵树合并成一棵新二叉树。合并的规则是：如果两个节点重叠，那么将这两个节点的值相加作为合并后节点的新值；
// 否则，不为 null 的节点将直接作为新二叉树的节点。返回合并后的二叉树。
// 注意: 合并过程必须从两个树的根节点开始。
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
/*深度优先搜索融合。在左树上融合，还是新建一个二叉树？
如果一个二叉树节点不存在，一个二叉树节点存在，则直接指向那个节点*/
class Solution
{
public:
    void dfsMerge(TreeNode *root1, TreeNode *root2)
    {
        if (!root1 && !root2)
            return;
        //双节点都存在
        int val = root1->val + root2->val;
        root1->val = val;
        if (root1->left && root2->left)
            dfsMerge(root1->left, root2->left);
        else if (root1->left || root2->left) //只存在一个节点
        {
            // root1->left存在，不动
            // root2->left存在，则需要将root1指向它
            if (root2->left)
                root1->left = root2->left;
        }
        if (root1->right && root2->right)
            dfsMerge(root1->right, root2->right);
        else if (root1->right || root2->right) //只存在一个节点
        {
            // root1->right存在，不动
            // root2->right存在，则需要将root1指向它
            if (root2->right)
                root1->right = root2->right;
        }
    }
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2)
    {
        //双根节点存在才进入融合
        if (root1 && root2)
            dfsMerge(root1, root2);
        else if (root1 || root2) //只存在单节点
            return root1 ? root1 : root2;
        return root1;
    }
};