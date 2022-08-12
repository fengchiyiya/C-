// 请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
// 实现 LRUCache 类：
// LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
// int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
// void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
// 函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

/*O(1)的时间复杂度，第一时间想到了哈希表。
题目还要求一个类似队列的结构来记录访问的先后顺序
哈希表+双向链表
head->node1->node2->tail
*/
#include <unordered_map>
#include <iostream>
using namespace std;
/*添加了4个双向链表的操作函数*/
class DListNode
{
public:
    int key;
    int val;
    DListNode *prev, *next;
    DListNode(int _key, int _value) : key(_key), val(_value), prev(nullptr), next(nullptr) {}
    DListNode() : key(0), val(0), prev(nullptr), next(nullptr) {}
};
class LRUCache
{
private:
    int capacity;
    int size;
    //头尾的哨兵节点 dummy节点
    DListNode *head, *tail;
    unordered_map<int, DListNode *> cache;

public:
    LRUCache(int _capacity) : capacity(_capacity), size(0)
    {
        head = new DListNode();
        tail = new DListNode();
        head->next = tail;
        tail->prev = head;
    }
    int get(int key)
    {
        if (!cache.count(key))
            return -1;
        DListNode *node = cache[key];
        //cout<<"node->val = "<<node->val<<endl;
        moveToHead(node);
        return node->val;
    }
    void put(int key, int value)
    {
        if (!cache.count(key))
        {
            DListNode *temp = new DListNode(key, value);
            //添加进哈希表
            cache[key] = temp;
            //添加至双向链表的头部
            addToHead(temp);
            ++size;
            if (size > capacity)
            {
                DListNode* temp =removeTail();
                cache.erase(temp->key);
                delete temp;
                --size;
            }
        }
        else // key存在,修改节点值
        {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DListNode *node = cache[key];
            node->val = value;
            moveToHead(node);
        }
    }
    // 在头哨兵节点后面插入节点(要求节点是存在的)
    void addToHead(DListNode *node)
    {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    // 移动到头结点
    void moveToHead(DListNode *node)
    {
        removeNode(node);
        addToHead(node);
    }
    // 移除节点(但是不释放内存)
    void removeNode(DListNode *node)
    {
        if (cache.count(node->key))
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
    }
    // 删除尾节点
    DListNode* removeTail()
    {
        DListNode* temp=tail->prev;
        removeNode(temp);
        return temp;
    }
};
int main()
{
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout<<cache.get(1)<<endl;
    cache.put(3, 3);
    cout<<cache.get(2)<<endl;
    cache.put(4,4);
    cout<<cache.get(1)<<endl;
    cout<<cache.get(3)<<endl;
    cout<<cache.get(4)<<endl;
    cout <<111111111<<endl; 
    return 0;
}