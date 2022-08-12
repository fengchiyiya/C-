//单词必须按照字母顺序，通过相邻的单元格内的字母构成，
//其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
#include<vector>
#include<string>
using namespace std;
/*递归+回溯
将字符串元素拆分字符，放入递归中比较，这样就如之前的递归练习一样了
矩阵路径问题采用方向数组是个不错的办法。
注意递归的推出条件和返回值的位置*/
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty())
            return false;
        int row = board.size();
        int col = board[0].size();
        vector<vector<int>> visited(row, vector<int>(col));
        for (size_t i = 0; i < row; ++i)
        {
            for (size_t j = 0; j < col; ++j)
            {
                if (board[i][j]==word[0])
                {
                    bool flag=find(board, visited, i, j, word,0);
                    if (flag)
                        return flag;
                }
            }
        }
        return false;
    }
    bool find(vector<vector<char>>& board, vector<vector<int>>visited, int i, int j, string word,int k)
    {
        if (board[i][j] != word[k])
            return false;
        if (board[i][j] == word[k] && k == word.size() - 1)
            return true;
        vector<pair<int, int>>direction{ {0,-1},{0,1},{-1,0},{1,0} };//矩阵常用这种方法寻找路径
        int row = board.size();
        int col = board[0].size();
        visited[i][j] = -1;
        for (const auto& dir:direction)
        {
            int newRow = i + dir.first;
            int newCol = j + dir.second;
            if (newRow >= 0 && newRow < row && newCol>=0 && newCol < col)
            {
                if (visited[newRow][newCol] != -1)
                {
                    //开头的return只是返回最底层的递归调用，后面还是需要返回值的，需要递归后还需要return
                    bool flag = find(board, visited, newRow, newCol, word, k + 1);
                    if (flag)//如果为true，代表找到了，直接返回
                    {
                        return flag;
                        break;
                    }
                }
            }
        }
        //当前节点不满足条件，占用取消
        visited[i][j] = 0;
        return false;//如果没有提前返回，直接返回false
    }
};