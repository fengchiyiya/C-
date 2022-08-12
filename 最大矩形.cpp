//给定一个仅包含0和1、大小为rowsxcols的二维二进制矩阵，找出只包含1的最大矩形，并返回其面积。
#include <vector>
using namespace std;
class Solution
{
public:
    int maximalRectangle(vector<vector<char>> &matrix)
    {
        int m = matrix.size();
        if (m == 0)
            return 0;
        int n = matrix[0].size();
        //统计i行到j的位置时，连续的1的个数（注意是连续的）
        vector<vector<int>> left(m, vector<int>(n, 0));
        for (size_t i = 0; i < m; ++i)
        {
            for (size_t j = 0; j < n; ++j)
            {
                if (matrix[i][j] == '1')
                    left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
            }
        }
        int res = 0;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (matrix[i][j] == '0')
                    continue;
                int width = left[i][j];
                int area=width;//本层的备用面积，这个是需要的。
                for (int k = i - 1; k >= 0; --k)
                {
                    width=min(left[k][j],width);
                    area=max(area,(i-k+1)*width);//不能直接使用res，如果没有进入循环的话，res就不会有正确的值了
                }
                res=max(res,area);
            }
        }
        return res;
    }
};