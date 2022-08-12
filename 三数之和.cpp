//给你一个包含n个整数的数组nums，判断nums中是否存在三个元素a,b,c,使得a+b+c=0？
//请你找出所有和为0且不重复的三元组。
#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;
/*排序+双指针：
虽然想到了这个方法，但是还是没理清关系，还是在基于三重循环的基础上改进的。
所谓不重复就是三元组(a,b,c)满足a<=b<=c，保证只有这个顺序的三元组会被枚举到*/
//class Solution {
//public:
//    vector<vector<int>> threeSum(vector<int>& nums) {
//        int n = nums.size();
//        sort(nums.begin(), nums.end());
//        vector<vector<int>> ans;
//        // 枚举 a
//        for (int first = 0; first < n; ++first) {
//            // 需要和上一次枚举的数不相同
//            if (first > 0 && nums[first] == nums[first - 1]) {
//                continue;
//            }
//            // c 对应的指针初始指向数组的最右端
//            int third = n - 1;
//            int target = -nums[first];
//            // 枚举 b
//            for (int second = first + 1; second < n; ++second) {
//                // 需要和上一次枚举的数不相同
//                if (second > first + 1 && nums[second] == nums[second - 1]) {
//                    continue;
//                }
//                // 需要保证 b 的指针在 c 的指针的左侧
//                while (second < third && nums[second] + nums[third] > target) {
//                    --third;
//                }
//                // 如果指针重合，随着 b 后续的增加
//                // 就不会有满足 a+b+c=0 并且 b<c 的 c 了，可以退出循环
//                if (second == third) {
//                    break;
//                }
//                if (nums[second] + nums[third] == target) {
//                    ans.push_back({ nums[first], nums[second], nums[third] });
//                }
//            }
//        }
//        return ans;
//    }
//};
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> vecs;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        for (size_t first = 0; first < n; ++first)
        {
            //当first大于0时，必须保证进入循环时的first和前一个first值不同
            if (first > 0 && nums[first] == nums[first - 1])//注意是前一个值
                continue;
            int third = n - 1;
            int target = -nums[first];//目标值
            //second不能超过third
            for (size_t second = first+1; second < third; ++second)
            {
                //同理，second也得保证和上一个second值不同
                if (second > first + 1 && nums[second] == nums[second - 1])
                    continue;
                while (second<third&&nums[second]+nums[third]>target)
                {
                    third--;
                }
                //third发生了变化，需要判断是否满足second小于third
                if (second == third)//注意second不可以和third相等，相等后必然没有满足的三元组
                    break;
                if (target == nums[second] + nums[third])
                {
                    cout << nums[first] << " , " << nums[second] << " , " << nums[third] << endl;
                    vecs.push_back(vector<int>{nums[first], nums[second], nums[third]});
                }
            }
        }
        return vecs;
    }
};
int main()
{
    //vector<int> v{ -1,0,1,2,-1,-4 };
    vector<int> v{ 1,2,-2,-1};
    //vector<int> v{ 0,0,0,0 };
    Solution plan;
    auto x = plan.threeSum(v);
    cout << " x = " << x.size() << endl;
    return 0;
}