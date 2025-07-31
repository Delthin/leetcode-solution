/**
给你一个整数数组 nums 。nums 的每个元素是 1，2 或 3。在每次操作中，你可以删除 nums 中的一个元素。返回使 nums 成为 非递减 顺序所需
操作数的 最小值。 

 

 示例 1： 

 
输入：nums = [2,1,3,2,1]
输出：3
解释：
其中一个最优方案是删除 nums[0]，nums[2] 和 nums[3]。
 

 示例 2： 

 
输入：nums = [1,3,2,1,3,3]
输出：2
解释：
其中一个最优方案是删除 nums[1] 和 nums[2]。
 

 示例 3： 

 
输入：nums = [2,2,2,2,3,3]
输出：0
解释：
nums 已是非递减顺序的。
 

 

 提示： 

 
 1 <= nums.length <= 100 
 1 <= nums[i] <= 3 
 

 进阶：你可以使用 O(n) 时间复杂度以内的算法解决吗？ 

 Related Topics 数组 二分查找 动态规划 👍 37 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2826{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        // vector<vector<int>> dp(n + 1, vector<int>(3, 0));
        // for (int i = 1; i <= n; i++) {
        //     int x = nums[i - 1];
        //     for (int j = 1; j <= 3; j++) {
        //         if (j < x) {
        //             dp[i][j - 1] = dp[i - 1][j - 1];
        //         } else {
        //             dp[i][j - 1] = max(dp[i - 1][j - 1], dp[i - 1][x - 1] + 1);
        //         }
        //     }
        // }
        // return n - dp[n][2];
        vector<int> dp(3, 0);
        for (int x: nums) {
            dp[x - 1]++;
            dp[1] = max(dp[1],dp[0]);
            dp[2] = max(dp[2], dp[1]);
        }
        return n - dp[2];
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2826;
int main() {
    Solution solution;
    vector<int> nums = {2,1,3,2,1};
    cout << solution.minimumOperations(nums) << endl;
    return 0;
}