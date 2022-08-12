//字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。
//请定义一个函数实现字符串左旋转操作的功能。
//比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。
#include<string>
#include<iostream>
using namespace std;
//循环+利用append函数
//class Solution {
//public:
//    string reverseLeftWords(string s, int n) {
//        for (size_t i = 0; i < n; ++i)
//        {
//            char c = s[i];
//            s.append(string(1,c));//用字符构建字符串
//        }
//        s.erase(0, n);
//        return s;
//    }
//};
//字符串切片
class Solution {
public:
    string reverseLeftWords(string s, int n) {
        string temp = s.substr(0, n);
        s.erase(0, n);
        s.append(temp);
        return s;
    }
};
int main()
{
    string s = "abcdefg";
    Solution plan;
    plan.reverseLeftWords(s, 2);
    return 0;
}