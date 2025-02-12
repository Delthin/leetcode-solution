/**
给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。 

 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。 

 你可以认为每种硬币的数量是无限的。 

 

 示例 1： 

 
输入：coins = [1, 2, 5], amount = 11
输出：3 
解释：11 = 5 + 5 + 1 

 示例 2： 

 
输入：coins = [2], amount = 3
输出：-1 

 示例 3： 

 
输入：coins = [1], amount = 0
输出：0
 

 

 提示： 

 
 1 <= coins.length <= 12 
 1 <= coins[i] <= 2³¹ - 1 
 0 <= amount <= 10⁴ 
 

 Related Topics 广度优先搜索 数组 动态规划 👍 2969 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution322{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, numeric_limits<int>::max());
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for(int coin: coins) {
                if (i < coin || dp[i - coin] == numeric_limits<int>::max()) {
                    continue;
                }
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
        return dp[amount] == numeric_limits<int>::max() ? -1 : dp[amount];
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution322;
int main() {
    Solution solution;

    return 0;
}