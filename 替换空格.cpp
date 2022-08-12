#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
//请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

//1.使用string类自身的的find函数，配合erase和insert，注意和stl顺序容器的不同，返回的不是迭代器
//class Solution {
//public:
//    string replaceSpace(string s) {
//		string x = "%20";
//		string flag = " ";
//		string::size_type pos = 0;
//		while(pos!=s.npos)
//		{
//			pos= s.find(flag,pos);//从pos开始查找
//			if (pos != s.npos)
//			{
//				s.erase(pos, 1);//string的erase返回的不是迭代器是字符串引用
//				s.insert(pos,x);//insert(下标，字符串）；insert(迭代器，字符串首地址，尾地址）
//				pos += 2;
//			}
//		}
//		for (auto c : s)
//			cout << c;
//		cout << endl;
//		return s;
//    }
//};

//直接循环使用replace，replace(pos,len,string)
//class Solution {
//public:
//	string replaceSpace(string s) {
//		string x = "%20";
//		string flag = " ";
//		string::size_type pos = 0;
//		while (pos != s.npos)
//		{
//			pos = s.find(flag, pos);//从pos开始查找
//			if (pos != s.npos)
//			{
//				s.replace(pos, 1, x);//pos,len,string
//			}
//		}
//		for (auto c : s)
//			cout << c;
//		cout << endl;
//		return s;
//	}
//};

//使用数组依次拷贝
class Solution {
public:
	string replaceSpace(string s) {
		string x = "%20";
		string temp;
		for (auto& c : s)
		{
			if (c == ' ')
			{
				temp.append(x);
			}
			else
			{
				temp.push_back(c);
			}
		}
		return temp;
	}
};
int main()
{
	string s = "we are happy";
	Solution plan;
	plan.replaceSpace(s);
	return 0;
}