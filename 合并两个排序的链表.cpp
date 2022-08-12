#include<iostream>
using namespace std;
//输入两个递增排序的链表，合并这两个链表并使新链表中的节点仍然是递增排序的
//返回头节点
class ListNode
{
public:
	int val;
	ListNode* next;
	ListNode(int x) :val(x), next(nullptr) {}
};
/*迭代
引入伪头节点：由于初始状态合并链表中无节点，因此循环第一轮时无法将节点添加到合并链表中。*/
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* mixList = new ListNode(-1);//堆上新建一个表头
        ListNode* head=mixList;
        //要明确的修改指向，不然没有用
        //head->next=xxx这种有用
        //head=head->next;head=xxx这种没用
        while (l1&&l2)//两者都存在
        {
            if (l1->val < l2->val)
            {
                head->next=l1;
                l1 = l1->next;
            }
            else
            {
                head->next=l2;
                l2 = l2->next;
            }
            head = head->next;
        }
        //有一个为空了，剩下的直接继续添加
        head->next = l1 == nullptr ? l2 : l1;
        return mixList->next;
    }
};
/*递归：链表递归经常与回溯思想一起使用。
递归最重要的找到黑盒函数的作用*/
class Solution {
public:
    //mergeTwoLists函数:返回更小的节点
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        //递归先编写终止条件,其中一方为空，直接返回另一个节点
        if (l1 == nullptr)
            return l2;
        else if(l2==nullptr)
        {
            return l1;
        }
        if (l1->val < l2->val)
        {
            l1->next = mergeTwoLists(l1->next, l2);//递归，修改指向
            return l1;//回溯
        }
        else
        {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};