// 你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
// 在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，
// 表示如果要学习课程 ai 则 必须 先学习课程  bi 。
// 例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
// 请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。
#include <vector>
using namespace std;
/* 拓扑排序问题 有向无环图
给定一个包含n个节点的有向图G，我们给出它的节点编号的一种排列，如果满足：
对于图 GG 中的任意一条有向边 (u, v)，u 在排列中都出现在 v 的前面。就是拓扑排序
从入度思考（从前往后排序），入度为0的节点，在拓扑排序中一定排在前面，删除对应的边，继续寻找入度为0的节点
从出度思考（从后往前排序），出度为0的节点，在拓扑排序中一定排在后面，删除对应的边，继续寻找出度为0的节点
*/

/*
深度优先搜索
将节点分为3个状态：
0 代表没访问过
1 代表处于在本次递归访问过程中，访问过
2 本次递归即将结束，节点被访问过
主要是判断此次拓扑排序没有形成环
*/
class Solution
{
private:
    bool vaild = true;
    vector<int> visited;
    vector<vector<int>> edges;

public:
    void dfs(int u)
    {
        visited[u] = 1;
        for (auto &v : edges[u])
        {
            if (visited[v] == 0) // 没有访问过
            {
                dfs(v);
                if (!vaild)
                    return;
            }
            else if (visited[v] == 1) // 本次迭代中，第二次访问，形成了环
            {
                vaild = false;
                return;
            }
        }
        visited[u] = 2; // 迭代时没有二次访问过
    }
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        visited.resize(numCourses);
        edges.resize(numCourses);
        for (const auto &info : prerequisites)
        {
            edges[info[0]].push_back(info[1]); //这个插入顺序可以颠倒，主要是检查有没有环
        }
        for (size_t i = 0; i < numCourses && vaild; ++i) //注意vaild的判断要加上
        {
            if (!visited[i])
                dfs(i);
        }
        return vaild;
    }
};
/*广度优先搜索
即从出度思考*/
#include <queue>
class Solution
{
private:
    vector<vector<int>> edges;
    vector<int> inedges; //入度
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        //resize的注意点，当n>容器现在的size时，resize(n)只会对多的内存地址初始化 即大于size的部分
        edges.resize(numCourses);
        inedges.resize(numCourses);
        for (const auto &info : prerequisites)
        {
            edges[info[1]].push_back(info[0]); // 边从 info[1] 指向info[0]
            ++inedges[info[0]];
        }
        queue<int> q;
        for (int i = 0; i < numCourses; ++i)
        {
            if (inedges[i] == 0) // 入度为0
                q.push(i); // 压入入度点，不是入度的边数
        }
        int visited = 0;
        //如果存在环， inedges[v]会比平常大1，循环不会恰好结束
        while (!q.empty())
        {
            ++visited;
            auto u = q.front();
            q.pop();
            for (auto &v : edges[u])
            {
                --inedges[v]; // v的入度减1
                if (inedges[v] == 0)
                    q.push(v);
            }
        }
        return visited==numCourses;
    }
};
