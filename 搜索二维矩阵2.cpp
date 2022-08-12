// 编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：
// 每行的元素从左到右升序排列。
// 每列的元素从上到下升序排列。
#include <vector>
using namespace std;
/*每行使用二分法容易想到，但是这个Z字形查找，没有想到
从右上角(0,n-1)开始搜索，以matrix的左下角为右下角，(x,y)为右上角的矩阵进行搜索
如果matrix[x,y]=target,说明搜索完成
如果matrix[x,y]>target,由于每一列的元素都是升序排列，那么在当前的搜索矩阵中，所有第y列的元素都是大于target的，即y-1
如果matrix[x,y]<target,由于每一行的元素都是升序排列，那么在当前的搜索矩阵中，所有第x行的元素都是小于target的，即x+1
*/
class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int m = matrix.size(), n = matrix[0].size();
        int x = 0, y = n - 1;
        while (x < m && y >= 0)
        {
            if (matrix[x][y] == target)
                return true;
            if (matrix[x][y] > target) // 因为从右上角开始搜寻，所以当前值比target大，代表当前列不符合
                --y;
            else // 同理  (这里注意不能再使用if,不然--y后，可能已经越界了)
                ++x;
        }
        return false;
    }
};
class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        int m = matrix.size(), n = matrix[0].size();
        int x = 0, y = n - 1;
        while (x < m && y >= 0)
        {
            if (matrix[x][y] == target)
            {
                return true;
            }
            if (matrix[x][y] > target)
            {
                --y;
            }
            else
            {
                ++x;
            }
        }
        return false;
    }
};