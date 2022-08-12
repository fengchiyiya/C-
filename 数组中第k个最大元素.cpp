// 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
// 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
#include <vector>
using namespace std;
/*第一眼感觉就是考排序*/

/*快速排序*/
class Solution
{
public:
    void quickSort(vector<int> &nums, int begin, int end)
    {
        //快速排序的退出条件，不要忘了
        if (begin >= end)
            return;
        int key = nums[begin];
        int l = begin, r = end;
        // key是左边的话，需要从右半部分开始寻找
        while (l < r)
        {
            while (l < r && nums[r] >= key) // 右半部分寻找小于key的值
            {
                --r;
            }
            while (l < r && nums[l] <= key) // 左半部分寻找大于key的值
            {
                ++l;
            }
            swap(nums[l], nums[r]);
        }
        swap(nums[begin], nums[l]);
        quickSort(nums, begin, l - 1);
        quickSort(nums, l + 1, end);
    }
    int findKthLargest(vector<int> &nums, int k)
    {
        if (nums.empty())
            return -1;
        int n = nums.size() - 1;
        quickSort(nums, 0, n);
        // 第k大的元素，代表对排序后的数组从后往前遍历
        for (int i = n; i >= 0; i--)
        {
            --k;
            if (k == 0)
                return nums[i];
        }
        return -1;
    }
};
/*堆排序
堆排序，升序排列需要创建大根堆
堆排序：
    1.构建大根堆：大根堆就是根节点是树的最大值
    2.将根放在结尾，重新构建大根堆
注意事项：
下标为i的节点的父节点的下标：i/2；
i节点的左子节点的下标为2*i+1；
i节点的右子节点的下标为2*i+2;
最后的父节点索引为n/2 - 1。n为最大的下标
*/
class Solution
{
public:
    //维护大根堆的性质
    void heapify(vector<int> &nums, int begin, int end)
    {
        while (begin <= end)
        {
            int leftChild = 2 * begin + 1;
            int rightChild = 2 * begin + 2;
            int maxElem = begin;
            if (rightChild <= end && nums[maxElem] < nums[rightChild])
                maxElem = rightChild;
            if (leftChild <= end && nums[maxElem] < nums[leftChild])
                maxElem = leftChild;
            if (maxElem != begin)
            {
                swap(nums[maxElem], nums[begin]);
                //继续查看修改后的大根堆的下一层是否符合情况
                begin = maxElem;
            }
            else
                break;//维护堆性质时，注意退出，不然容易形成死循环
        }
    }
    // 构建大根堆
    void buildHeap(vector<int> &nums, int size)
    {
        //从最后一个父节点开始，依次向前构建
        for (int i = size / 2; i >= 0; --i)
        {
            heapify(nums, i, size);
        }
    }
    void heapSort(vector<int> &nums)
    {
        int n = nums.size() - 1;
        //构建大根堆
        buildHeap(nums, n);
        for (size_t i = 0; i < n; i++)
        {
            int len = n - i;
            swap(nums[0], nums[len]);
            heapify(nums, 0, len - 1);
        }
    }
    int findKthLargest(vector<int> &nums, int k)
    {
        int n = nums.size() - 1;
        heapSort(nums);
        for (int i = n; i >= 0; i--)
        {
            --k;
            if (k == 0)
                return nums[i];
        }
        return -1;
    }
};