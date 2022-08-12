//一个机器人位于一个mxn网格的左上角（起始点在下图中标记为 “Start” ）。
//机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
//问总共有多少条不同的路径？
#include <vector>
#include <iostream>
using namespace std;
/*递归超时了，动态规划能处理这个吗？*/
// class Solution
// {
// public:
//     int search(int m, int n, int x, int y)
//     {
//         if (x == m && y == n)
//         {
//             return 1;
//         }
//         if (x > m || y > n)
//             return 0;
//         return search(m, n, x + 1, y) + search(m, n, x, y + 1);
//     }
//     int uniquePaths(int m, int n)
//     {
//         auto cnt = search(m, n, 1, 1);
//         return cnt;
//     }
// };
/*动态规划
dp[i][j]表示到(i,j)点的路径数量
dp[i][j]=dp[i-1][j]+dp[i][j-1]*/
class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        vector<vector<int>>dp(m+1,vector<int>(n+1,0));
        dp[1][1]=1;
        for (size_t i = 1; i < m+1; ++i)
        {
            for (size_t j = 1; j < n+1; ++j)
            {
                cout<<"i = "<<i<<" , j = "<<j<<endl;
                if(i==1&&j==1)
                    dp[i][j]=1;
                else if(i==1)
                    dp[i][j]=dp[i][j-1];
                else if(j==1)
                    dp[i][j]=dp[i-1][j];
                else 
                    dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }  
        }
        return dp[m][n];
    }
};
int main()
{
    int m = 23, n = 12;
    Solution plan;
    auto cnt = plan.uniquePaths(m, n);
    cout << "cnt = " << cnt << endl;
    return 0;
}