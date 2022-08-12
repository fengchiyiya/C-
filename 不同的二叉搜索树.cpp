//给你一个整数n，求恰由n个节点组成且节点值从1到n互不相同的二叉搜索树有多少种？
//返回满足题意的二叉搜索树的种数。
/*动态规划
给定一个有序序列1⋯n，为了构建出一棵二叉搜索树，我们可以遍历每个数字i，将该数字作为树根，
将1⋯(i−1) 序列作为左子树，将(i+1)⋯n序列作为右子树。
接着我们可以按照同样的方式递归构建左子树和右子树。
定义两个函数G(n):长度为n的序列能构成的不同的二叉搜索树的个数
F(i,n):以i为根、序列长度为n的不同二叉搜索树个数(1<=i<=n)
可见G(n)是我们求解需要的函数
G(n)可以从F(i,n)得到，而F(i,n)又会递归依赖于G(n)
F(i,n)=G(i-1)*G(n-i)
G(n)=求和(G(i-1)*G(n-i))*/
#include <vector>
using namespace std;
class Solution
{
public:
    int numTrees(int n)
    {
        vector<int> G(n+1,0);
        //当序列长度为0和1时，只有一种情况
        G[0]=G[1]=1;
        for (int i = 2; i <= n; i++)//i代表序列长度
        {
            for (int j = 1; j <= i; j++)//j代表根节点的位置
            {
                //G[j-1]代表左子树的数量，G[i-j]代表右子树的数量
                G[i]+=G[j-1]*G[i-j];
            }
        }
        return G[n];
    }
};
/*数学方法
卡塔兰数*/
class Solution
{
public:
    int numTrees(int n)
    {
        long long C = 1;
        for (int i = 0; i < n; ++i)
        {
            C = C * 2 * (2 * i + 1) / (i + 2);
        }
        return (int)C;
    }
};