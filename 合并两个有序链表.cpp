//将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
/*链表问题都可以考虑创建一个哑结点，防止头结点被删除找不到
本题虽然可以不用，但是需要额外判断取哪个为头结点*/
class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        if (!list1 && !list2)
            return nullptr;
        else if (!list1)
            return list2;
        else if (!list2)
            return list1;
        ListNode *head, *cur;
        //取小的头结点作为新链表的头结点
        if (list1->val <= list2->val)
        {
            head = list1;
            list1 = list1->next;
        }
        else
        {
            head = list2;
            list2 = list2->next;
        }
        cur = head;//记录头结点
        while (list1 && list2) //将公共部分先拼接
        {
            int left = list1->val;
            int right = list2->val;
            if (right <= left)
            {
                head->next = list2;
                head = head->next;
                list2 = list2->next;
            }
            else
            {
                head->next = list1;
                head = head->next;
                list1 = list1->next;
            }
        }
        if (list1)
            head->next = list1;
        else if (list2)
            head->next = list2;
        return cur;
    }
};