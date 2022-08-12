//请你来实现一个myAtoi(string s)函数，使其能将字符串转换成一个32位有符号整数（类似C/C++中的atoi函数）。
#include<string>
#include<vector>
#include<iostream>
#include<unordered_map>
using namespace std;
/*注意32位判断 rev<=INT_MAX/10或者rev>INT_MIN/10*/
/*状态机
字符串处理的题目往往涉及复杂的流程以及条件情况，如果直接上手写程序，一不小心就会写出极其臃肿的代码。
因此，为了有条理地分析每个输入字符的处理方法，我们可以使用自动机这个概念：
我们的程序在每个时刻有一个状态s，每次从序列中输入一个字符c，并根据字符c转移到下一个状态s'。
这样，我们只需要建立一个覆盖所有情况的从 s 与 c 映射到 s' 的表格即可解决题目中的问题。
*/
class Automaton {
    string state = "start";
    unordered_map<string, vector<string>> table = {
        {"start", {"start", "signed", "in_number", "end"}},
        {"signed", {"end", "end", "in_number", "end"}},
        {"in_number", {"end", "end", "in_number", "end"}},
        {"end", {"end", "end", "end", "end"}}
    };//第三列都是in_number(除了结束时)

    int get_col(char c) {
        if (isspace(c)) return 0;//空格只在开头才有用
        if (c == '+' or c == '-') return 1;//符号判断，只可以通过开头转向这个状态
        if (isdigit(c)) return 2;//进入数字处理
        return 3;//直接结束
    }
public:
    int sign = 1;
    long long ans = 0;

    void get(char c) {
        state = table[state][get_col(c)];
        if (state == "in_number") {
            ans = ans * 10 + c - '0';
            ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
        }
        else if (state == "signed")
            sign = c == '+' ? 1 : -1;
    }
};

class Solution {
public:
    int myAtoi(string str) {
        Automaton automaton;
        for (char c : str)
            automaton.get(c);
        return automaton.sign * automaton.ans;
    }
};

int main()
{
	//string s = "words and 987";
	string s = "-91283472332";
	string s ="-42";
	Solution plan;
	auto n = plan.myAtoi(s);
	cout << "n = " << n << endl;
	return 0;
}