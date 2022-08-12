#include<vector>
#include<iostream>
#include<unordered_map>
#include<algorithm>
using namespace std;
//在一个长度为 n 的数组 nums 里的所有数字都在 0～n - 1 的范围内。
//数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。
//请找出数组中任意一个重复的数字。
/*最朴素的思想：遍历找重复*/
//class Solution {
//public:
//    int findRepeatNumber(vector<int>& nums) {
//		vector<int> temp;
//		for (auto &num:nums)
//		{
//			if(temp.empty())
//			{
//				temp.push_back(num);
//				continue;
//			}
//			if(auto i = find(temp.begin(), temp.end(), num) == temp.end())//代表没找到
//				temp.push_back(num);
//			else
//			{
//				return num;
//			}
//		}
//		return -1;//遍历一圈都没找到
//    }
//};
/*利用哈希表*/
class Solution {
public:
	int findRepeatNumber(vector<int>& nums) {
		unordered_map<int,int> temp;
		for (auto &num : nums)
		{
			temp[num]++;
			if(temp[num]>=2)
				return num;
		}
		return nums[nums.size()-1];//遍历一圈都没找到
	}
};