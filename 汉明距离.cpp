// 两个整数之间的 汉明距离 指的是这两个数字对应二进制位不同的位置的数目。
// 给你两个整数 x 和 y，计算并返回它们之间的汉明距离。

/*自己实现的，先将整数转化为二进制数，依次对比二进制数中不同的位数
也可以先将x、y异或，统计异或后的二进制数中1的个数*/
class Solution
{
public:
    int hammingDistance(int x, int y)
    {
        int cnt = 0;
        // x->二进制数
        while (x > 0 && y > 0)
        {
            int res_x = x % 2;
            x = x >> 1;
            int res_y = y % 2;
            y = y >> 1;
            if (res_x != res_y)
                ++cnt;
        }
        if (x || y)
        {
            int target = x > 0 ? x : y;
            while (target)
            {
                int res = target % 2;
                target = target >> 1;
                if (res)
                    ++cnt;
            }
        }
        return cnt;
    }
};
/*c++自带函数*/
class Solution
{
public:
    int hammingDistance(int x, int y)
    {
        // 统计二进制中有多少个1
        return __builtin_popcount(x ^ y);
    }
};