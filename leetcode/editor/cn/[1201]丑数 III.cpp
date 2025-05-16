/**
丑数是可以被 a 或 b 或 c 整除的 正整数 。 

 给你四个整数：n 、a 、b 、c ，请你设计一个算法来找出第 n 个丑数。 

 

 示例 1： 

 
输入：n = 3, a = 2, b = 3, c = 5
输出：4
解释：丑数序列为 2, 3, 4, 5, 6, 8, 9, 10... 其中第 3 个是 4。 

 示例 2： 

 
输入：n = 4, a = 2, b = 3, c = 4
输出：6
解释：丑数序列为 2, 3, 4, 6, 8, 9, 10, 12... 其中第 4 个是 6。
 

 示例 3： 

 
输入：n = 5, a = 2, b = 11, c = 13
输出：10
解释：丑数序列为 2, 4, 6, 8, 10, 11, 12, 13... 其中第 5 个是 10。
 

 

 提示： 

 
 1 <= n, a, b, c <= 10⁹ 
 1 <= a * b * c <= 10¹⁸ 
 本题结果在 [1, 2 * 10⁹] 的范围内 
 

 Related Topics 数学 二分查找 组合数学 数论 👍 164 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1201{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    using LL = long long;
    LL MCM(LL a,LL b){

        LL Multi = a * b;

        while(b > 0){
            LL tmp = a % b;
            a = b;
            b = tmp;
        }

        return Multi/a;
    }

public:
    int nthUglyNumber(int n, int a, int b, int c) {
        auto check = [&] (LL x) -> bool {
            LL cnt = 0;
            cnt += x / a + x / b + x / c;
            cnt -= x / MCM(a, b) + x / MCM(b, c) + x / MCM(a, c);
            cnt += x / MCM(MCM(a,b), c);
            return cnt < n;
        };
        int l = min(a, min(b, c)), r = min(l * n, 2'000'000'001);
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            (check(mid) ? l : r) = mid;
        }
        return r;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1201;
int main() {
    Solution solution;

    return 0;
}