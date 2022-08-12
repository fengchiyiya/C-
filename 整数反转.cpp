//给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。
//如果反转后整数超过 32 位的有符号整数的范围 [−231, 231 − 1] ，就返回 0。
//假设环境不允许存储 64 位整数（有符号或无符号）。
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
//char型字符参与数字运算，都是用的ascll码 -‘0’变为数字
//翻转字符，栈也可以考虑一试；
//但是题目要求不允许使用 6464 位整数，即运算过程中的数字必须在 3232 位有符号整数的范围内，
//因此我们不能直接按照上述式子计算，需要另寻他路。
//class Solution {
//public:
//    int reverse(int x) {
//        int rev = 0;
//        while (x != 0) {
//            //有溢出，直接返回0
//            if (rev < INT_MIN / 10 || rev > INT_MAX / 10) {
//                return 0;
//            }
//            //这样子，负数也没关系，还解决结尾为0的情况
//            int digit = x % 10;//余数，从最低位开始
//            x /= 10;
//            rev = rev * 10 + digit;
//        }
//        return rev;
//    }
//};
class Solution {
public:
    int reverse(int x) {
        int rev = 0;
        while (x!=0)
        {
            if (rev > INT_MAX / 10 || rev < INT_MIN / 10)
            {
                return 0;
            }
            int digit = x % 10;
            x = x / 10;
            rev = rev * 10 + digit;
        }
        return rev;
    }
};
int main()
{
    int n = 1463847412;
    Solution plan;
    auto x=plan.reverse(n);
    cout << "x = " << x << endl;
    return 0;
}