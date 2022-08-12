//给你一个字符串数组，请你将字母异位词组合在一起。可以按任意顺序返回结果列表。
//字母异位词 是由重新排列源单词的字母得到的一个新单词，所有源单词中的字母通常恰好只用一次。
//其实就是找到由相同字母组合的字符串
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
using namespace std;
/*利用unorder_set统计，还可以直接利用unorder_map统计，更加方便快捷*/
class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<string> flag(strs);
        vector<vector<string>> vv;
        unordered_set<string> s; //判断是否插入过
        for (size_t i = 0; i < strs.size(); i++)
        {
            sort(flag[i].begin(), flag[i].end()); //按照字符大小重新排列
        }
        for (size_t i = 0; i < flag.size(); ++i)
        {
            vector<string> temp;
            if (!s.count(flag[i]))
            {
                s.insert(flag[i]);
                auto x = find(flag.begin(), flag.end(), flag[i]);
                while (x != flag.end())
                {
                    auto id = distance(flag.begin(), x); //根据迭代器获取下标
                    temp.push_back(strs[id]);
                    // cout<<"str = "<<strs[id]<<endl;
                    x = find(x+1, flag.end(), flag[i]);//是否有重复的字符串
                }
                vv.emplace_back(temp);
            }
        }
        return vv;
    }
};
/*对标准库的容器认识还不够，unorder_map的键可以是容器，这样就可以存储同个key的不同元素*/
class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> vv;
        unordered_map<string,vector<string>> m; //判断是否插入过,first为排序后的字符串，second为原字符串
        for (size_t i = 0; i < strs.size(); i++)
        {
            string flag=strs[i];
            sort(flag.begin(), flag.end()); //按照字符大小重新排列
            m[flag].emplace_back(strs[i]);
        }
        for (auto it = m.begin(); it !=m.end(); ++it)
        {
            vv.emplace_back(it->second);
        }
        return vv;
    }
};
int main()
{
    vector<string> strs{"eat", "tea", "tan", "ate", "nat", "bat"};
    Solution plan;
    auto n = plan.groupAnagrams(strs);
    cout << "n = " << n.size() << endl;
    return 0;
}