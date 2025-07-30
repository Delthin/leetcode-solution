/**
「快乐前缀」 是在原字符串中既是 非空 前缀也是后缀（不包括原字符串自身）的字符串。 

 给你一个字符串 s，请你返回它的 最长快乐前缀。如果不存在满足题意的前缀，则返回一个空字符串
 "" 。 

 

 示例 1： 

 
输入：s = "level"
输出："l"
解释：不包括 s 自己，一共有 4 个前缀（"l", "le", "lev", "leve"）和 4 个后缀（"l", "el", "vel", "evel"）
。最长的既是前缀也是后缀的字符串是 "l" 。
 

 示例 2： 

 
输入：s = "ababab"
输出："abab"
解释："abab" 是最长的既是前缀也是后缀的字符串。题目允许前后缀在原字符串中重叠。
 

 

 提示： 

 
 1 <= s.length <= 10⁵ 
 s 只含有小写英文字母 
 

 Related Topics 字符串 字符串匹配 哈希函数 滚动哈希 👍 131 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1392{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    vector<int> compute_next(const string& p) {
        if (p.empty()) return {};
        vector<int> next(p.length());
        for (int i = 1, j = 0; i < p.length(); i++) {
            while (j > 0 && p[i] != p[j]) {
                j = next[j - 1];
            }
            if (p[i] == p[j]) {
                j++;
            }
            next[i] = j;
        }
        return next;
    }

    // 在文本串s中查找模式串p的所有出现位置 (返回0-indexed的起始下标)
    vector<int> kmp_search(const string& s, const string& p) {
        if (p.empty() || s.length() < p.length()) return {};

        vector<int> next = compute_next(p);
        vector<int> result;

        for (int i = 0, j = 0; i < s.length(); i++) {
            while (j > 0 && s[i] != p[j]) {
                j = next[j - 1];
            }
            if (s[i] == p[j]) {
                j++;
            }
            if (j == p.length()) {
                result.push_back(i - j + 1);
                j = next[j - 1]; // 继续寻找下一个匹配
            }
        }
        return result;
    }
public:
    string longestPrefix(string s) {
        vector<int> next = compute_next(s);
        int max_len = next[s.size() - 1];
        return s.substr(0, max_len);
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1392;
int main() {
    Solution solution;

    return 0;
}