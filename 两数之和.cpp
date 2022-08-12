#include<vector>
using namespace std;
//给定一个整数数组nums和一个整数目标值target，请你在该数组中找出和为目标值target的那两个整数，并返回它们的数组下标。
//你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。你可以按任意顺序返回答案。
#include<unordered_map>
#include<iostream>
/*法1暴力枚举比较简单*/
/*哈希表
查询是否存在target-x这个元素存在*/
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int>ids;
        unordered_map<int, int> map;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            if (map.count(target - nums[i]))//是否存在target-nums[i]
            {
                ids.emplace_back(i);
                ids.emplace_back(map[target-nums[i]]);
                return ids;
            }
            map[nums[i]] = i;//记录位置
        }
        return ids;
    }
};
int main()
{
    Solution plan;
    vector<int> s{2, 7, 11, 15};
    auto x =plan.twoSum(s, 9);
    for (auto a:x)
    {
        cout << a << endl;
    }
    return 0;
}