//给你一个链表，删除链表的倒数第n个结点，并且返回链表的头结点
#include <iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
/*链表的递归加回溯：
通常可以使用哑结点，这样可以避免头结点被删除，找不到头结点的情况*/
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
/*反转问题，一般可以借助栈空间，利用栈先入后出的特性
 */

/*双指针：快指针先移动n个结点，然后快慢指针同时移动，注意是同时，当快指针指向尾结点时停止
判断指针存在，直接if(left),不存在直接if(!left),不要搞错
 */
class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *cur = new ListNode(0, head);
        ListNode *left = cur, *right = cur;
        //虽然增加了一个快慢指针，但是不影响快慢指针的相对位置，不需要+1
        while (right) //右结点存在
        {
            if (right->next) //子结点存在
                right = right->next;
            n--;
            if (n == 0)
                break;
        } 
        // right直接遍历到结尾
        while (right)
        {

            if (right->next)
            {
                left = left->next;
                right = right->next;
            }
            else
                break;
        } //退出循环时，right指向根节点，删除的结点位在left下一个的下一个
        //left=left->next;
        left->next = left->next->next;
        return cur->next;
    }
};
