/**
给你两个正整数 n 和 limit 。 

 请你将 n 颗糖果分给 3 位小朋友，确保没有任何小朋友得到超过 limit 颗糖果，请你返回满足此条件下的 总方案数 。 

 

 示例 1： 

 
输入：n = 5, limit = 2
输出：3
解释：总共有 3 种方法分配 5 颗糖果，且每位小朋友的糖果数不超过 2 ：(1, 2, 2) ，(2, 1, 2) 和 (2, 2, 1) 。
 

 示例 2： 

 
输入：n = 3, limit = 3
输出：10
解释：总共有 10 种方法分配 3 颗糖果，且每位小朋友的糖果数不超过 3 ：(0, 0, 3) ，(0, 1, 2) ，(0, 2, 1) ，(0, 3, 0
) ，(1, 0, 2) ，(1, 1, 1) ，(1, 2, 0) ，(2, 0, 1) ，(2, 1, 0) 和 (3, 0, 0) 。
 

 

 提示： 

 
 1 <= n <= 10⁶ 
 1 <= limit <= 10⁶ 
 

 Related Topics 数学 组合数学 枚举 👍 36 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2929{
//leetcode submit region begin(Prohibit modification and deletion)
    class Solution {
        long long c2(long long n) {
            return n > 1 ? n * (n - 1) / 2 : 0;
        }

    public:
        long long distributeCandies(int n, int limit) {
            return c2(n + 2) - 3 * c2(n - limit + 1) + 3 * c2(n - 2 * limit) - c2(n - 3 * limit - 1);
        }
    };
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2929;
int main() {
    Solution solution;

    return 0;
}