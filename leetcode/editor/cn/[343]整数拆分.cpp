/**
给定一个正整数 n ，将其拆分为 k 个 正整数 的和（ k >= 2 ），并使这些整数的乘积最大化。 

 返回 你可以获得的最大乘积 。 

 

 示例 1: 

 
输入: n = 2
输出: 1
解释: 2 = 1 + 1, 1 × 1 = 1。 

 示例 2: 

 
输入: n = 10
输出: 36
解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。 

 

 提示: 

 
 2 <= n <= 58 
 

 Related Topics 数学 动态规划 👍 1449 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution343{
//leetcode submit region begin(Prohibit modification and deletion)
    class Solution {
    public:
        int integerBreak(int n) {
            vector<int> dp(n + 1);
            dp[2] = 1;
            for (int i = 3; i <= n ; i++) {
                for (int j = 1; j <= i / 2; j++) {
                    dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));
                }
            }
            return dp[n];
        }
    };
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution343;
int main() {
    Solution solution;

    return 0;
}