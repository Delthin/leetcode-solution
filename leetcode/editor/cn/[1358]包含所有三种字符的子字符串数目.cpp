////给你一个字符串 s ，它只包含三种字符 a, b 和 c 。 
////
//// 请你返回 a，b 和 c 都 至少 出现过一次的子字符串数目。 
////
//// 
////
//// 示例 1： 
////
//// 输入：s = "abcabc"
////输出：10
////解释：包含 a，b 和 c 各至少一次的子字符串为 "abc", "abca", "abcab", "abcabc", "bca", "bcab", 
////"bcabc", "cab", "cabc" 和 "abc" (相同字符串算多次)。
//// 
////
//// 示例 2： 
////
//// 输入：s = "aaacb"
////输出：3
////解释：包含 a，b 和 c 各至少一次的子字符串为 "aaacb", "aacb" 和 "acb" 。
//// 
////
//// 示例 3： 
////
//// 输入：s = "abc"
////输出：1
//// 
////
//// 
////
//// 提示： 
////
//// 
//// 3 <= s.length <= 5 x 10^4 
//// s 只包含字符 a，b 和 c 。 
//// 
////
//// Related Topics 哈希表 字符串 滑动窗口 👍 140 👎 0
//

#include <bits/stdc++.h>

using namespace std;
  
namespace solution1358{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int numberOfSubstrings(string s) {
        unordered_map<int, int> freq;
        int ans = 0;
        int l = 0, r = 0;
        for (; r < s.size(); r++) {
            freq[s[r]]++;
            while (freq.size() == 3) {
                ans += s.size() - r;
                freq[s[l]]--;
                if (freq[s[l]] == 0) {
                    freq.erase(s[l]);
                }
                l++;
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1358;
int main() {
    Solution solution;

    return 0;
}