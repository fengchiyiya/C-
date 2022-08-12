//给定一个n×n的二维矩阵matrix表示一个图像。请你将图像顺时针旋转90度。
//你必须在原地旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要使用另一个矩阵来旋转图像。
#include<vector>
#include<algorithm>
using namespace std;
//先按主对角线翻转，再翻转每一行。
//也可以按照水平翻转，再按主对角线翻转。
/*
旋转90°，matrix[row][col]<=>matrix[col][n-col-1],两者交换
水平翻转的话，matrix[row][col]<=>matrix[n-row-1][col],
再按主对角线翻转的话，matrix[n-row-1][col]=matrix[col][n-row-1]
即matrix[row][col]经过水平翻转和主对角线翻转后，变为了matrix[col][n-row-1]

先按主对角线翻转的话matrix[row][col]<=>matrix[col][row]
再翻转每一行，即matrix[col][row]<=>matrix[col][n-row-1]
即matrix[col][row]经过主对角线翻转和行翻转后，变味了matrix[col][n-row-1]
*/
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        //以对角线镜像交换，交换一个三角形即可
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            for (size_t j = i; j < matrix[0].size(); ++j)
            {
                int tmp=matrix[i][j];
                matrix[i][j]=matrix[j][i];
                matrix[j][i]=tmp;
            }
        }
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            reverse(matrix[i].begin(),matrix[i].end());
        }
    }
};