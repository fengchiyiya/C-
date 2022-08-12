#include<vector>
#include<stack>
using namespace std;
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
    int val;//当前节点的值
    ListNode* next;//下一个节点
    ListNode(int x) : val(x), next(NULL) {}//构造函数    
};
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {

        while (head)//当前节点不为null
        {
            int temp = head->val;
            s.push(temp);//push基础类型都是深拷贝
            head = head ->next;
        }
        vector<int> v;
        v.reserve(10000);//不能直接使用resize,resize会执行默认初始化，后续如果没有赋值到的地方，会被初始化为0
        while (!s.empty())
        {
            int t = s.top();
            v.push_back(t);
            s.pop();
        }
        return v;
    }
private:
    stack<int> s;
};
/*
* 方法一：本文件代码，利用栈的特性来反向输出
* 方法二：递归操作：快，但是浪费内存
class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        if(!head)
            return {};
        vector<int> a=reversePrint(head->next);
        a.push_back(head->val);
        return a;
    }
};
*/