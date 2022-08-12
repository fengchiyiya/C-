//输入一个整数数组实现一个函数来调整该数组中数字的顺序，使得所有奇数在数组的前半部分，
//所有偶数在数组的后半部分。
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        if (nums.empty())
            return nums;
        vector<int> temp(nums.size(),0);
        auto begin = temp.begin(),end=temp.end()-1;
        for (auto& num:nums)
        {
            if (num % 2 == 1)
            {
                *begin= num;
                begin++;
            }
            else
            {
                *end = num;
                end--;
            }
        }
        return temp;
    }
};
/*双指针在原数组上修改，对数组前后进行交换，找前部分的偶数和尾部分的奇数交换
同时，判断奇偶使用位操作更加快*/
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        if (nums.empty())
            return nums;
        auto begin = nums.begin(), end = nums.end() - 1;
        while (begin!=end)
        {
            while (begin<end&&(*begin&1)==1)//奇数继续增加，直到begin指向偶数
                begin++;
            while (begin < end && (*end & 1) == 0)//偶数继续减少，
                end--;
            swap(*begin, *end);
        }
        return nums;
    }
};