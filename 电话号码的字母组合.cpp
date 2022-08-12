//给定一个仅包含数字2-9的字符串，返回所有它能表示的字母组合。答案可以按任意顺序 返回。
//给出数字到字母的映射如下（与电话按键相同）。注意1不对应任何字母。
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <unordered_map>
using namespace std;
/*
BFS:广度优先算法将每一层的结果存入队列中，同时删除上一层的结果
广度优先算法的核心，队列的size要用上，不然会陷入死循环
广度优先搜索的临时变量的创建和pop均在内层循环中。
*/
// class Solution
// {
// public:
//     unordered_map<int, string> valueString = {
//         {2, "abc"},
//         {3, "def"},
//         {4, "ghi"},
//         {5, "jkl"},
//         {6, "mno"},
//         {7, "pqrs"},
//         {8, "tuv"},
//         {9, "wxyz"},
//     };
//     vector<string> letterCombinations(string digits)
//     {
//         queue<string> q;
//         auto s0 = valueString[digits[0] - '0'];
//         vector<string> v;
//         if (digits.size() == 1)
//         {
//             for (size_t i = 0; i < s0.size(); i++)
//             {
//                 // emplace_back直接右值插入，当数据不需要重复使用时，可以使用
//                 v.push_back(string{s0[i]});
//             }
//             return v;
//         }
//         for (size_t i = 0; i < s0.size(); i++)
//         {
//             q.push(string{s0[i]});
//         }
//         int i = 1;
//         while (!q.empty())
//         {
//             int size = q.size();
//             //这个size要用上
//             for (size_t id = 0; id < size; ++id)
//             {
//                 string temp = q.front();
//                 q.pop();
//                 if (i >= digits.size())
//                     break;
//                 auto str = valueString[digits[i] - '0'];
//                 // cout << "str = " << str << endl;
//                 for (size_t j = 0; j < str.size(); ++j)
//                 {
//                     if (i == digits.size() - 1)
//                     {
//                         v.push_back(temp + string{str[j]});
//                     }
//                     else
//                         q.push(temp + string{str[j]});
//                 }
//             }
//             i++;
//         }
//         return v;
//     }
// };
/*递归回溯
首先使用哈希表存储每个数字对应的所有可能的字母，然后进行回溯操作。
回溯过程中维护一个字符串，表示已有的字母排列（如果未遍历完电话号码的所有数字，则已有的字母排列是不完整的）。该字符串初始为空。每次取电话号码的一位数字，从哈希表中获得该数字对应的所有可能的字母，并将其中的一个字母插入到已有的字母排列后面，然后继续处理电话号码的后一位数字，直到处理完电话号码中的所有数字，即得到一个完整的字母排列。然后进行回退操作，遍历其余的字母排列。
回溯算法用于寻找所有的可行解，如果发现一个解不可行，则会舍弃不可行的解。在这道题中，由于每个数字对应的每个字母都可能进入字母组合，因此不存在不可行的解，直接穷举所有的解即可。
通过引用在回溯中修改值，一般用在容器中，比如返回一个容器
*/
class Solution
{
public:
    unordered_map<int, string> valueString = {
        {2, "abc"},
        {3, "def"},
        {4, "ghi"},
        {5, "jkl"},
        {6, "mno"},
        {7, "pqrs"},
        {8, "tuv"},
        {9, "wxyz"},
    };
    //通过引用在递归回溯中改变参数
    void backtrack(const unordered_map<int, string> &valueString, string &digits, int index, vector<string> &combinations, string &combination)
    {
        if (index == digits.size())
            combinations.push_back(combination);
        else
        {
            int i=digits[index]-'0';
            //valueString[i];const对象不能使用下标，下标操作代表插入或查找，有修改对象的风险，和const的对象冲突
            string letters=valueString.at(i);
            for (auto c:letters)
            {
                combination.push_back(c);//string也有push_back，直接对字符操作
                backtrack(valueString, digits, index+1, combinations, combination);
                combination.pop_back();
            }  
        }
    }
    vector<string> letterCombinations(string digits)
    {
        vector<string> combinations;
        string combination;
        if (digits.empty())
            return combinations;
        backtrack(valueString, digits, 0, combinations, combination);
        return combinations;
    }
};
int main()
{
    string digits = "234";
    Solution plan;
    auto x = plan.letterCombinations(digits);
    cout << "x = " << x.size() << endl;
    unordered_map<int,string> map{{1,"asdd"}};
    auto x=map[1];
    return 0;
}
