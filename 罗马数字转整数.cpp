#include<string>
#include<iostream>
using namespace std;
class Solution {
public:
    pair<int, string> valueSymbol[13] = {
        {1000, "M"},
        { 900,"CM" },
        { 500,"D" },
        { 400,"CD" },
        { 100,"C" },
        { 90,"XC" },
        { 50,"L" },
        { 40,"XL" },
        { 10,"X" },
        { 9,"IX" },
        { 5,"V" },
        { 4,"IV" },
        { 1,"I" }
    };
    int romanToInt(string s) {
        int num = 0;
        for (const auto&[value,symbol]:valueSymbol)
        {
            size_t pos = s.find(symbol);
            while (pos==0)//代表找到了，并且在开头
            {
                num += value;
                s.erase(pos, symbol.size());
                pos = s.find(symbol);//pos需要更新，不然死循环
            }
            if (s.size() == 0)
                break;
        }
        return num;
    }
};
int main()
{
    string roman = "III";
    //string roman = "LVIII";
    //string roman = "MCMXCIV";
    Solution plan;
    auto x = plan.romanToInt(roman);
    cout << "x = " << x << endl;
    return 0;
}