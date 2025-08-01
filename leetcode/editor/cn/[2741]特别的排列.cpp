/**
给你一个下标从 0 开始的整数数组 nums ，它包含 n 个 互不相同 的正整数。如果 nums 的一个排列满足以下条件，我们称它是一个特别的排列： 

 
 对于 0 <= i < n - 1 的下标 i ，要么 nums[i] % nums[i+1] == 0 ，要么 nums[i+1] % nums[i] ==
 0 。 
 

 请你返回特别排列的总数目，由于答案可能很大，请将它对 109 + 7 取余 后返回。 

 

 示例 1： 

 输入：nums = [2,3,6]
输出：2
解释：[3,6,2] 和 [2,6,3] 是 nums 两个特别的排列。
 

 示例 2： 

 输入：nums = [1,4,3]
输出：2
解释：[3,1,4] 和 [4,1,3] 是 nums 两个特别的排列。
 

 

 提示： 

 
 2 <= nums.length <= 14 
 1 <= nums[i] <= 10⁹ 
 

 Related Topics 位运算 数组 动态规划 状态压缩 👍 97 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2741{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int specialPerm(vector<int>& nums) {
        int n = nums.size();
        using ll = long long;
        const int MOD = 1e9 + 7;
        vector<vector<ll>> f(1 << n, vector<ll>(n, 0));
        for (int i = 0; i < n; i++) {
            f[1 << i][i] = 1;
        }
        for (int s = 1; s < 1 << n; s++) {
            for (int i = 0; i < n; i++) {
                // 假设上一个用的是i
                if (!(s >> i & 1)) continue;
                for (int j = 0; j < n; j++) {
                    if (!(s >> j & 1) && (nums[i] % nums[j] == 0 || nums[j] % nums[i] == 0)) {
                        int new_s = s | 1 << j;
                        f[new_s][j] += f[s][i];
                    }
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += f[(1 << n) - 1][i];
        }
        return ans % MOD;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2741;
int main() {
    Solution solution;
    vector<int> nums = {2, 3, 6};
    solution.specialPerm(nums);
    return 0;
}