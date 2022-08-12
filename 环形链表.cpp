// 给你一个链表的头节点 head ，判断链表中是否有环。
// 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
// 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
// 注意：pos 不作为参数进行传递 。仅仅是为了标识链表的实际情况。
// 如果链表中存在环 ，则返回 true 。 否则，返回 false 。
class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
#include <unordered_map>
using namespace std;
/*哈希表*/
class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        if (!head)
            return false;
        int pos = 0;
        unordered_map<ListNode *, int> map;
        while (head)
        {
            auto id = map.find(head);
            if (id != map.end()) //链表节点被记录过
            {
                pos = distance(id, map.find(head));
                return true;
            }
            else
            {
                map[head] = pos++;
                head = head->next;
            }
        }
        return false;
    }
};
/*快慢指针的双指针
快指针每次跑两步，慢指针每次跑一步，如果相遇了就代表了有环，
有点像操场跑步的感觉，只要一直跑，速度快的一定会追上速度慢的
慢指针操场跑一半，快指针，必然操场跑了一圈，慢指针跑了1圈，快指针必然跑了2圈，两者必然相遇*/
class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        ListNode *fast = head, *slow = head;
        //只要fast和fast->next存在即可，fast->next->next如果为nullptr，后面就会退出循环
        while (fast&&fast->next)
        {
            fast=fast->next->next;
            slow=slow->next;
            if(fast==slow)
                return true;
        }
        return false; 
    }
};