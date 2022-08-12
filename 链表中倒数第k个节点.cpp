//输入一个链表，输出该链表中倒数第k个节点。
//为了符合大多数人的习惯，本题从1开始计数，即链表的尾节点是倒数第1个节点。
#include<iostream>
#include<stack>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
/*借助栈的特性*/
//class Solution {
//public:
//	ListNode* getKthFromEnd(ListNode* head, int k) {
//		ListNode* pre=head;
//		stack<ListNode*> s;
//		while (pre)//节点存在
//		{
//			s.push(pre);
//			pre = pre->next;
//		}
//		while (k>0)
//		{
//			pre = s.top();
//			s.pop();
//			k--;
//		}
//		return pre;
//	}
//};
/*递归+回溯思想将链表反转
回溯是在递归函数的调用后进行的操作。*/
class Solution
{
public:
    /*
    删除倒数第n个结点
    递归+回溯
    */
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        if (!head->next) //如果只有一个结点,返回空指针
            return nullptr;
        ListNode *cur = new ListNode(0, head); //记录头结点的值
        reverseNode(cur, n);
        return cur->next;
    }
    /*回溯*/
    ListNode *reverseNode(ListNode *cur, int &n)
    {
        //记住一般是如果结点不存在，直接返回(不是子节点！！)
        if (!cur)
            return nullptr;
        else
        {
            ListNode *pre = reverseNode(cur->next, n);
            if (n == 0)
            {
                if (pre->next)
                    cur->next = pre->next;
                else
                    cur->next = nullptr;
                n--;
                return cur;
            }
            n--;
            return cur;
        }
    }
};
int main()
{
	ListNode a0(0), a1(1), a2(2);
	a0.next = &a1;
	a1.next = &a2;
	Solution plan;
	auto n = plan.inverse(&a0);
	cout << "val = " << n->val << endl;
	return 0;
}