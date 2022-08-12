/*
* 输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)
* B是A的子结构， 即 A中有出现和B相同的结构和节点值。
*/
#include<vector>
#include<queue>
#include<iostream>
using namespace std;
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) :val(x), left(nullptr), right(nullptr) {}
};
/*1、先序遍历树A中的每个节点；
2、判断树A中以根节点的子树是否包含树B*/
class Solution {
public:
    vector<TreeNode*> first_node;
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (!A || !B) {
            return false;
        }
        //找到所有包含B的根节点的节点
        find_first_node(A, B);
        if (first_node.size() == 0) {
            return false;
        }
        bool ans = false;
        for (auto A : first_node) {
            ans |= is_sub(A, B);
        }
        return ans;
    }
    void find_first_node(TreeNode* A, TreeNode* B) {
        if (!A) {
            return;
        }
        if (A->val == B->val) {
            first_node.push_back(A);
        }
        find_first_node(A->left, B);
        find_first_node(A->right, B);
    }
    bool is_sub(TreeNode* A, TreeNode* B) {
        if (!A && B) {//A节点为空（null），B不为空，返回false；
            return false;
        }
        if ((!A && !B) || (A && !B)) {//A和B都为空，或者A不为空，B为空，返回true；
            return true;
        }
        if (A->val != B->val) {//A的val和B的val不相等，返回false；
            return false;
        }

        return is_sub(A->left, B->left) & is_sub(A->right, B->right);
    }
};
class Solution {
public:
    vector<TreeNode*> first_node;//匹配的根节点
    bool isSubStructure(TreeNode* A, TreeNode* B) {
        if (!A||!B)//B为空节点，直接返回false
            return false;
        findFristNode(A, B);//找匹配点
        bool flag;
        for (auto node:first_node)
        {
            flag=isSub(node, B);
        }
        return flag;
    }
    bool isSub(TreeNode* A, TreeNode* B)
    {   
        if (!A&&B)//A空，B不空 return false
            return false;
        if ((A && !B) || (!A && !B)) //A不空，B空或者A空，B空 return true
            return true;
        if (A->val != B->val)//值不相等
            return false;
        //if (A->val == B->val)//这个不能加，这个加了就提前退出，只判断退出条件
        //    return true;
        return isSub(A->left, B->left) & isSub(A->right, B->right);
    }
    void findFristNode(TreeNode* A, TreeNode* B)
    {
        if (!A)//A为空节点
            return;
        if (A->val == B->val)
            first_node.push_back(A);
        findFristNode(A->left,B);
        findFristNode(A->right,B);
    }
};
int main()
{
    TreeNode a(4), a1(2), a2(3), a3(4),a4(5),a5(6),a6(7),a7(8),a8(9);
    a.left = &a1;
    a.right = &a2;
    a1.left = &a3;
    a1.right = &a4;
    a2.left = &a5;
    a2.right = &a6;
    a3.left = &a7;
    a3.right = &a8;
    Solution plan;
    int res = plan.isSubStructure(&a, &a3);
    cout << "res = " << res << endl;
    return 0;
}