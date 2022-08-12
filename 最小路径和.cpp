//给定一个包含非负整数的mxn网格grid，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
//说明：每次只能向下或者向右移动一步。
#include <vector>
#include <algorithm>
using namespace std;
/*递归又超时*/
class Solution
{
public:
    void search(vector<vector<int>> &grid, int m, int n, int x, int y, int curSum, int &minSum)
    {
        if (x == m - 1 && y == n - 1)
        {
            curSum += grid[x][y];
            minSum = min(curSum, minSum);
        }
        if (x >= m || y >= n)
            return;
        curSum += grid[x][y];
        search(grid, m, n, x + 1, y, curSum, minSum);
        search(grid, m, n, x, y + 1, curSum, minSum);
        curSum -= grid[x][y];
    }
    int minPathSum(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        int minSum = INT_MAX;
        search(grid, m, n, 0, 0, 0, minSum);
        return minSum;
    }
};
/*动态规划
dp[i][j]代表到(i,j)点位置的最小路径和*/
class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n));
        for (size_t i = 0; i < m; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                if (i == 0 && j == 0)
                    dp[i][j] = grid[i][j];
                else if (i == 0)
                    dp[i][j] = grid[i][j] + dp[i][j - 1];
                else if (j == 0)
                    dp[i][j] = grid[i][j] + dp[i - 1][j];
                else
                    dp[i][j] = min(dp[i-1][j],dp[i][j-1])+grid[i][j];
            }
        }
        return dp[m-1][n-1];
    }
};
