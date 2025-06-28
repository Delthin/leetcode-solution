/**
给定一个整数数组 arr 和一个整数 k ，通过重复 k 次来修改数组。 

 例如，如果 arr = [1, 2] ，
 k = 3 ，那么修改后的数组将是 [1, 2, 1, 2, 1, 2] 。 

 返回修改后的数组中的最大的子数组之和。注意，子数组长度可以是 0，在这种情况下它的总和也是 0。 

 由于 结果可能会很大，需要返回的
 10⁹ + 7 的 模 。 

 

 示例 1： 

 
输入：arr = [1,2], k = 3
输出：9
 

 示例 2： 

 
输入：arr = [1,-2,1], k = 5
输出：2
 

 示例 3： 

 
输入：arr = [-1,-2], k = 7
输出：0
 

 

 提示： 
 

 
 1 <= arr.length <= 10⁵ 
 1 <= k <= 10⁵ 
 -10⁴ <= arr[i] <= 10⁴ 
 

 Related Topics 数组 动态规划 👍 158 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1191{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        using ll = long long;
        const int MOD = 1'000'000'007;
        ll sum = accumulate(arr.begin(), arr.end(), 0);
        int n = arr.size();
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            dp[i] = max(dp[i - 1] + arr[i - 1], 0);
        }
        vector<int> dp2(min(2, k) * n + 1, 0);
        for (int i = 1; i <= min(k, 2) * n; i++) {
            dp2[i] = max(dp2[i - 1] + arr[(i - 1) % n], 0);
        }
        int maxDp1 = *max_element(dp.begin(), dp.end());
        int maxDp2 = *max_element(dp2.begin(), dp2.end());

        int ans = 0;
        if (sum > 0) {
            ans = max(sum * (k - 2) % MOD + maxDp2, sum * (k - 1) % MOD + maxDp1);
        } else {
            ans = maxDp2;
        }
        return ans % MOD;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1191;
int main() {
    Solution solution;

    return 0;
}