#include <vector>
#include <string>
using namespace std;
// 给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，
// 其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。
// 另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，
// 请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。
// 返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。
// 如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。

/*这题有点像找相交的区间，事先算好两两之间的差，等待查询,但是具体流程没有很好的思路*/
/*广度优先搜索
我们可以将整个问题建模成一张图：给定图中的一些点，以及某些边的权值，试对任意两点求出其路径长。
因此，我们首先需要遍历equations数组，找出其中所有不同的字符串，并通过哈希表将每个不同的字符串映射成整数。
构建完图之后，任何一个查询，就可以从起点出发，通过广度优先搜索的方式，不断更新起点与当前点之间的路径长度，直到搜索到终点为止。
注意细节，代码有点长
*/
#include <unordered_map>
#include <iostream>
#include <queue>
class Solution
{
public:
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        int idx = 0;
        unordered_map<string, int> vars; // 存储节点值和节点编号
        int n = equations.size();
        for (size_t i = 0; i < n; i++)
        {
            // 第一次时，记录节点值和编号
            if (vars.find(equations[i][0]) == vars.end())
                vars[equations[i][0]] = idx++;
            if (vars.find(equations[i][1]) == vars.end())
                vars[equations[i][1]] = idx++;
        }
        // --idx; 不能--，因为这里的idx代表节点个数,索引比尺寸少1
        cout << "idx = " << idx << endl;
        vector<vector<pair<int, double>>> edges(idx); //存储节点编号和权值,注意使用了pair；注意是存储的是到另外的节点个数
        for (size_t i = 0; i < n; i++)
        {
            int va = vars[equations[i][0]], vb = vars[equations[i][1]];
            cout << "va = " << va << " , vb = " << vb << endl;
            edges[va].push_back(make_pair(vb, values[i]));
            edges[vb].push_back(make_pair(va, 1.0 / values[i]));
        }
        vector<double> ans;
        // 开始查询
        for (const auto &v : queries)
        {
            double result = -1.0; // 这个result是有必要的，因为可能没有进入到下面的if判断
            // 先判断节点是否都存在，上次错误就是这里误写成了循环
            if (vars.find(v[0]) != vars.end() && vars.find(v[1]) != vars.end())
            {
                int ia = vars[v[0]], ib = vars[v[1]];
                if (ia == ib) // a/a=1.0
                    result = 1.0;
                else
                {
                    queue<int> points; //存储节点编号
                    points.push(ia);
                    vector<double> vals(idx, -1.0); // 存储的是double类型的值
                    vals[ia] = 1.0;                 // 初始值赋值为1.0;
                    // 开始广度优先搜索
                    while (!points.empty() && vals[ib] < 0)
                    {
                        auto x = points.front();
                        points.pop();
                        cout << "x = " << x << endl;
                        for (auto [y, val] : edges[x])
                        {
                            if (vals[y] < 0) //节点没有访问过
                            {
                                vals[y] = val * vals[x];
                                points.push(y);
                            }
                        }
                    }
                    result = vals[ib];
                }
            }
            ans.push_back(result);
        }
        return ans;
    }
};

/*带权并查集
有点难，看下面的视频解析
https://leetcode.cn/problems/evaluate-division/solution/399-chu-fa-qiu-zhi-nan-du-zhong-deng-286-w45d/
    1.构建有向图
    2.统一变量与路径压缩
有一个问题，节点在更新时，发现父节点不止一个，这怎么办呢？
    发现最后会被压缩指向一个共同的节点。
压缩节点时，注意父节点更新必须在权值更新后面，不然会漏父节点
*/
class Solution
{
public:
    // 在查询时，实时压缩路径，将路径指向根节点
    int findf(vector<int> &f, vector<double> &w, int x)
    {
        if (f[x] != x) // 节点的父节点！=本身
        {
            int father = findf(f, w, f[x]);
            // 注意更新父节点必须在更新权值后面，因为权值需要利用之前的父节点
            w[x] *= w[f[x]];
            f[x] = father; // 更新父节点
        }
        return f[x];
    }
    // 更新两个根节点之间的距离，构建有向图。类似四边形，直到3边，求第四条边
    void merge(vector<int> &f, vector<double> &w, int x, int y, double val)
    {
        int fx = findf(f, w, x);
        int fy = findf(f, w, y);
        f[fx] = fy;
        w[fx] = val * w[y] / w[x];
    }
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        int n = equations.size();
        unordered_map<string, int> vars;
        size_t idx = 0;
        for (size_t i = 0; i < n; i++)
        {
            // 注意，不存在时等于尾迭代器！！不要搞错
            if (vars.find(equations[i][0]) == vars.end())
                vars[equations[i][0]] = idx++;
            if (vars.find(equations[i][1]) == vars.end())
                vars[equations[i][1]] = idx++;
        }
        vector<int> f(idx); // idx代表节点个数
        vector<double> w(idx, 1.0);
        for (size_t i = 0; i < idx; i++)
        {
            f[i] = i;
        }
        // 开始构建有向图
        for (size_t i = 0; i < n; i++)
        {
            int ia = vars[equations[i][0]], ib = vars[equations[i][1]];
            merge(f, w, ia, ib, values[i]);
        }
        vector<double> ans;
        for (const auto &q : queries)
        {
            double result = -1.0;
            if (vars.find(q[0]) != vars.end() && vars.find(q[1]) != vars.end())
            {
                int ia = vars[q[0]], ib = vars[q[1]];
                int fa = findf(f, w, ia), fb = findf(f, w, ib);
                if (fa == fb)
                    result = w[ia] / w[ib];
            }
            ans.push_back(result);
        }
        return ans;
    }
};
