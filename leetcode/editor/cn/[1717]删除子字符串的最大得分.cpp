/**
给你一个字符串 s 和两个整数 x 和 y 。你可以执行下面两种操作任意次。 

 
 删除子字符串 "ab" 并得到 x 分。 
 

 
 比方说，从 "cabxbae" 删除 ab ，得到 "cxbae" 。 
 
 
 删除子字符串"ba" 并得到 y 分。
 
 比方说，从 "cabxbae" 删除 ba ，得到 "cabxe" 。 
 
 


 请返回对 s 字符串执行上面操作若干次能得到的最大得分。 

 

 示例 1： 

 输入：s = "cdbcbbaaabab", x = 4, y = 5
输出：19
解释：
- 删除 "cdbcbbaaabab" 中加粗的 "ba" ，得到 s = "cdbcbbaaab" ，加 5 分。
- 删除 "cdbcbbaaab" 中加粗的 "ab" ，得到 s = "cdbcbbaa" ，加 4 分。
- 删除 "cdbcbbaa" 中加粗的 "ba" ，得到 s = "cdbcba" ，加 5 分。
- 删除 "cdbcba" 中加粗的 "ba" ，得到 s = "cdbc" ，加 5 分。
总得分为 5 + 4 + 5 + 5 = 19 。 

 示例 2： 

 输入：s = "aabbaaxybbaabb", x = 5, y = 4
输出：20
 

 

 提示： 

 
 1 <= s.length <= 10⁵ 
 1 <= x, y <= 10⁴ 
 s 只包含小写英文字母。 
 

 Related Topics 栈 贪心 字符串 👍 37 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1717{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    int getMax(string s, int x, int y, char a, char b) {
        // 假设ab大，遇到大的就消
        // aaaaaa
        // bbbbbbbaaaaaaa
        int c1 = 0, c2 = 0, ans = 0;
        s += 'c';// 隔断最后一个
        for (char c : s) {
            if (c == a) c1++;
            else if (c == b) {
                if (c1 == 0) c2++;
                else {
                    ans += x;
                    c1--;
                }
            } else {
                // 只可能出现ba，减去min个数即可
                ans += min(c2, c1) * y;
                c1 = 0;
                c2 = 0;
            }
        }
        return ans;
    }
public:
    int maximumGain(string s, int x, int y) {
        return x > y ? getMax(s, x, y, 'a', 'b') : getMax(s, y, x, 'b', 'a');
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1717;
int main() {
    Solution solution;

    return 0;
}