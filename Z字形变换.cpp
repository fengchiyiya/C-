//将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。
//比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：
//P   A   H   N
//A P L S I I G
//Y   I   R
//之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："PAHNAPLSIIGYIR"。
#include<string>
#include<vector>
#include<iostream>
using namespace std;
/*利用二维矩阵模拟
Z字形变换的周期为2r-2，r为行数，列数可以取周期数+1*Z字的列数，循环时利用Z字形的列数周期赋值，取余操作。
可以优化矩阵空间
注意到每次往矩阵的某一行添加字符时，都会添加到该行上一个字符的右侧，
且最后组成答案时只会用到每行的非空字符。因此我们可以将矩阵的每行初始化为一个空列表，
每次向某一行添加字符时，添加到该行的列表末尾即可。
*/
class Solution {
public:
    void fillVec(string s, vector<vector<char>>& Z)
    {
        int rows = Z.size();
        int cols = Z[0].size();
        int zcol = rows - 1;
        int id = 0;
        for (int i = 0; i < cols; ++i)//列
        {
            for (int j = 0; j < rows; ++j)//行
            {
                int res = i % zcol;
                if (id < s.size())
                {
                    if (res == 0)
                    {
                        Z[j][i] = s[id++];
                    }
                    else
                    {
                        Z[rows - 1 - res][i] = s[id++];
                        break;
                    }
                }
                else
                    return;//字符串遍历结束，提前退出
            }
        }

    }
    string convert(string s, int numRows) {
        int size = s.size();
        if (numRows < 2)//一行的话，直接返回
            return s;
        int elems = (numRows - 2) * 2 + 2;
        int res = size % elems;//余数
        int Cols1 = res>0?1:0;
        int Cols2 = res - numRows > 0 ? res - numRows : 0;
        int cols = (size / elems)*(numRows-1) + Cols1 + Cols2;
        vector<vector<char>> Z(numRows,vector<char>(cols,' '));//默认全为空格
        fillVec(s, Z);
        string temp;
        for (int i=0;i<Z.size();++i)
        {
            for (auto& c:Z[i])
            {
                if (c != ' ')
                {
                    temp.append(string{ c });
                }
            }

        }
        return temp;
    }
};
int main()
{
    string s = "PAYPALISHIRING";
    int numRows = 3;
    Solution plan;
    auto x= plan.convert(s, numRows);
    cout << "x =" << x << endl;
    return 0;
}