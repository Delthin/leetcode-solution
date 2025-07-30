/**
给你一个字符串 text ，请你返回满足下述条件的 不同 非空子字符串的数目： 

 
 可以写成某个字符串与其自身相连接的形式（即，可以写为 a + a，其中 a 是某个字符串）。 
 

 例如，abcabc 就是 abc 和它自身连接形成的。 

 

 示例 1： 

 输入：text = "abcabcabc"
输出：3
解释：3 个子字符串分别为 "abcabc"，"bcabca" 和 "cabcab" 。
 

 示例 2： 

 输入：text = "leetcodeleetcode"
输出：2
解释：2 个子字符串为 "ee" 和 "leetcodeleetcode" 。
 

 

 提示： 

 
 1 <= text.length <= 2000 
 text 只包含小写英文字母。 
 

 Related Topics 字典树 字符串 哈希函数 滚动哈希 👍 62 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1316{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    using ULL = unsigned long long;
    struct StringHasher {
        ULL p1 = 131, p2 = 13331; // 两个不同的质数基底
        vector<ULL> h1, h2, pw1, pw2;

        StringHasher(const string& s) {
            int n = s.length();
            h1.resize(n + 1); h2.resize(n + 1);
            pw1.resize(n + 1); pw2.resize(n + 1);
            pw1[0] = pw2[0] = 1;

            for (int i = 0; i < n; ++i) {
                pw1[i+1] = pw1[i] * p1;
                pw2[i+1] = pw2[i] * p2;
                h1[i+1] = h1[i] * p1 + s[i];
                h2[i+1] = h2[i] * p2 + s[i];
            }
        }

        // 获取子串 s[l..r] (0-indexed) 的哈希值
        pair<ULL, ULL> get_hash(int l, int r) {
            r++; // 转换为半开半闭区间 [l, r)
            ULL hash1 = h1[r] - h1[l] * pw1[r - l];
            ULL hash2 = h2[r] - h2[l] * pw2[r - l];
            return {hash1, hash2};
        }

        bool equal(int l1, int r1, int l2, int r2) {
            return get_hash(l1, r1) == get_hash(l2, r2);
        }
    };
public:
    int distinctEchoSubstrings(string text) {
        StringHasher hasher(text);
        set<pair<ULL,ULL>> seen;
        int n = text.length();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; j++) {
                int len = j - i;
                if (j + len > n) break;
                if (hasher.equal(i, j - 1, j, j + len - 1)) {
                    seen.insert(hasher.get_hash(i, j + len - 1));
                }
            }
        }
        return seen.size();
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1316;
int main() {
    Solution solution;

    return 0;
}