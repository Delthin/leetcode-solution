//给你一个字符串 s 和一个机器人，机器人当前有一个空字符串 t 。执行以下操作之一，直到 s 和 t 都变成空字符串： 
//
// 
// 删除字符串 s 的 第一个 字符，并将该字符给机器人。机器人把这个字符添加到 t 的尾部。 
// 删除字符串 t 的 最后一个 字符，并将该字符给机器人。机器人将该字符写到纸上。 
// 
//
// 请你返回纸上能写出的字典序最小的字符串。 
//
// 
//
// 示例 1： 
//
// 输入：s = "zza"
//输出："azz"
//解释：用 p 表示写出来的字符串。
//一开始，p="" ，s="zza" ，t="" 。
//执行第一个操作三次，得到 p="" ，s="" ，t="zza" 。
//执行第二个操作三次，得到 p="azz" ，s="" ，t="" 。
// 
//
// 示例 2： 
//
// 输入：s = "bac"
//输出："abc"
//解释：用 p 表示写出来的字符串。
//执行第一个操作两次，得到 p="" ，s="c" ，t="ba" 。
//执行第二个操作两次，得到 p="ab" ，s="c" ，t="" 。
//执行第一个操作，得到 p="ab" ，s="" ，t="c" 。
//执行第二个操作，得到 p="abc" ，s="" ，t="" 。
// 
//
// 示例 3： 
//
// 输入：s = "bdda"
//输出："addb"
//解释：用 p 表示写出来的字符串。
//一开始，p="" ，s="bdda" ，t="" 。
//执行第一个操作四次，得到 p="" ，s="" ，t="bdda" 。
//执行第二个操作四次，得到 p="addb" ，s="" ，t="" 。
// 
//
// 
//
// 提示： 
//
// 
// 1 <= s.length <= 10⁵ 
// s 只包含小写英文字母。 
// 
//
// Related Topics 栈 贪心 哈希表 字符串 👍 69 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution2434{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    string robotWithString(string s) {
        // 相当于每段每段翻转，字典序最小
        int n = s.size();
        // 计算后缀最小值
        vector<char> suf_min(n + 1);
        suf_min[n] = 'z';
        for (int i = n - 1; i >= 0; i--) {
            suf_min[i] = min(suf_min[i + 1], s[i]);
        }
        stack<char> st;
        string ans;
        for (int i = 0; i < n; i++) {
            st.emplace(s[i]);
            while (!st.empty() && suf_min[i + 1] >= st.top()) {
                ans.push_back(st.top());
                st.pop();
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2434;
int main() {
    Solution solution;

    return 0;
}