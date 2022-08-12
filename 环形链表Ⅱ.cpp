// 给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
// 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
// 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
// 如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。
// 不需要修改链表
class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
/*哈希表*/
#include <unordered_map>
using namespace std;
class Solution
{
public:
    ListNode *detectCycle(ListNode *head)
    {
        unordered_map<ListNode *, int> node_map;
        int idx = 0;
        while (head)
        {
            if (!node_map.count(head)) //没有重复的，插入
            {
                node_map[head] = idx++;
                head = head->next;
            }
            else
                return head;
        }
        return nullptr;
    }
};
/*快慢指针，
慢指针跑一圈的话，快指针必然跑了两圈，两者必然在慢指针第一圈就相遇，但是题目还有一段直道
同时两者一定会相遇而不是经过，每次快指针比慢指针速度快1，两者距离每次都会减少1。
假设当慢指针入环时，快指针跑了b的距离，那么经过c步（快->慢），两者必然会在第一圈相遇
像环形链表1的快慢指针方法，无法确定入环点。
最近的数学思维很固化，感觉还是得动笔写一写
假设直道长度为a，慢指针在环内走了b长度与走了n圈的快指针相遇，环内剩余长度为c
慢：a+b，a+n(b+c)+b ：快
同时快=2慢，a+n(b+c)+b=2(a+b)
a=(n-1)b+nc;
当两者第一相遇时,n=1
a=c;即slow指针没走完的长度
*/
class Solution
{
public:
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *fast = head, *slow = head;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast)
            {
                ListNode *ptr = head;
                while (ptr != slow)
                {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
};