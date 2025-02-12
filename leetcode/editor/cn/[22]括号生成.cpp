/**
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。 

 

 示例 1： 

 
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]
 

 示例 2： 

 
输入：n = 1
输出：["()"]
 

 

 提示： 

 
 1 <= n <= 8 
 

 Related Topics 字符串 动态规划 回溯 👍 3764 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution22{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<vector<string>> dp;
        dp.push_back({{}});
        for (int i = 1; i <= n; i++) {
            unordered_set<string> n_of_parenthesis;
            int size = dp[i - 1].size();
            for (int j = 0; j < size; j++) {
                n_of_parenthesis.insert("(" + dp[i - 1][j] + ")");
            }
            for (int j = 1; j <= i - 1; j ++) {
                int size1 = dp[j].size();
                int size2 = dp[i - j].size();
                for (int k = 0; k < size1; k++) {
                    for (int l = 0; l < size2; l++) {
                        n_of_parenthesis.insert(dp[j][k] + dp[i - j][l]);
                    }
                }
            }
            vector<string> vec;
            copy(n_of_parenthesis.begin(), n_of_parenthesis.end(), back_inserter(vec));
            dp.push_back(vec);
        }
        return dp[n];
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution22;
int main() {
    Solution solution;
    solution.generateParenthesis(3);
    return 0;
}