/**
给你一个大小为 4 的整数数组 a 和一个大小 至少为 4 的整数数组 b。 

 你需要从数组 b 中选择四个下标 i0, i1, i2, 和 i3，并满足 i0 < i1 < i2 < i3。你的得分将是 a[0] * b[i0] + 
a[1] * b[i1] + a[2] * b[i2] + a[3] * b[i3] 的值。 

 返回你能够获得的 最大 得分。 

 

 示例 1： 

 
 输入： a = [3,2,5,6], b = [2,-6,4,-5,-3,2,-7] 
 

 输出： 26 

 解释： 选择下标 0, 1, 2 和 5。得分为 3 * 2 + 2 * (-6) + 5 * 4 + 6 * 2 = 26。 

 示例 2： 

 
 输入： a = [-1,4,5,-2], b = [-5,-1,-3,-2,-4] 
 

 输出： -1 

 解释： 选择下标 0, 1, 3 和 4。得分为 (-1) * (-5) + 4 * (-1) + 5 * (-2) + (-2) * (-4) = -1。 


 

 提示： 

 
 a.length == 4 
 4 <= b.length <= 10⁵ 
 -10⁵ <= a[i], b[i] <= 10⁵ 
 

 Related Topics 数组 动态规划 👍 22 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution3290{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    long long maxScore(vector<int>& a, vector<int>& b) {
        int n = b.size();
        vector<vector<long long>> dp(5, vector<long long>(n + 1, LONG_LONG_MIN));
        for (int i = 0; i < n + 1; i++) {
            dp[0][i] = 0;
        }
        for (int i = 1; i <= 4; i++) {
            for (int j = i; j <= n; j++) {
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j - 1] + (long long)a[i - 1] * b[j - 1]);
            }
        }
        return dp[4][n];
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3290;
int main() {
    Solution solution;

    return 0;
}