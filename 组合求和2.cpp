// 给定一个候选人编号的集合 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
// candidates 中的每个数字在每个组合中只能使用 一次 。
// 注意：解集不能包含重复的组合。 
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
private:
    vector<pair<int, int>> freq; // val,cnt
    vector<vector<int>> ans;
    vector<int> sequence;

public:
    void dfs(int pos, int rest)
    {
        if (rest == 0)
        {
            ans.push_back(sequence);
            return;
        }
        if (pos == freq.size() || rest < freq[pos].first)
        {
            return;
        }
        // 不选择当前位置
        dfs(pos + 1, rest);

        int most = min(rest / freq[pos].first, freq[pos].second);
        // 去重
        for (int i = 1; i <= most; ++i)
        {
            sequence.push_back(freq[pos].first);
            dfs(pos + 1, rest - i * freq[pos].first); // 选择了i次
        }
        for (int i = 1; i <= most; ++i)
        {
            sequence.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        for (int num : candidates)
        {
            if (freq.empty() || num != freq.back().first)
            {
                freq.emplace_back(num, 1);
            }
            else
            {
                ++freq.back().second;
            }
        }
        dfs(0, target);
        return ans;
    }
};