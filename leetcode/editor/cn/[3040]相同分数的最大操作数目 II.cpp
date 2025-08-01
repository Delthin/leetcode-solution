/**
给你一个整数数组 nums ，如果 nums 至少 包含 2 个元素，你可以执行以下操作中的 任意 一个： 

 
 选择 nums 中最前面两个元素并且删除它们。 
 选择 nums 中最后两个元素并且删除它们。 
 选择 nums 中第一个和最后一个元素并且删除它们。 
 

 一次操作的 分数 是被删除元素的和。 

 在确保 所有操作分数相同 的前提下，请你求出 最多 能进行多少次操作。 

 请你返回按照上述要求 最多 可以进行的操作次数。 

 

 示例 1： 

 
输入：nums = [3,2,1,2,3,4]
输出：3
解释：我们执行以下操作：
- 删除前两个元素，分数为 3 + 2 = 5 ，nums = [1,2,3,4] 。
- 删除第一个元素和最后一个元素，分数为 1 + 4 = 5 ，nums = [2,3] 。
- 删除第一个元素和最后一个元素，分数为 2 + 3 = 5 ，nums = [] 。
由于 nums 为空，我们无法继续进行任何操作。
 

 示例 2： 

 
输入：nums = [3,2,6,1,4]
输出：2
解释：我们执行以下操作：
- 删除前两个元素，分数为 3 + 2 = 5 ，nums = [6,1,4] 。
- 删除最后两个元素，分数为 1 + 4 = 5 ，nums = [6] 。
至多进行 2 次操作。
 

 

 提示： 

 
 2 <= nums.length <= 2000 
 1 <= nums[i] <= 1000 
 

 Related Topics 记忆化搜索 数组 动态规划 👍 55 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution3040{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maxOperations(vector<int>& nums) {
        int n = nums.size();
        auto do_dp = [&](int l, int r, int target) {
            vector<vector<int>> dp(n + 1, vector<int>(n + 1));
            for (int i = r - 1; i >= l; --i) {
                for (int j = i + 1; j <= r; j++) {
                    if (nums[i] + nums[i + 1] == target) {
                        dp[i][j] = max(dp[i][j], dp[i + 2][j] + 1);
                    }
                    if (i == 0 && j == 1) continue;
                    if (nums[j] + nums[j - 1] == target) {
                        dp[i][j] = max(dp[i][j], dp[i][j - 2] + 1);
                    }
                    if (nums[i] + nums[j] == target) {
                        dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + 1);
                    }
                }
            }
            return dp[l][r];
        };
        int res1 = do_dp(2, n - 1, nums[0] + nums[1]);
        int res2 = n > 2 ? do_dp(0, n - 3, nums[n - 1] + nums[n - 2]) : 0;
        int res3 = do_dp(1, n - 2, nums[0] + nums[n - 1]);
        return max({res1, res2, res3}) + 1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3040;
int main() {
    Solution solution;

    return 0;
}