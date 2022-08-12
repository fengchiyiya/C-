//给定一个mxn二维字符网格board和一个字符串单词word。如果word存在于网格中，返回true;否则，返回false。
//单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
//同一个单元格内的字母不允许被重复使用。
#include <vector>
#include <string>
#include <iostream>
using namespace std;
/*递归一定要注意状态还原
还有返回值要及时返回，在最后返回的话，返回的是最新的值，不一定是需要的值
中间如果产生了true,在最后返回的话，会被flase刷新掉*/
class Solution
{
public:
    vector<pair<int, int>> dirs{{-1,0},{1, 0}, {0, -1}, {0, 1}}; //上，下，左，右三个顺序
    bool findBoard(vector<vector<bool>> &flags, vector<vector<char>> &board, string word, int id, int x, int y)
    {
        if (board[x][y] == word[id])
        {
            flags[x][y] = false;
            if (id == word.length() - 1)
            {
                return true;
            }
        }
        else
            return false;
        bool state = false;
        for (auto &[dir_x, dir_y] : dirs)
        {
            int newX = x + dir_x, newY = y + dir_y;
            if (newX >= 0 && newX < board.size() && newY >= 0 && newY < board[0].size())
                if (flags[newX][newY])
                    state = findBoard(flags, board, word, id + 1, newX, newY);
            if (state)
                return state;
        }
        flags[x][y] = true; //状态还原
        return state;
    }
    bool exist(vector<vector<char>> &board, string word)
    {
        if (board.empty())
            return false;
        int m = board.size();
        int n = board[0].size();
        vector<vector<bool>> flags(m, vector<bool>(n, true));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                auto flag = findBoard(flags, board, word, 0, i, j);
                if (flag)
                    return flag;
            }
        }
        return false;
    }
};
int main()
{
    // vector<vector<char>> v{{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    vector<vector<char>> v{{'a','b'},{'c','d'}};
    string s = "acdb";
    Solution plan;
    auto state = plan.exist(v, s);
    cout << state << endl;
    return 0;
}