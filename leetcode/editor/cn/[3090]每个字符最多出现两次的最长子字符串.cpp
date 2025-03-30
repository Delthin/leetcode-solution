/**
给你一个字符串 s ，请找出满足每个字符最多出现两次的最长子字符串，并返回该子字符串的 最大 长度。 

 

 示例 1： 

 
 输入： s = "bcbbbcba" 
 

 输出： 4 

 解释： 

 以下子字符串长度为 4，并且每个字符最多出现两次："bcbbbcba"。 

 示例 2： 

 
 输入： s = "aaaa" 
 

 输出： 2 

 解释： 

 以下子字符串长度为 2，并且每个字符最多出现两次："aaaa"。 

 

 提示： 

 
 
 2 <= s.length <= 100 
 
 s 仅由小写英文字母组成。 
 

 Related Topics 哈希表 字符串 滑动窗口 👍 23 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution3090{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int maximumLengthSubstring(string s) {
        unordered_map<int, int> freq;
        int ans = 0;
        int l = 0, r = 0;
        for (; r < s.size(); r++) {
            if (freq[s[r]]++ == 2) {
                ans = max(ans, r - l);
                while (freq[s[r]] == 3) {
                    freq[s[l++]]--;
                }
            }
        }
        ans = max(ans, r - l);
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3090;
int main() {
    Solution solution;

    return 0;
}