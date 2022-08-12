//罗马数字包含以下7种字符：I，V，X，L，C，D和M
//	I	V	X	L	C	D	M 	
//	1	5	10	50	100	500	1000
//通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，
//例如4不写做IIII，而是IV。数字1在数字5的左边，所表示的数等于大数5减小数1得到的数值4。
//同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
//I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
//X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
//C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
#include<string>
#include<vector>
using namespace std;
/*利用整数反转的知识，从最低位开始循环判断，类似硬编码*/
class Solution {
public:
    string intToRoman(int num) {
        vector<vector<string>> vec = {
            {"I","VI","V","XI"},
            {"X","LX","L","CX"},
            {"C","DC","D","MC"},
            {"M"}
        };
        string s;
        int i = 0;
        while (num>0)
        {
            int digit = num % 10;//各位上的数
            num = num / 10;
            if (digit == 9)
            {
                s += vec[i++][3];
                continue;
            }
            else
            {
                int res = digit / 5;//倍数
                int ret = digit % 5;//余数
                while (ret>0&&ret!=4)
                {
                    s += vec[i][0];
                    ret--;
                }
                if (ret == 4)//余数
                    s += vec[i][1];
                if (res)
                    s += vec[i][2];

            }  
            i++;
        }
        reverse(s.begin(), s.end());
        return s;
    }
};
/*贪心法：
我们用来确定罗马数字的规则是：对于罗马数字从左到右的每一位，选择尽可能大的符号值。
对于140，最大可以选择的符号值为C=100。接下来，
对于剩余的数字 40，最大可以选择的符号值为XL=40。因此140的对应的罗马数字为CXL。
*/
class Solution {
public:
    const pair<int,string> valueSymbols[13]={//符号对应的值都要先列好
        {1000,"M"},
        {900,"CM"},
        {500,"D"},
        {400,"CD"},
        {100,"C"},
        {90,"XC"},
        {50,"L"},
        {40,"XL"},
        {10,"X"},
        {9,"IX"},
        {5,"V"},
        {4,"IV"},
        {1,"I"}
    };
    string intToRoman(int num) {
        string roman;
        for (auto&[value,symbol]:valueSymbols)
        {
            while(num >= value)
            {
                roman.append(symbol);
                num -= value;
            }
            if (num == 0)
                break;
        }
        return roman;
    }
};