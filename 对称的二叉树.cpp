/*请实现一个函数，用来判断一棵二叉树是不是对称的。
如果一棵二叉树和它的镜像一样，那么它是对称的。*/
#include<iostream>
#include<queue>
using namespace std;
class TreeNode
{
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};
/*两个树互为镜像：1、两个树的根节点具有相同的值
2、每个树的右子树都与另一个树的左子树镜像对称
我们可以实现这样一个递归函数，通过「同步移动」两个指针的方法来遍历这棵树，
p 指针和 q 指针一开始都指向这棵树的根，随后 p 右移时，q 左移，p 左移时，q 右移。
每次检查当前p和q节点的值是否相等，如果相等再判断左右子树是否对称。
*/
class Solution {
public:
    bool check(TreeNode* p, TreeNode* q)
    {
        if (!p && !q)//p,q都为空
            return true;
        if (!p || !q)//p,q只有一个为空
            return false;
        return p->val == q->val && check(p->left, q->right) && check(p->right, q->left);
    }

    bool isSymmetric(TreeNode* root) {
        return check(root, root);//利用两个指针，这样不用深拷贝二叉树
    }
};
/*方法2：迭代。将递推方法改为迭代方法，引入队列是常用方法。
初始化时，将根节点入队两次，每次提取两个节点并比较它们的值，
然后将两个节点的左右子节点按相反的顺序插入队列。当队列为空，或者检测到树不对称时，该算法结束*/
class Solution {
public:
    bool isSymmetric(TreeNode* root)
    {
        return check(root, root);
    }
    bool check(TreeNode* u, TreeNode* v)
    {
        queue<TreeNode*> q;
        q.push(u);
        q.push(v);
        while (!q.empty())
        {
            u = q.front();
            q.pop();
            v = q.front();
            q.pop();
            if (!u && !v)//左、右都为空,代表到了叶子节点 直接continue 不插入节点，就会自动退出循环
                continue;
            if (!u || !v)//只有一个为空，另一个不空
                return false;
            if (u->val != v->val)
                return false;
            q.push(u->left);
            q.push(v->right);
            q.push(u->right);
            q.push(v->left);
        }
        return true;
    }
};