/**
给定一个非空的字符串
 s ，检查是否可以通过由它的一个子串重复多次构成。 

 

 示例 1: 

 
输入: s = "abab"
输出: true
解释: 可由子串 "ab" 重复两次构成。
 

 示例 2: 

 
输入: s = "aba"
输出: false
 

 示例 3: 

 
输入: s = "abcabcabcabc"
输出: true
解释: 可由子串 "abc" 重复四次构成。 (或子串 "abcabc" 重复两次构成。)
 

 

 提示： 

 
 

 
 1 <= s.length <= 10⁴ 
 s 由小写英文字母组成 
 

 Related Topics 字符串 字符串匹配 👍 1257 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution459{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int len = s.size();
        vector<int> next(len);
        for (int i = 1, j = 0; i < len; i++) {
            while (j > 0 && s[j] != s[i]) j = next[j - 1];
            if (s[i] == s[j]) {
                j++;
            }
            next[i] = j;
        }
        if (next[len - 1] != 0 && len % (len - next[len - 1]) == 0) {
            return true;
        }
        return false;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution459;
int main() {
    Solution solution;
    solution.repeatedSubstringPattern("abcabcaa");
    return 0;
}