// 给你一个字符串s和一个字符串列表wordDict作为字典。请你判断是否可以利用字典中出现的单词拼接出s 。
// 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
#include <string>
#include <vector>
using namespace std;
/*递归，该方法不行，直接G了，因为ccbb，"cb","bc"这种情况，
字符串裁剪递归的方法会误判正确，因为裁剪会改变相对位置*/
// class Solution
// {
// public:
//     bool flag=false;
//     bool check(string& s,vector<string>&wordDict,int length)
//     {
//         if(length==0)
//         {
//             flag=true;//还是得赋值为true，因为可能不止一次进入该函数
//             return flag;
//         }
//         else if(length<0)
//             return false;
//         for(const auto&subStr:wordDict)
//         {
//             int pos=s.find(subStr);
//             if(pos!=s.npos)//找到了
//             {
//                 string temp{s};
//                 temp.erase(pos,subStr.size());
//                 check(temp,wordDict,length-subStr.size());
//             }
//         }
//         return false;
//     }
//     bool wordBreak(string s, vector<string> &wordDict)
//     {
//         int length=s.size();//匹配长度
//         check(s,wordDict,length);
//         return flag;
//     }
// };

/*动态规划,该题需要从头开始匹配，不能随机匹配，随机匹配不符合题意
dp[i]=dp[j]&&check(s[j...i-1)
这题是一维数组，但是可以用双重循环来实现动态规划，以后遇到类似的题可以参考一下*/
#include <unordered_set>
class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> word_set;
        for (const auto &word : wordDict)
        {
            word_set.insert(word);
        }
        const int n = s.size();
        //状态列表
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        // dp[n+1]代表到s[i]的字符串是否合法
        for (int i = 1; i <= n + 1; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (!dp[j]) // dp[j]不合法，则直接跳过
                    continue;
                //检查s[0,j-1]和s[j,i-1]是否都合法,这里可以进一步优化，判断[0,j-1]可以拿到外面循环
                if (dp[j] && word_set.count(s.substr(j, i - j)))
                {
                    dp[i] = true;
                }
            }
        }
        return dp[n];
    }
};
// 更快的dp, 时间复杂度: O(N * M), N是字符串s的长度, M是数组wordDict的长度
class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> word_set;
        for (const auto &word : wordDict)
        {
            word_set.insert(word);
        }
        const int n = s.size();
        //状态列表
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        // dp[n+1]代表到s[i]的字符串是否合法
        for (int i = 1; i <= n + 1; ++i)
        {
            if(!dp[i-1])
                continue;
            for (auto word:wordDict)//执行到这，说明[0,i-1]是可以拆分的，dp[i]代表的字符串的i-1位置，要记住
            {
                int j=i-1+word.size();
                if(j<=n+1&&word_set.count(s.substr(i-1,j-i+1)))
                    dp[j]=true;
            }
            
        }
        return dp[n];
    }
};
