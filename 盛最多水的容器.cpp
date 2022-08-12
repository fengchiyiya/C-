//给定一个长度为n的整数数组height 。有n条垂线，第i条线的两个端点是(i, 0)和(i, height[i])。
//找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
//返回容器可以储存的最大水量。
#include<vector>
using namespace std;
/*双指针
假设left,right分别指向height的左右边界，值分别为x,y，并且x<=y,t为距离。
容积为min(x,y)*t=xt
如果向左移动右指针，则right指向的值为y1，距离t1<t。
如果y1>y,则min(x,y1)=min(x,y)=x,
容积为xt1<xt。
如果y1<=y,则min(x,y1)<=min(x,y)=x,
容积为min(x,y1)*t1<xt
由此可见，移动height值高的指针必然不会的得到比原来更大的结果
*/
class Solution {
public:
    int maxArea(vector<int>& height) {
        int size = height.size();
        int left = 0, right = size - 1;
        int maxVolume = 0;
        while (left<right)
        {
            int volume = min(height[left], height[right]) * (right - left);
            if (height[left]<height[right])
            {
                left++;
            }
            else
            {
                right--;
            }
            maxVolume = max(maxVolume, volume);
        }
        return maxVolume;
    }
};