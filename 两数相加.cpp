//给你两个非空的链表，表示两个非负的整数。它们的每位数字都是按照逆序的方式存储的，并且每个节点只能存储一位数字。
//请你将两个数相加，并以相同形式返回一个表示和的链表
//你可以假设除了数字0之外，这两个树都不会以0开头。
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};
/*模拟:逆序存储的，根节点是最小的数字*/
#include <vector>
#include <queue>
using namespace std;
/*逆序存储，根节点就是最小值，从根节点开始依次相加，并且每个节点只能存储一位数字，所以进位也需要分开存储*/
//对于链表问题，返回结果为头结点时，通常需要先初始化一个预先指针 pre，该指针的下一个节点指向真正的头结点head。
//使用预先指针的目的在于链表初始化时无可用节点值，而且链表构造过程需要指针移动，进而会导致头指针丢失，无法返回结果。
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* head = nullptr, * tail = nullptr;
		int carry = 0;
		while (l1||l2)
		{
			int n1 = l1 ? l1->val : 0;//l1存在，赋值l1节点的值，否则填0
			int n2 = l2 ? l2->val : 0;
			int sum = n1 + n2+carry;
			carry = sum / 10;
			if (!head)//
			{
				//记录头节点，避免头节点丢失
				head = tail = new ListNode{ sum % 10 };//head,tail都是指向同一个节点，如果head->next=tail就是圆形了，所以是错的
			}
			else
			{
				tail->next = new ListNode{ sum % 10 };//存余数，进位等到下一次循环，作为求和的一部分
				tail = tail->next;
			}
			if (l1)
				l1 = l1->next;
			if (l2)
				l2 = l2->next;
		}
		if (carry > 0)//最后由进位
			tail->next = new ListNode{ carry };
		return head;
    }
};