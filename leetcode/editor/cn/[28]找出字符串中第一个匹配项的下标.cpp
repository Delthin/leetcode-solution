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
    public:
        int strStr(string haystack, string needle) {
            int n = haystack.size(), m = needle.size();
            if (m == 0) {
                return 0;
            }
            vector<int> pi(m);
            for (int i = 1, j = 0; i < m; i++) {
                while (j > 0 && needle[i] != needle[j]) {
                    j = pi[j - 1];
                }
                if (needle[i] == needle[j]) {
                    j++;
                }
                pi[i] = j;
            }
            for (int i = 0, j = 0; i < n; i++) {
                while (j > 0 && haystack[i] != needle[j]) {
                    j = pi[j - 1];
                }
                if (haystack[i] == needle[j]) {
                    j++;
                }
                if (j == m) {
                    return i - m + 1;
                }
            }
            return -1;
        }
    };
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution28;
int main() {
    Solution solution;

    return 0;
}