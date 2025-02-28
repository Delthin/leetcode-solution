/**
给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。 

 

 示例 1： 

 
输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]
 

 示例 2： 

 
输入：s = "a"
输出：[["a"]]
 

 

 提示： 

 
 1 <= s.length <= 16 
 s 仅由小写英文字母组成 
 

 Related Topics 字符串 动态规划 回溯 👍 1949 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution131{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    vector<vector<string>> ret;
    vector<string> path;
    void backTrace(const string& s, int index, vector<vector<int>>& dp) {
        if (index >= s.size()) {
            ret.emplace_back(path);
            return;
        }
        for (int i = index + 1; i <= s.size(); i++) {
            if (dp[index][i]) {
                string str = s.substr(index, i - index);
                path.emplace_back(str);
                backTrace(s, i, dp);
                path.pop_back();
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        // 左开右闭
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i <= n; i++) {
            dp[i][i] = true;
        }
        for (int i = 0; i < n; i++) {
            dp[i][i + 1] = true;
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j <= n; j++) {
                dp[i][j] = dp[i][j] || (s.at(i) == s.at(j - 1) && dp[i + 1][j - 1]);
            }
        }
        backTrace(s, 0, dp);
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution131;
int main() {
    Solution solution;
    solution.partition("aab");
    return 0;
}