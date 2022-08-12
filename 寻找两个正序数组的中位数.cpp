//给定两个大小分别为m和n的正序（从小到大）数组nums1和nums2。请你找出并返回这两个正序数组的中位数。
//算法的时间复杂度应该为O(log(m + n))。
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
/*利用sort函数，sort函数类似快速排序  logN的时间复杂度*/
//class Solution {
//public:
//    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
//        int n1 = nums1.size();
//        int n2 = nums2.size();
//        vector<int> nums(n1+n2,0);//{}是赋值初始化，里面的元素用来赋值；()是构造函数
//        copy(nums1.begin(), nums1.end(), nums.begin());
//        copy(nums2.begin(), nums2.end(), nums.begin()+nums1.size());
//        sort(nums.begin(), nums.end());//sort的时间复杂度logN
//        if (nums.size() & 1)//位与操作：1为奇数
//            return (double)nums[nums.size() / 2];
//        else
//        {
//            return (double)(nums[nums.size() / 2] + nums[nums.size()/2 - 1]) / 2;
//        }
//    }
//};
/*容器尺寸已知，只要找到中位数的位置即可，寻找第k小的数字。时间复杂度为logN一般想到二分法*/
class Solution {
public:
    int getKthElements(vector<int>& nums1, vector<int>& nums2, int k)
    {
        /*寻找第k小的元素，即顺序数组的索引k-1的值*/
        /* 主要思路：要找到第 k (k>1) 小的元素，那么就取 pivot1 = nums1[k/2-1] 和 pivot2 = nums2[k/2-1] 进行比较
        * 这里的 "/" 表示整除
        * nums1 中小于等于 pivot1 的元素有 nums1[0 .. k/2-2] 共计 k/2-1 个
        * nums2 中小于等于 pivot2 的元素有 nums2[0 .. k/2-2] 共计 k/2-1 个
        * 取 pivot = min(pivot1, pivot2)，两个数组中小于等于 pivot 的元素共计不会超过 (k/2-1) + (k/2-1) <= k-2 个
        * 这样 pivot 本身最大也只能是第 k-1 小的元素
        * 如果 pivot = pivot1，那么 nums1[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums1 数组
        * 如果 pivot = pivot2，那么 nums2[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums2 数组
        * 由于我们 "删除" 了一些元素（这些元素都比第 k 小的元素要小），因此需要修改 k 的值，减去删除的数的个数
        */
        int n1 = nums1.size();
        int n2 = nums2.size();

        int newIdx1=0,newIdx2=0;//记录数组的索引变化
        while (k>0)
        {
            if (newIdx1 == n1)//第一个数组遍历完，直接返回第二个数组的剩余k值
                return nums2[newIdx2 + k-1 ];//变成索引要-1
            if (newIdx2 == n2)//第二个数组遍历完，直接返回第一个数组的剩余k值
                return nums1[newIdx1 + k-1 ];
            if (k == 1)//返回数组的最小值
                return min(nums1[newIdx1], nums2[newIdx2]);
            int idx1 = min(newIdx1 + k / 2 - 1, n1 - 1);//使用min，代替三元运算符
            int idx2 = min(newIdx2 + k / 2 - 1,n2 - 1);
            int pivot1 = nums1[idx1];
            int pivot2 = nums2[idx2];
            if (pivot1 <= pivot2)
            {
                k -= idx1 - newIdx1 + 1;//减去排除的值
                newIdx1 = idx1+1;//注意，记录数组顺序时，下一个位置是前一个位置+1,不是链表
            }
            else if (pivot1 > pivot2)
            {
                k -= idx2 - newIdx2 + 1;
                newIdx2 = idx2+1;
            }//相等的情况不能单独处理，0到k/2-1一共k/2个数，都减去的话，会出现k=0的情况，
        }
        return 0;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int totalLength = nums1.size() + nums2.size();
        if (totalLength & 1)//奇数
            return getKthElements(nums1, nums2, (totalLength+1) / 2);//奇数应该要找的位置是索引+1的数，比如3,要找第2小的数，索引为1
        else
            return (getKthElements(nums1, nums2, totalLength / 2) + getKthElements(nums1, nums2, totalLength / 2 + 1)) / 2.0;
    }
};
int main()
{
    vector<int> v1{ 2,2,4,4 }, v2{ 2,2,4,4};
    Solution plan;
    auto n=plan.findMedianSortedArrays(v1,v2);
    cout << "n = " << n << endl;
    return 0;
}