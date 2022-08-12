//编写一个函数来查找字符串数组中的最长公共前缀。
//如果不存在公共前缀，返回空字符串 ""。
#include<vector>
#include<string>
using namespace std;
/*横向搜索：
先讲两个字符串比较找到公共子串，然后讲公共子串依次和剩下的字符串使用
*/
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
		string prefix=strs[0];
		for (size_t i = 1; i < strs.size(); ++i)
		{
			string curfix = prefix;
			prefix.clear();
			for (size_t j = 0; j < strs[i].size(); ++j)
			{
				if (curfix[j] == strs[i][j])
				{
					prefix.append(string{ strs[i][j] });
				}
				else
					break;
			}
		}
		return prefix;
    }
};
/*纵向扫描：按列搜索
*/
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (!strs.size()) {
            return "";
        }
        int length = strs[0].size();
        int count = strs.size();
        for (int i = 0; i < length; ++i) {
            char c = strs[0][i];
            for (int j = 1; j < count; ++j) {
                if (i == strs[j].size() || strs[j][i] != c) {//某一字符串结束，或者某一列不相等
                    return strs[0].substr(0, i);
                }
            }
        }
        return strs[0];
    }
};