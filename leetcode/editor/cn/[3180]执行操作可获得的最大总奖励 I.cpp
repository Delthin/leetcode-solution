/**
给你一个整数数组 rewardValues，长度为 n，代表奖励的值。 

 最初，你的总奖励 x 为 0，所有下标都是 未标记 的。你可以执行以下操作 任意次 ： 

 
 从区间 [0, n - 1] 中选择一个 未标记 的下标 i。 
 如果 rewardValues[i] 大于 你当前的总奖励 x，则将 rewardValues[i] 加到 x 上（即 x = x + 
rewardValues[i]），并 标记 下标 i。 
 

 以整数形式返回执行最优操作能够获得的 最大 总奖励。 

 

 示例 1： 

 
 输入：rewardValues = [1,1,3,3] 
 

 输出：4 

 解释： 

 依次标记下标 0 和 2，总奖励为 4，这是可获得的最大值。 

 示例 2： 

 
 输入：rewardValues = [1,6,4,3,2] 
 

 输出：11 

 解释： 

 依次标记下标 0、2 和 1。总奖励为 11，这是可获得的最大值。 

 

 提示： 

 
 1 <= rewardValues.length <= 2000 
 1 <= rewardValues[i] <= 2000 
 

 Related Topics 数组 动态规划 👍 70 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution3180{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        sort(rewardValues.begin(), rewardValues.end());
        int n = rewardValues.size();
        int m = rewardValues[n - 1] * 2;
        vector<bool> dp(m, false);
        dp[0] = true; // 初始状态，总奖励为0
        for (int i = 1; i <= n; i++) {
            for (int j = 2 * rewardValues[i - 1] - 1; j >= 0; j--) {
                if (j >= rewardValues[i - 1]) {
                    dp[j] = dp[j] || dp[j - rewardValues[i - 1]];
                }
            }
        }
        for (int i = m - 1; i >= 0; i--) {
            if (dp[i]) {
                return i;
            }
        }
        return 0;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3180;
int main() {
    Solution solution;

    return 0;
}