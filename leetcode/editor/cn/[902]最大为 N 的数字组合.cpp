/**
给定一个按 非递减顺序 排列的数字数组
 digits 。你可以用任意次数 digits[i] 来写的数字。例如，如果
 digits = ['1','3','5']，我们可以写数字，如
 '13', '551', 和 '1351315'。 

 返回 可以生成的小于或等于给定整数 n 的正整数的个数 。 

 

 示例 1： 

 
输入：digits = ["1","3","5","7"], n = 100
输出：20
解释：
可写出的 20 个数字是：
1, 3, 5, 7, 11, 13, 15, 17, 31, 33, 35, 37, 51, 53, 55, 57, 71, 73, 75, 77.
 

 示例 2： 

 
输入：digits = ["1","4","9"], n = 1000000000
输出：29523
解释：
我们可以写 3 个一位数字，9 个两位数字，27 个三位数字，
81 个四位数字，243 个五位数字，729 个六位数字，
2187 个七位数字，6561 个八位数字和 19683 个九位数字。
总共，可以使用D中的数字写出 29523 个整数。 

 示例 3: 

 
输入：digits = ["7"], n = 8
输出：1
 

 

 提示： 
 

 
 1 <= digits.length <= 9 
 digits[i].length == 1 
 digits[i] 是从 '1' 到 '9' 的数 
 digits 中的所有值都 不同 
 digits 按 非递减顺序 排列 
 1 <= n <= 10⁹ 
 

 Related Topics 数组 数学 字符串 二分查找 动态规划 👍 295 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution902{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        string s = to_string(n);
        unordered_set<int> digit_set;
        for (const string& digit : digits) {
            digit_set.insert(stoi(digit));
        }
        vector<long long> memo(s.length(), -1);
        memo[0] = 0;
        function<long long(int, bool, bool)> dfs = [&](int pos, bool is_limit, bool is_leading_zero) {
            // 1. 递归终止条件
            if (pos == s.length()) {
                // 如果 is_leading_zero 仍为 true，说明整个数字是 0
                // 根据题目要求返回 1 (有效方案) 或 0 (无效方案)
                return is_leading_zero ? 0LL : 1LL;
            }

            // 2. 记忆化：只有在不受限的情况下才能复用结果
            if (!is_limit && !is_leading_zero && memo[pos]!=-1) {
                return memo[pos];
            }

            long long ans = 0;
            // 3. 确定当前位的上限
            int upper_bound = is_limit ? (s[pos] - '0') : 9;

            // 4. 遍历当前位所有可能的数字 d
            for (int d = 0; d <= upper_bound; d++) {
                if (is_leading_zero && d == 0) {
                } else if (digit_set.count(d) == 0) {
                    continue;
                }
                // 5. 递归到下一位
                ans += dfs(
                    pos + 1,
                    is_limit && (d == upper_bound),
                    is_leading_zero && (d == 0)
                );
            }

            // 6. 存入 memo
            if (!is_limit && !is_leading_zero) {
                memo[pos] = ans;
            }

            return ans;
        };
        return dfs(0, true, true);
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution902;
int main() {
    Solution solution;
    vector<string> digits = {"1","3","5","7"};
    int n = 100;
    cout << solution.atMostNGivenDigitSet(digits, n) << endl;
    return 0;
}