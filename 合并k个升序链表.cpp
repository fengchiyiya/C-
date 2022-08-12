//给你一个链表数组，每个链表都已经按升序排列
//请你将所有的链表合并到一个升序链表中，返回合并后的链表
#include <vector>
#include <queue>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
/*两个链表循环融合:利用两个链表融合的知识*/
class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        int n = lists.size();
        if (lists.empty())
            return nullptr;
        else if (lists.size() == 1)
            return lists[0];
        ListNode *L;
        for (size_t i = 1; i < n; ++i)
        {
            if (i == 1)
            {
                ListNode *left = lists[i - 1];
                ListNode *right = lists[i];
                L = merge2Lists(left, right);
            }
            else
            {
                ListNode *right = lists[i];
                L = merge2Lists(L, right);
            }
        }
        return L;
    }
    ListNode *merge2Lists(ListNode *left, ListNode *right)
    {
        ListNode *head, *cur;
        if (!left || !right)
            return left ? left : right;
        int v1 = left->val;
        int v2 = right->val;
        if (v1 <= v2)
        {
            head = left;
            left = left->next;
        }
        else
        {
            head = right;
            right = right->next;
        }
        cur = head;
        while (left && right)
        {
            if (left->val <= right->val)
            {
                head->next = left;
                left = left->next;
                head = head->next;
            }
            else
            {
                head->next = right;
                right = right->next;
                head = head->next;
            }
        }
        head->next = (left ? left : right);
        return cur;
    }
};
/*分治合并！多个操作目标时，需要想到分治操作,分治思想有时候和二分法差不多
将k个链表配对并将同一对中的链表合并
第一轮合并以后，k个链表被合并成了k/2个链表
重复这一过程，直到得到了最终链表
*/
class Solution
{
public:
    ListNode *merge(vector<ListNode *> &lists, int begin, int end)
    {
        if (begin == end)
            return lists[begin];
        if (begin > end) // mid+1可能会超过end，直接返回nullptr，此时begin==mid==end,只有一个元素
            return nullptr;
        int mid = (begin + end) >> 1; //类似二分法的边界 [begin,mid],[mid+1,end]
        return mergeTwoLists(merge(lists, begin, mid), merge(lists, mid + 1, end));
    }
    ListNode *mergeTwoLists(ListNode *left, ListNode *right)
    {
        if (!left || !right)
            return left ? left : right;
        ListNode head, *tail = &head; //不使用new创建链表结点，这样可以自动释放
        while (left && right)
        {
            int v1 = left->val;
            int v2 = right->val;
            if (v1 <= v2)
            {
                tail->next = left;
                left = left->next;
            }
            else
            {
                tail->next = right;
                right = right->next;
            }
            tail = tail->next;
        }
        tail->next = (left ? left : right);
        return head.next; //返回后面的结点，这样开头的哑结点就会被自动删除
    }
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        int size = lists.size() - 1; //代表索引值，需要-1
        return merge(lists, 0, size);
    }
};
/*使用优先队列合并
优先队列具有队列的所有特性，包括队列的基本操作，并在此基础上添加了一个内部的一个排序*/
class Solution
{
public:
    struct Status
    {
        int val;
        ListNode *ptr;
        //形参必须是const成员
        bool operator<(const Status &rhs) const 
        {
            return val>rhs.val;//这里是为了配合优先级队列，先找到最大的，放进去
        }
    };
    //优先级队列可以理解为栈，大的先进，但是后出。最后的结果类似从小到大排序的栈，栈顶是最小值
    priority_queue<Status> q;
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        for (auto x : lists)
        {
            if (x)
                q.push({x->val, x});//struct结构体依次赋值，如果是class类，需要构造函数
        }
        ListNode head,*tail=&head;
        while (!q.empty())
        {
            Status n=q.top();
            q.pop();
            tail->next=n.ptr;
            tail=tail->next;
            if(n.ptr->next)
                q.push({n.ptr->next->val,n.ptr->next});
        }
        return head.next;
    }
};
