/**
如果一个正整数每一个数位都是 互不相同 的，我们称它是 特殊整数 。 

 给你一个 正 整数 n ，请你返回区间 [1, n] 之间特殊整数的数目。 

 

 示例 1： 

 
输入：n = 20
输出：19
解释：1 到 20 之间所有整数除了 11 以外都是特殊整数。所以总共有 19 个特殊整数。
 

 示例 2： 

 
输入：n = 5
输出：5
解释：1 到 5 所有整数都是特殊整数。
 

 示例 3： 

 
输入：n = 135
输出：110
解释：从 1 到 135 总共有 110 个整数是特殊整数。
不特殊的部分数字为：22 ，114 和 131 。 

 

 提示： 

 
 1 <= n <= 2 * 10⁹ 
 

 Related Topics 数学 动态规划 👍 141 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2376{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int countSpecialNumbers(int n) {
        string s = to_string(n);
        vector<vector<long long>> memo(s.length(), vector<long long>(1 << 10, -1));
        // 表示走到pos为止，已经使用了mask表示的数字，里面含有的特殊整数
        function<long long(int, int, bool, bool)> dfs = [&](int pos, int mask, bool is_limit, bool is_leading_zero) {
            // 1. 递归终止条件
            if (pos == s.length()) {
                return is_leading_zero ? 0LL : 1LL;
            }

            // 2. 记忆化：只有在不受限的情况下才能复用结果
            if (!is_limit && !is_leading_zero && memo[pos][mask] != -1) {
                return memo[pos][mask];
            }

            long long ans = 0;
            // 3. 确定当前位的上限
            int upper_bound = is_limit ? (s[pos] - '0') : 9;

            // 4. 遍历当前位所有可能的数字 d
            for (int d = 0; d <= upper_bound; d++) {
                // --- 剪枝：根据题目条件判断数字 d 是否合法 ---
                // if (is_leading_zero && d == 0) { ... }
                // else if (/* d 不满足和上一位的关系 */) { continue; }
                if (!is_leading_zero && mask >> d & 1) {
                    continue;
                }
                // 5. 递归到下一位
                ans += dfs(
                    pos + 1,
                    (is_leading_zero && d == 0) ? mask : (mask | (1 << d)),
                    is_limit && (d == upper_bound),
                    is_leading_zero && (d == 0)
                );
            }

            // 6. 存入 memo
            if (!is_limit && !is_leading_zero) {
                memo[pos][mask] = ans;
            }

            return ans;
        };
        return dfs(0, 0, true, true);
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2376;
int main() {
    Solution solution;

    return 0;
}