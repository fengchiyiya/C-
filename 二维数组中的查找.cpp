//在一个 n* m 的二维数组中，每一行都按照从左到右递增的顺序排序，
//每一列都按照从上到下递增的顺序排序。请完成一个高效的函数，
//输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
#include<vector>
#include<iostream>
using namespace std;
//class Solution {
//public:
//    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
//        if (matrix.empty()||matrix[0].empty())
//            return false;
//        int m = matrix[0].size();//列数
//        int n = matrix.size();//行数
//        int small = matrix[0][0];//smallest
//        int big = matrix[n-1][m-1];//bigest  注意列表
//        if (small > target||big<target)//最小值大于target，最大值小于target,返回false
//            return false;
//        for (size_t i = 0; i < n; ++i)
//        {
//            int begin = matrix[i][0];//起始
//            int end = matrix[i][m-1];
//            if (begin>target||end<target)//本行没有
//            {
//                continue;
//            }
//            //循环找
//            for (size_t j = 0; j < m; ++j)
//            {
//                if (matrix[i][j] == target)
//                    return true;
//            }
//        }
//        return false;
//    }
//};

class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if (matrix.empty()||matrix[0].empty())
            return false;
        int m = matrix[0].size();//列数
        int n = matrix.size();//行数
        int small = matrix[0][0];//smallest
        int big = matrix[n-1][m-1];//bigest  注意列表
        if (small > target||big<target)//最小值大于target，最大值小于target,返回false
            return false;
        for (size_t i = 0; i < n; ++i)
        {
            int begin = matrix[i][0];//起始
            int end = matrix[i][m-1];
            if (begin>target||end<target)//本行没有
            {
                continue;
            }
            //二分查找。速度还不如循环查找
            int left = 0, right = m - 1;
            int mid = (left + right) / 2;
            while (left<=right)//
            {
                if (matrix[i][mid] == target)//target=mid
                    return true;
                else if (matrix[i][mid] < target)//target处于(middle,end]之间
                    left = mid + 1;
                else if(matrix[i][mid]>target)//target处于[begin,middle)之间
                    right = mid - 1;
                mid = (left + right) / 2;
            }
        }
        return false;
    }
};
int main()
{
    vector<int> v1 = { 1, 4, 7, 11, 15 };
    vector<int> v2 = { 2, 5, 8, 12, 19 };
    vector<vector<int>> vv;
    vv.push_back(v1);
    vv.push_back(v2);
    Solution plan;
    bool flag=plan.findNumberIn2DArray(vv, 10);
    cout << flag << endl;
    return 0;
}