//数字n代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且有效的括号组合
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
/*暴力法
生成所有可能的序列(2^(2n))，然后检查每一个是否有效即可。
*/
/*深度优先遍历dfs
一个合法的括号序列需要满足两个条件
1：左右括号的数量相等
2：任意前缀中左括号数量>=右括号数量(也就是说每一个右括号总能找到相匹配的左括号)
搜索过程如下：
1.初始时定义序列的左括号数量lc和右括号rc都为0
2.如果lc<n，左括号的个数小于n，则在当前序列str后拼接左括号
3.如果rc<n&&lc>rc，则在当前序列str后拼接右括号
3.当lc==n&&rc==n时，将当前合法序列str加入容器中
*/
class Solution
{
public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> ans;
        string str;
        dfs(ans,0,0,n,str);
        return ans;
    }
    void dfs(vector<string> &ans, int lc, int rc, int n, string str)
    {
        if (lc == n && rc == n)
            ans.push_back(str);
        if (lc < n)
            //不能改变str，会影响下面的if
            dfs(ans,lc+1,rc,n,str+'(');
        if(rc<n&&lc>rc)
            dfs(ans,lc,rc+1,n,str+')');
    }
};