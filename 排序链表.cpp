// 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。
class ListNode
{
public:
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *_next) : val(x), next(_next) {}
};
/*最简单的方法就是利用map将节点值存下来，并排序，然后依次连接。
 */
/*最适合链表的排序算法是归并排序
自顶向下归并排序。
1.找到链表的中点，以中点为分界，将链表拆分成两个子链表。寻找链表的中点可以使用快慢指针的做法，快指针每次移动两步，
慢指针每次移动一步，当快指针到达链表末端时，慢指针指向的链表节点即为链表的中点。一直拆到只有一个结点。这样等于把所有节点打散，重组
2.对两个子链表分别排序。
3.将两个排序后的子链表合并，得到完整的排序后的链表。可以使用合并两个有序链表的做法，将两个有序的子链表进行合并。
*/
class Solution
{
public:
    ListNode *sortList(ListNode *head)
    {
        return sortList(head, nullptr);
    }
    ListNode *sortList(ListNode *head, ListNode *tail)
    {
        if (!head) //链表的节点为空
            return head;
        else if (head->next == tail) //保证链表的节点个数等于1，将链表从tail处断开
        {
            head->next = nullptr;
            return head;
        }
        ListNode *fast = head, *slow = head;
        while (fast != tail) // fast！=tail才能作为判断条件，因为分割后fast->next可能不为空
        {
            slow = slow->next;
            fast = fast->next;
            if (fast != tail) //这里的判断条件也是一样的
                fast = fast->next;
        }

        return merge(sortList(head, slow), sortList(slow, tail));
    }
    ListNode *merge(ListNode *head1, ListNode *head2)
    {
        ListNode dummy = ListNode(0);
        //这里不拷贝指针也可以，函数调用传进去的指针为拷贝后的指针，在函数内指针本身的改变，不影响外部指针的值？
        ListNode *temp = &dummy, *L = head1, *R = head2;
        while (L && R)
        {
            if (L->val <= R->val)
            {
                temp->next = L;
                L = L->next;
            }
            else
            {
                temp->next = R;
                R = R->next;
            }
            temp = temp->next;
        }
        if (!L)
            temp->next = R;
        else
            temp->next = L;
        return dummy.next;
    }
};
/*自底向下归并排序 O(1)的空间复杂度
1.用subLength表示每次需要排序的子链表的长度，初始时subLength=1
2.每次将链表拆分成若干个长度为subLength的子链表（最后一个子链表的长度可以小于subLength)，两两进行合并
3.将subLength的值加倍，重复第二步，直到有序子链表的长度大于或等于length，整个链表排序完成。
*/
class Solution
{
public:
    ListNode *merge(ListNode *head1, ListNode *head2)
    {
        ListNode dummy{0};
        ListNode *temp = &dummy;
        while (head1 && head2)
        {
            if (head1->val <= head2->val)
            {
                temp->next = head1;
                head1 = head1->next;
            }
            else
            {
                temp->next = head2;
                head2 = head2->next;
            }
            temp = temp->next;
        }
        if (!head1)
            temp->next = head2;
        else
            temp->next = head1;
        return dummy.next;
    }
    ListNode *sortList(ListNode *head)
    {
        int n = 0;
        ListNode *node = head;
        while (node)
        {
            ++n;
            node = node->next;
        }
        ListNode dummy{0, head};
        //注意位操作时 <<=和>>=后面的=不能忘
        for (int len = 1; len < n; len <<= 1)
        {
            ListNode *prev = &dummy, *curr = dummy.next;
            while (curr)
            {
                //子链表两两合并。
                ListNode *head1 = curr; //第一段子链表的起点
                for (int i = 1; i < len && curr->next; i++)
                {
                    curr = curr->next;
                }
                ListNode *head2 = curr->next; //第二段子链表的起点
                curr->next = nullptr;         //第一段与第二段子链表断开
                curr = head2;//从第二段开始继续寻找尾结点，需要保证第二段的开头不是空结点
                for (int i = 1; i < len && curr&&curr->next; i++)
                {
                    curr = curr->next;
                }
                ListNode *next; //记录下一段的开头
                if (curr)       //如果第二段链表的结尾不为空
                {
                    next = curr->next;
                    curr->next = nullptr; //第二段与剩余链表断开，
                    curr = next;
                }
                prev->next = merge(head1, head2);
                while (prev->next) //将prev移动到结尾! 不是空结点
                {
                    prev = prev->next;
                }
            }
        }
        return dummy.next;
    }
};
/*
注意点1： prev指向哑结点，在循环中，每次指向尾节点，不是空结点。
2：第二段的开头需要判断开头是否为空指针；指针的迭代需要判断下一个指针结点是否为空时必须的。
3：位操作的=号不能忘，<<=,>>=。
*/