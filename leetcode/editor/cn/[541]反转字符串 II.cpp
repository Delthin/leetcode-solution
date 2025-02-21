/**
给定一个字符串 s 和一个整数 k，从字符串开头算起，每计数至 2k 个字符，就反转这 2k 字符中的前 k 个字符。 

 
 如果剩余字符少于 k 个，则将剩余字符全部反转。 
 如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。 
 

 

 示例 1： 

 
输入：s = "abcdefg", k = 2
输出："bacdfeg"
 

 示例 2： 

 
输入：s = "abcd", k = 2
输出："bacd"
 

 

 提示： 

 
 1 <= s.length <= 10⁴ 
 s 仅由小写英文组成 
 1 <= k <= 10⁴ 
 

 Related Topics 双指针 字符串 👍 655 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution541{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    string reverseStr(string s, int k) {
        int i = 0;
        for (;i < s.size(); i += 2 * k) {
            int l = i, r = l + k - 1;
            if (i + 2 * k > s.size()) {
                r = min(static_cast<int>(s.size() - 1), l + k - 1);
            }
            while (l < r) {
                swap(s[l], s[r]);
                l++;
                r--;
            }
        }
        return s;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution541;
int main() {
    Solution solution;

    return 0;
}