// 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。
// 找出那个只出现了一次的元素。
// 说明：
// 你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？
#include <vector>
using namespace std;
/*位运算
答案是使用位运算。对于这道题，可使用异或运算⊕。异或运算有以下三个性质。
任何数和 0 做异或运算，结果仍然是原来的数，即 a⊕0=a。
任何数和其自身做异或运算，结果是 0，即 a⊕a=0。
异或运算满足交换律和结合律，即 a⊕b⊕a=b⊕a⊕a=b⊕(a⊕a)=b⊕0=b。

^代表亦或运算符，
~按位取反运算符，~a，对变量a中全部二进制位取反。
*/
class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        int ret = 0;
        for (auto e : nums)
            ret ^= e;
        return ret;
    }
};