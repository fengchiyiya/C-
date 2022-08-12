//地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。
//一个机器人从坐标 [0, 0] 的格子开始移动，它每次可以向左、右、上、下移动一格（不能移动到方格外），
//也不能进入行坐标和列坐标的数位之和大于k的格子。
//例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。
//但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？
#include<vector>
#include<iostream>
using namespace std;
/*DFS:DFS通过递归，先朝一个方向搜到底，再回溯至上个节点，沿另一个方向搜索
机器人仅可通过向下或者向右访问所有的可达解*/
//数位和的增量和公式：(x+1)%10!=0?s_x+1:s_x-8;s_x代表数位和
//注意每一层递归都保存了该层函数的参数，在内层函数中修改了全局变量的值，只有return，才能在外层循环中观察到变化
//class Solution {
//public:
//    int movingCount(int m, int n, int k) {
//        vector<vector<bool>> visited(m, vector<bool>(n, 0));
//        auto x = DFS(visited, m, n, 0, 0, k);
//        return x;
//    }
//    //虽然题目说机器人可以朝4个方向移动，但是可达解只需要向右向下就可达到。4个方向反而会将情况变复杂
//    int DFS(vector<vector<bool>>& visited, int m, int n, int x, int y, int k)
//    {
//        if (x >= m || y >= n || bitSum(x, y) > k || visited[x][y])
//            return 0;
//        visited[x][y] = true;
//        //这种方向问题，可以在return中递归调用
//        return 1 + DFS(visited, m, n, x + 1, y, k) + DFS(visited, m, n, x, y + 1, k);
//    }
//    int bitSum(int x, int y)
//    {
//        int s = 0;
//        s += x / 10;
//        s += x % 10;
//        s += y / 10;
//        s += y % 10;
//        return s;
//    }
//};
#include<queue>
/*BFS:广度优先算法，先遍历某一层，在递归往下。常常把某一层压入队列中，记录遍历结果*/
class Solution {
public:
    int movingCount(int m, int n, int k) {
        queue<pair<int, int>> layer;
        layer.push(pair<int, int>{ 0, 0 });
        vector<vector<bool>> visited{ (size_t)m,vector<bool>(n,0) };
        int cnt = 1;
        while (!layer.empty())
        {
            int size = layer.size();
            for (size_t i = 0; i < size; ++i)
            {
                pair<int, int> temp = layer.front();
                layer.pop();
                //插入条件：行列索引均未出界；满足数组和；之前未被访问过
                if (temp.first + 1 >= 0 && temp.first+1 < m && !visited[temp.first + 1][temp.second])
                {
                    if (bitSum(temp.first + 1, temp.second) <= k)
                    {
                        layer.push(pair<int, int>{temp.first + 1, temp.second});
                        visited[temp.first+1][temp.second] = true;
                        cnt++;
                    }
                }
                if(temp.second>= 0 && temp.second + 1 < n && !visited[temp.first][temp.second+1])
                {
                    if (bitSum(temp.first, temp.second + 1) <= k && visited[temp.first][temp.second + 1] == false)
                    {
                        layer.push(pair<int, int>{temp.first, temp.second + 1});
                        visited[temp.first][temp.second+1] = true;
                        cnt++;
                    }
                }

            }          
        }
        return cnt;

    }
    int bitSum(int x, int y)
    {
        int s = 0;
        s += x % 10;
        s += x / 10;
        s += y % 10;
        s += y / 10;
        return s;
    }
};
int main()
{
    Solution plan;
    auto n=plan.movingCount(1, 2,1);
    cout << "n = " << n << endl;
    return 0;
}