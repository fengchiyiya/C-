#include<vector>
#include<unordered_map>
#include<iostream>
using namespace std;
//无序容器适合查询工作
//class Solution {
//public:
//    int search(vector<int>& nums, int target) {
//		unordered_map<int, int> map;//无序map
//		for (auto &num:nums)
//		{
//			map[num]++;
//		}
//		return map[target];
//    }
//};
/*
* 注意题目：有序数组。题目就会被转换成，怎么找到target。
使用二分法找到左右边界，最后返回right-left-1
首先判断开头是否大于target，结尾是否小于target，直接返回
开头和结尾是否都等于target，是的话直接返回
nums[m] < target ，则 target 在闭区间 [m+1,j] 中，因此执行 i = m+1；
若 nums[m] > target ，则 target 在闭区间 [i,m−1] 中，因此执行 j = m−1；
若 nums[m] = target ，则右边界 right 在闭区间 [m+1,j] 中；左边界 left 在闭区间 [i,m−1] 中。因

*/
//class Solution {
//public:
//	int search(vector<int>& nums, int target) {
//		int begin=0,end=nums.size()-1;
//		if (nums.size() == 0)//极限情况先排除
//			return 0;
//		else if (nums[begin] > target || nums[end] < target)
//			return 0;
//		else if (nums[begin] == target && nums[end] == target)
//			return nums.size();
//
//		//右边界
//		while (begin<=end)
//		{
//			int middle = (begin + end) / 2;
//			if (target<nums[middle])//target处于[begin,middle]之间
//				end=middle-1;
//			else//target处于[middle,end]之间，并且等于target时，begin还会继续增加，直到右边界
//			{
//				begin = middle + 1;
//			}
//		}
//		int right = begin;
//		begin = 0; end = nums.size() - 1;
//		//左边界
//		while (begin<=end)
//		{
//			int middle = (begin + end) / 2;
//			if (target>nums[middle])//target处于[middle,end]
//				begin = middle + 1;
//			else//target处于[begin,middle]之间，并且等于target时,end还会继续减少，直到左边界
//			{
//				end = middle - 1;
//			}
//		}
//		int left = end;
//		cout << "right = " << right << endl;
//		cout << "left = " << left << endl;
//		return right-1-left;
//	}
//};
/*如何使用递推做
*/
class Solution {
public:
	int search(vector<int>& nums, int target) {
		int begin = 0;
		int end = nums.size() - 1;
		if (nums.size() == 0)//空容器
			return 0;
		return binarySearch(nums, target, begin, end);
	}
	int binarySearch(vector<int>& nums, int target, int begin, int end)//这个递推函数是找到target，并把所有的target相加 
	{
		if (nums[begin] > target || nums[end] < target||begin>end)//begin>end也要记得退出
			return 0;
		if (nums[begin] == nums[end] && nums[begin] == target)
			return end - begin + 1;
		int middle = (begin + end) / 2;
		int x = binarySearch(nums, target, begin, middle);
		int y = binarySearch(nums, target, middle + 1, end);
		return x + y;
	}

};
int main()
{
	vector<int> nums = {5,7,7,8,8,10};
	int target = 8;
	Solution plan;
	int count=plan.search(nums, target);
	cout << count << endl;
	return 0;
}