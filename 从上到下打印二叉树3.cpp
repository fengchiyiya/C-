/*请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，
第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。*/
#include<vector>
#include<deque>
#include<iostream>
using namespace std;
class TreeNode {
public:
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) :val(x), left(nullptr), right(nullptr){}
};
/*奇数层，添加到双端队列的尾部
偶数层，添加到双端队列的头部*/
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		if (root == nullptr)
			return vector<vector<int>>{};
		deque<TreeNode*> d;
		vector<vector<int>> out;
		if (root)
			d.push_front(root);
		int count = 1;//层数(还可以用out的尺寸来判断层数是奇偶)
		//层序遍历
		while (!d.empty())
		{
			int size = d.size();
			vector<int> tmp;	
			//奇数层，从左往右打印，偶数层从右到左打印
			//奇数层存储节点时,先左节点，后右节点，采用尾插的方法存储
			//奇数层读取时，从头读（不能尾读，不然读入会读到刚插入的，读入和插入得相反）
			if (count % 2 == 1)
			{
				for (size_t i = 0; i < size; ++i)
				{
					TreeNode* node = d.front();
					d.pop_front();
					tmp.push_back(node->val);
					if (node->left)
						d.push_back(node->left);
					if (node->right)
						d.push_back(node->right);
				}
			}
			//偶数层存储节点时，先右节点，后左节点，采用头插的方式存储
			//偶数层读取时，从尾读（读入和插入顺序得相反，并且注意头插时，需要先右节点）
			else
			{
				for (size_t i = 0; i < size; ++i)
				{
					TreeNode* node = d.back();
					d.pop_back();
					tmp.push_back(node->val);
					if (node->right)
						d.push_front(node->right);
					if (node->left)
						d.push_front(node->left);
				}
			}
			count++;
			out.push_back(tmp);
		}
		return out;
	}
};