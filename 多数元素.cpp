// 给定一个大小为n的数组nums，返回其中的多数元素。多数元素是指在数组中出现次数大于⌊n/2⌋的元素。
// 你可以假设数组是非空的，并且给定的数组总是存在多数元素。
#include <vector>
#include <iostream>
using namespace std;
//进阶：尝试设计时间复杂度为O(n)、空间复杂度为O(1) 的算法解决此问题。
/*哈希表可以解决，但是空间复杂度超过O(1)
快速排序+返回中点值？快速排序平均时间复杂度O(nlogN)，但是最差情况下为O(n^2)
但是堆排序和归并排序最差情况下的复杂度也为O(nlogN)*/
class Solution
{
public:
    void quickSort(vector<int> &nums, int begin, int end)
    {
        if (begin >= end)
            return;
        int key = nums[begin];
        int L = begin, R = end;
        while (begin < end)
        {
            while (begin < end && nums[end] >= key)
            {
                --end;
            }
            while (begin < end && nums[begin] <= key)
            {
                ++begin;
            }
            if (begin >= end)
                break;
            swap(nums[begin], nums[end]);
        }
        swap(nums[L], nums[begin]); // 将key放到begin的位置，后续begin不需要
        quickSort(nums, L, begin - 1);
        quickSort(nums, begin + 1, R);
    }
    int majorityElement(vector<int> &nums)
    {
        int n = nums.size();
        quickSort(nums, 0, n - 1);
        for (auto n : nums)
        {
            cout << " n =" << n << endl;
        }
        return nums[n / 2];
    }
};
/*堆排序
首先堆是一种叫做完全二叉树的数据结构。
排序思想：
1.首先将待排序的数组构造成一个大根堆，此时，整个数组的最大值就是堆结构的顶端
2.将顶端的数与末尾的数交换，此时，末尾的数为最大值，剩余待排序数组个数为n-1
3.将剩余的n-1个数再构造成大根堆，再将顶端数与n-1位置的数，再将顶端数与n-1位置的数交换。反复执行
建立大根堆，数组排序结果是升序排列
下标为i的结点的父节点的下标：i/2[i为下标]
i结点的左子结点的下标为 2*i+1;
i结点的右子结点的下标为 2*i+2;
最后的父节点索引为 n/2。n为数组中最大下标
*/
class Solution
{
public:
    //维护当前层当前结点的堆性质，并向后延申。
    void heapify(vector<int> &nums, int begin, int end)
    {
        // begin为开始的父节点位置
        while ((begin << 1) + 1 <= end)
        {
            int lson = (begin << 1) + 1;
            int rson = (begin << 1) + 2;
            int largest = begin;
            if (lson <= end && nums[lson] > nums[largest])
                largest = lson;
            if (rson <= end && nums[rson] > nums[largest])
                largest = rson;
            if (largest != begin) //不满足堆性质
            {
                swap(nums[begin], nums[largest]);
                begin = largest; //检查交换后的结点是否满足堆的性质
            }
            else
                break;
        }
    }
    void buildHeap(vector<int> &nums)
    {
        int n = nums.size();
        //最后一个非叶子结点的索引为n/2 - 1，n为数组长度；或者为i/2
        for (int i = (n >> 1)-1; i >= 0; i--) //构建的时候根节点也需要检查，因为i可以等于0！
        {
            heapify(nums, i, n);
        }
    }
    void heapSort(vector<int> &nums)
    {
        buildHeap(nums);
        int len = nums.size() - 1;
        for (int i = len; i > 0; --i)
        {
            swap(nums[0], nums[i]);
            len -= 1;
            heapify(nums, 0, len);
        }
    }
    int majorityElement(vector<int> &nums)
    {
        heapSort(nums);
        return nums[nums.size() / 2];
    }
};
/*Boyer-Moore 投票算法
1.维护一个候选众数candidate和它出现的次数count。初始时，candidate可以为任意值，count为0。
2.我们遍历数组nums中的所有元素，对于每个元素x，在判断x之前，如果count的值为0，我们先将x的值赋予candidate，
随后我们判断x:
            如果x与candidate相等，那么计数器count的值增加1
            如果x与candidate不等，那么计数器count的值减少1。
遍历完成后，candidate即为数组的众数。
count在遍历结束和真正的绑定在众数上的val是相同的*/
class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        if (nums.empty())
            return -1;
        int candidate = nums[0];
        int count = 0;
        int len = nums.size();
        for (int i = 1; i < len; i++)
        {
            if (candidate == nums[i])
                ++count;
            else
            {
                --count;
                if (count == 0)
                {
                    candidate = nums[i];
                }
            }
        }
        return candidate;
    }
};
int main()
{
    // vector<int> v{5, 2, 3, 1};
    vector<int> v{5, 1, 1, 2, 0, 0};
    Solution plan;
    plan.majorityElement(v);
    return 0;
}