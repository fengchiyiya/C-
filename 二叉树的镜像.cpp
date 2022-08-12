#include<iostream>
/*请完成一个函数，输入一个二叉树，该函数输出它的镜像。
*/
class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};
class Solution {
public:
	TreeNode* mirrorTree(TreeNode* root) {//递推函数：当前节点交换左右子节点
		if (!root) //当前节点为空，返回空指针
			return nullptr;
		TreeNode* left = root->left;
		TreeNode* right = root->right;
		root->left = right;
		root->right = left;
		mirrorTree(left);
		mirrorTree(right);
		return root;
	}
};