/*在字符串s中找出第一个只出现一次的字符。
如果没有，返回一个单空格.s只包含小写字母。*/
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;
/*查找出现次数的一般使用哈希表,哈希表查询方便，遍历不方便*/
class Solution {
public:
    char firstUniqChar(string s) {
        vector<char> vc;
        unordered_map<char, int> map;
        for (char& a:s)
        {
            if (find(vc.begin(), vc.end(), a) == vc.end())//第一次出现
            {
                vc.push_back(a);
                map[a]++;
                continue;
            }
            else//第二次出现
            {
                map[a]++;
            }
        }
        for (auto& elm : vc)
        {
            if (map[elm] == 1)
                return elm;
        }
        return ' ';
    }
};
/*我们也可以借助队列找到第一个不重复的字符。队列具有「先进先出」的性质，
因此很适合用来找出第一个满足某个条件的元素。
在维护队列时，可以使用了「延迟删除」这一技巧。
也就是说，即使队列中有一些字符出现了超过一次，但它只要不位于队首，那么就不会对答案造成影响，
我们也就可以不用去删除它。只有当它前面的所有字符被移出队列，它成为队首时，我们才需要将它移除。
*/