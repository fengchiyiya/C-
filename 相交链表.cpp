// 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。
// 如果两个链表不存在相交节点，返回 null 。
class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
/*利用哈希表
链表的相交意味着，链表的地址和值是完全相同的，两个链表的相交部分用的同一块内存*/
#include <unordered_set>
using namespace std;
class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        unordered_set<ListNode*> set;
        while (headA)
        {
            set.insert(headA);
            headA=headA->next;
        }
        while (headB)
        {
            if(set.count(headB))
                return headB;
            headB=headB->next;
        }
        return nullptr;
    }
};