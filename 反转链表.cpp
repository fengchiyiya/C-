#include <stack>
#include <vector>
#include <iostream>

using namespace std;
//定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。
class ListNode
{
public:
	int val;
	ListNode* next;
	ListNode(int x) :val(x), next(nullptr){}
};
/*
* 改变链表的指向就行，将next依次改为指向前一个节点
*/
//class Solution {
//public:
//    ListNode* reverseList(ListNode* head) {
//		ListNode* prev = nullptr;
//		ListNode* curr = head;
//		while (curr)
//		{
//			ListNode* next = curr->next;//注意这里的next的需要先缓存一下，后面next被改了
//			cout << "curr = "<<curr->val << endl;
//			curr->next = prev;//修改当前节点的指向
//			prev = curr;
//			curr = next;
//		}
//		return prev; 
//    }
//};
/*递归：递归最重要的是找通项，一般形式
* 下面体现的是一种递归+回溯的思想
* 
*/
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		// 回溯思想
		if (!head || !head->next) {//节点不存在
			return head;
		}
		// 这里head代表上一个节点，head->代表下一个节点，
		// newHead代表最后一个节点，并且每次返回时，值没变，所以一直都是最后一个节点
		ListNode* newHead = reverseList(head->next);
		head->next->next = head;
		head->next = nullptr;
		return newHead;
	}
};
int main()
{
	ListNode a1(1), a2(2), a3(3), a4(4), a5(5);
	a1.next = &a2;
	a2.next = &a3;
	a3.next = &a4;
	a4.next = &a5;
	Solution s;
	ListNode* L=s.reverseList(&a1);
	while (L)
	{
		cout << L->val << endl;
		L = L->next;
	}
	return 0;
}
/*
* 链表修改指向时，记得缓存之前的指向，不然你就找不到了！
*/