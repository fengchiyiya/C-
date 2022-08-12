// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
// 此外，你可以假设该网格的四条边均被水包围。
#include <vector>
#include <iostream>
using namespace std;
/*通俗化来说：1的上下左右如果全为0，则是岛屿；如果不全为0，则一直迭代判断
边界外为0，单独判断迭代方向
用空间换时间？
深度优先搜索：
独立解出来了！很开心，遍历二维矩阵，当找到1时，进入迭代，同时将迭代时遍历的到的1都记录，
保证下次不会重复遍历。同时这样的好处是便于计数，每进入依次迭代就代表找到1个岛屿。
有1个1，代表至少有1个岛屿*/
class Solution
{
public:
    int len = 0;
    vector<pair<int, int>> directions{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    //可以使用grid节省内存，找到的1赋值为0；
    void dfs(vector<vector<char>> &grid, int m, int n, int x, int y)
    {
        if (grid[x][y] == '0')
            return;
        else if (grid[x][y] == '1') //将为1的地方赋值为1，0不动
            grid[x][y] = '0';
        for (auto [_x, _y] : directions) //[]直接取pair的两个变量值
        {
            int newX = x + _x;
            int newY = y + _y;
            if (newX >= 0 && newX < m && newY >= 0 && newY < n)
                dfs(grid, m, n, newX, newY);
        }
    }
    int numIslands(vector<vector<char>> &grid)
    {
        if (grid.empty())
            return len;
        int m = grid.size();//使用尺寸前，先判断容器是否为空
        int n = grid[0].size();
        for (size_t i = 0; i < m; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if (grid[i][j] == '0')
                    continue;
                else
                {
                    dfs(grid, m, n, i, j);
                    ++len;
                }
            }
        }
        return len;
    }
};
/*同样地，我们也可以使用广度优先搜索代替深度优先搜索。
为了求出岛屿的数量，我们可以扫描整个二维网格。如果一个位置为 1，则将其加入队列，
开始进行广度优先搜索。在广度优先搜索的过程中，每个搜索到的 1 都会被重新标记为 0。
直到队列为空，搜索结束。
最终岛屿的数量就是我们进行广度优先搜索的次数。*/
#include<queue>
class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int nr = grid.size();
        if (!nr)
            return 0;
        int nc = grid[0].size();
        int num_islands = 0;
        for (int r = 0; r < nr; ++r)
        {
            for (int c = 0; c < nc; ++c)
            {
                if (grid[r][c] == '1')//进入依次广度优先搜索，就代表有一个独立的岛屿
                {
                    ++num_islands;
                    grid[r][c] = '0';
                    queue<pair<int, int>> neighbors;
                    neighbors.push({r, c});
                    while (!neighbors.empty())
                    {
                        auto rc = neighbors.front();
                        neighbors.pop();
                        int row = rc.first, col = rc.second;
                        if (row - 1 >= 0 && grid[row - 1][col] == '1')
                        {
                            neighbors.push({row - 1, col});
                            grid[row - 1][col] = '0';
                        }
                        if (row + 1 < nr && grid[row + 1][col] == '1')
                        {
                            neighbors.push({row + 1, col});
                            grid[row + 1][col] = '0';
                        }
                        if (col - 1 >= 0 && grid[row][col - 1] == '1')
                        {
                            neighbors.push({row, col - 1});
                            grid[row][col - 1] = '0';
                        }
                        if (col + 1 < nc && grid[row][col + 1] == '1')
                        {
                            neighbors.push({row, col + 1});
                            grid[row][col + 1] = '0';
                        }
                    }
                }
            }
        }

        return num_islands;
    }
};

int main()
{
    vector<vector<char>> vv{
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}};
    Solution plan;
    cout << 1111 << "\n";
    auto n = plan.numIslands(vv);
    cout << "n = " << n << "\n";
    return 0;
}