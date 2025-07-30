/**
给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串的第一个匹配项的下标（下标从 0 开始）。如果
 needle 不是 haystack 的一部分，则返回 -1 。 

 

 示例 1： 

 
输入：haystack = "sadbutsad", needle = "sad"
输出：0
解释："sad" 在下标 0 和 6 处匹配。
第一个匹配项的下标是 0 ，所以返回 0 。
 

 示例 2： 

 
输入：haystack = "leetcode", needle = "leeto"
输出：-1
解释："leeto" 没有在 "leetcode" 中出现，所以返回 -1 。
 

 

 提示： 

 
 1 <= haystack.length, needle.length <= 10⁴ 
 haystack 和 needle 仅由小写英文字符组成 
 

 Related Topics 双指针 字符串 字符串匹配 👍 2362 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution28{
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
        int strStr(string haystack, string needle) {
            vector<int> result = kmp_search(haystack, needle);
            if (result.empty()) {
                return -1;
            }
            return result[0];
        }
    };
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution28;
int main() {
    Solution solution;

    return 0;
}