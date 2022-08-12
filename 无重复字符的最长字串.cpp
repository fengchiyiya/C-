//给定一个字符串s ，请你找出其中不含有重复字符的最长子串的长度。
#include<string>
#include<unordered_set>
#include<iostream>
using namespace std;
/*法1：可以利用字符串的裁剪拼接*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        string subStr;
        int size = s.size();
        int maxSize = 0;
        for (size_t i = 0; i < size; ++i)
        {
            auto pos=subStr.find(s[i]);
            if (pos== subStr.npos)//没找到
            {
                subStr.append(string{ s[i] });//构造函数创建临时变量
            }     
            else//找到了
            {
                //subStr = subStr.erase(0,pos+1);//位置，和数量,采用删除
                subStr = subStr.substr(pos+1,subStr.size()-pos);
                subStr.append(string{ s[i] });
                
            };
            maxSize = max(maxSize, (int)subStr.size());
        }
        return maxSize;
    }
};
/*法2：利用双指针*/
//class Solution {
//public:
//    int lengthOfLongestSubstring(string s) {
//        int fast = 0, slow = 0;//快慢指针
//        int size = s.size();
//        unordered_set<char> subStr;//存储子串字符
//        int maxsize=0;
//        while (fast<size)
//        {
//            if (subStr.count(s[fast]))//如果找到,慢指针，开始移动，直到找到重复的字符
//            {
//                while (slow<=fast)//如何进入循环
//                {
//                    subStr.erase(s[slow]);//删除重复字符之前的记录,主力这里不能++，否则下一步就会出错
//                    if (s[slow++] == s[fast])
//                        break;
//                }
//            }
//            subStr.insert(s[fast++]);//字符串索引得到的char字符
//            maxsize = max(maxsize, fast - slow);
//        }
//        return maxsize;
//    }
//};
int main()
{
    Solution plan;
    //string s = "pwwkew";
    string s = "abcabcbb";
    //string s = "bbbbb";
    //string s = "aabaab!bb";
    auto n=plan.lengthOfLongestSubstring(s);
    cout << "n = " << n << endl;
    return 0;
}