/**
给你两个字符串 s 和 t ，统计并返回在 s 的 子序列 中 t 出现的个数，结果需要对 10⁹ + 7 取模。 

 

 示例 1： 

 
输入：s = "rabbbit", t = "rabbit"
输出：3
解释：
如下所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
rabbbit
rabbbit
rabbbit 

 示例 2： 

 
输入：s = "babgbag", t = "bag"
输出：5
解释：
如下所示, 有 5 种可以从 s 中得到 "bag" 的方案。 
babgbag
babgbag
babgbag
babgbag
babgbag
 

 

 提示： 

 
 1 <= s.length, t.length <= 1000 
 s 和 t 由英文字母组成 
 

 Related Topics 字符串 动态规划 👍 1327 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution115{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int numDistinct(string s, string t) {
        vector<int> dp(t.size() + 1, 0);
        dp[0] = 1;
        static constexpr int MODNUM = 1000000007;
        for (int i = 1;i <= s.size(); i++) {
            vector<int> dpLast = dp;
            for (int j = 1;j <= t.size(); j++) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] = (dpLast[j - 1] + dpLast[j]) % MODNUM;
                } else {
                    dp[j] = dpLast[j];
                }
            }
        }
        return dp[t.size()];
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution115;
int main() {
    Solution solution;

    return 0;
}