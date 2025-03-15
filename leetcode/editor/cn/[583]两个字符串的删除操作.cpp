/**
给定两个单词 word1 和
 word2 ，返回使得
 word1 和 
 word2 相同所需的最小步数。 

 每步 可以删除任意一个字符串中的一个字符。 

 

 示例 1： 

 
输入: word1 = "sea", word2 = "eat"
输出: 2
解释: 第一步将 "sea" 变为 "ea" ，第二步将 "eat "变为 "ea"
 

 示例 2: 

 
输入：word1 = "leetcode", word2 = "etco"
输出：4
 

 

 提示： 
 

 
 1 <= word1.length, word2.length <= 500 
 word1 和 word2 只包含小写英文字母 
 

 Related Topics 字符串 动态规划 👍 723 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution583{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<int> dp(word2.size() + 1, 0);
        dp[0] = 0;
        for (int i = 1; i <= word1.size(); i++) {
            vector<int> dpLast = dp;
            for (int j = 1; j <= word2.size(); j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[j] = dpLast[j - 1] + 1;
                } else {
                    dp[j] = max(dpLast[j], dp[j - 1]);
                }
            }
        }
        return word1.size() + word2.size() - 2 * dp[word2.size()];
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution583;
int main() {
    Solution solution;

    return 0;
}