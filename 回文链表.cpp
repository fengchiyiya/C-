// 给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *_next) : val(x), next(_next) {}
};

//回文链表指的是去掉头尾链表依旧是回文链表
// 使用数组接收一下？这个方法应该可行，但是应该是最差的
/*最好的办法快慢指针 时间复杂度O(n),空间复杂度O(1)
注意翻转的起点是慢指针的下一个节点，
因为如果总数为奇数，则slow的节点正好为中点，无序比较；
如果总数为偶数，则slow的节点为偏小的中间数，比如8，中间数为4或5，slow为4，后半部分也是从slow的下一个节点开始的
翻转链表时，需要注意，返回的应该是prev节点，因为最后的当前节点一般为空节点
*/
class Solution
{
public:
    bool isPalindrome(ListNode *head)
    {
        if (!head)
            return false;
        ListNode *half = findSecond(head);
        ListNode *secondHead = reverseList(half->next);
        ListNode *p1 = head, *p2 = secondHead;
        while (p2)
        {
            if (p1->val != p2->val)
                return false;
            p1 = p1->next;
            p2 = p2->next;
        }
        reverseList(secondHead);
        return true;
    }
    // 快慢指针找中点
    ListNode *findSecond(ListNode *head)
    {
        ListNode *fast = head, *slow = head;
        while (fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    // 翻转链表 注意返回的是前一个节点，因为最后一个一般是空节点，
    ListNode *reverseList(ListNode *node)
    {
        ListNode *prev = nullptr;
        ListNode *temp = node;
        while (node)
        {
            temp = node->next;
            node->next = prev;
            prev = node;
            node = temp;
        }
        return prev;
    }
};