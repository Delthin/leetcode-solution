/**
给你两个数字字符串 num1 和 num2 ，以及两个整数 max_sum 和 min_sum 。如果一个整数 x 满足以下条件，我们称它是一个好整数： 

 
 num1 <= x <= num2 
 min_sum <= digit_sum(x) <= max_sum. 
 

 请你返回好整数的数目。答案可能很大，请返回答案对 10⁹ + 7 取余后的结果。 

 注意，digit_sum(x) 表示 x 各位数字之和。 

 

 示例 1： 

 
输入：num1 = "1", num2 = "12", min_num = 1, max_num = 8
输出：11
解释：总共有 11 个整数的数位和在 1 到 8 之间，分别是 1,2,3,4,5,6,7,8,10,11 和 12 。所以我们返回 11 。
 

 示例 2： 

 
输入：num1 = "1", num2 = "5", min_num = 1, max_num = 5
输出：5
解释：数位和在 1 到 5 之间的 5 个整数分别为 1,2,3,4 和 5 。所以我们返回 5 。
 

 

 提示： 

 
 1 <= num1 <= num2 <= 10²² 
 1 <= min_sum <= max_sum <= 400 
 

 Related Topics 数学 字符串 动态规划 👍 111 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2719{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        const int MOD = 1e9 + 7;
        auto solve = [&](const string& s) {
            vector<vector<long long>> memo(s.length(), vector<long long>(max_sum + 1, -1));
            function<long long(int, int, bool)> dfs = [&](int pos, int sum, bool is_limit) {
                if (sum > max_sum) return 0LL;
                if (pos == s.length()) {
                    return sum >= min_sum ? 1LL : 0LL;
                }

                // 2. 记忆化：只有在不受限的情况下才能复用结果
                if (!is_limit && memo[pos][sum] != -1) {
                    return memo[pos][sum];
                }

                long long ans = 0;
                // 3. 确定当前位的上限
                int upper_bound = is_limit ? (s[pos] - '0') : 9;

                // 4. 遍历当前位所有可能的数字 d
                for (int d = 0; d <= upper_bound; d++) {
                    // 5. 递归到下一位
                    ans += dfs(
                        pos + 1,
                        sum + d,
                        is_limit && (d == upper_bound)
                    );
                    ans %= MOD;
                }

                // 6. 存入 memo
                ans %= MOD;
                if (!is_limit) {
                    memo[pos][sum] = ans;
                }

                return ans;
            };
            return dfs(0, 0, true);
        };
        int sum = 0;
        for (int i = 0; i < num1.length(); i++) {
            sum += num1[i] - '0';
        }
        int plus = sum >= min_sum && sum <= max_sum ? 1 : 0;
        return (solve(num2) - solve(num1) + plus + MOD) % MOD;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2719;
int main() {
    Solution solution;

    return 0;
}