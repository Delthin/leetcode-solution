/**
给定两个字符串 a 和 b，寻找重复叠加字符串 a 的最小次数，使得字符串 b 成为叠加后的字符串 a 的子串，如果不存在则返回 -1。 

 注意：字符串 "abc" 重复叠加 0 次是 ""，重复叠加 1 次是 "abc"，重复叠加 2 次是 "abcabc"。 

 

 示例 1： 

 输入：a = "abcd", b = "cdabcdab"
输出：3
解释：a 重复叠加三遍后为 "abcdabcdabcd", 此时 b 是其子串。
 

 示例 2： 

 输入：a = "a", b = "aa"
输出：2
 

 示例 3： 

 输入：a = "a", b = "a"
输出：1
 

 示例 4： 

 输入：a = "abc", b = "wxyz"
输出：-1
 

 

 提示： 

 
 1 <= a.length <= 10⁴ 
 1 <= b.length <= 10⁴ 
 a 和 b 由小写英文字母组成 
 

 Related Topics 字符串 字符串匹配 👍 347 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution686{
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
    int repeatedStringMatch(string a, string b) {
        int n = a.length(), m = b.length();
        int repeat = m / n;
        string s;
        for (int i = 1; i <= repeat; i++) {
            s += a;
        }
        while (repeat < m / n + 5) {
            vector<int> indices = kmp_search(s, b);
            if (!indices.empty()) {
                return repeat;
            }
            repeat++;
            s += a;
        }
        return -1;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution686;
int main() {
    Solution solution;

    return 0;
}