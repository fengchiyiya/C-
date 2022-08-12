//给你一个整数x ，如果x是一个回文整数，返回true ；否则，返回false 。
//回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
#include<string>
#include<iostream>
using namespace std;
class Solution {
public:
    bool isPalindrome(int x) {
        string s = to_string(x);
        int size = s.size();
        int begin = 0, end = size - 1;
        while (begin<=end)
        {
            if (s[begin] != s[end])
                return false;
            begin++;
            end--;
        }
        return true;
    }
};
int main()
{
    int x = -121;
    Solution plan;
    auto n = plan.isPalindrome(x);
    cout << "n = " << n << endl;
    return 0;
}