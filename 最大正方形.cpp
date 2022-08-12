// 在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。

#include <vector>
#include <math.h>
using namespace std;
/*这道题和之前最大的矩形类似，应该都是动态规划
动态规划记录当前行连续的1的值*/
class Solution
{
public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (j == 0 && matrix[i][j] == '1') //赋初值
                    dp[i][j] = 1;
                else if (matrix[i][j] == '1')
                    dp[i][j] = dp[i][j - 1] + 1;
            }
        }
        int maxArea = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (dp[i][j] > 0)
                {
                    int currArea = 1;      //当前的正方形面积
                    int minVal = dp[i][j]; //每一行的最小值
                    for (int k = i + 1; k < m && dp[k][j] > 0; ++k)
                    {
                        minVal = min(minVal, dp[k][j]);
                        if (minVal >= k - i + 1)
                            currArea = pow((k - i + 1), 2);
                    }
                    maxArea = max(maxArea, currArea);
                }
            }
        }
        return maxArea;
    }
};
/*虽然也是动态规划，但是本题的动态规划有简单版本
dp(i,j)=min(dp(i-1,j),dp(i-1,j-1),dp(i,j-1))+1
*/
class Solution
{
public:
    int maximalSquare(vector<vector<char>> &matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        int maxSide = 0; //最大边长
        for (int i = 0; i < m; ++i)
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    if (matrix[i][j] == '1')
                    {
                        if (j == 0 || i == 0) // 赋初值
                            dp[i][j] = 1;
                        else // 这个递推公式很巧妙
                            dp[i][j] = min({dp[i][j - 1], dp[i - 1][j - 1], dp[i - 1][j]}) + 1;
                    }
                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        return maxSide * maxSide;
    }
};
