/**
给你一个下标从 0 开始的字符串 s 、字符串 a 、字符串 b 和一个整数 k 。 

 如果下标 i 满足以下条件，则认为它是一个 美丽下标 ： 

 
 0 <= i <= s.length - a.length 
 s[i..(i + a.length - 1)] == a 
 存在下标 j 使得： 
 
 0 <= j <= s.length - b.length 
 s[j..(j + b.length - 1)] == b 
 |j - i| <= k 
 
 

 以数组形式按 从小到大排序 返回美丽下标。 

 

 示例 1： 

 
输入：s = "isawsquirrelnearmysquirrelhouseohmy", a = "my", b = "squirrel", k = 15
输出：[16,33]
解释：存在 2 个美丽下标：[16,33]。
- 下标 16 是美丽下标，因为 s[16..17] == "my" ，且存在下标 4 ，满足 s[4..11] == "squirrel" 且 |16 - 4
| <= 15 。
- 下标 33 是美丽下标，因为 s[33..34] == "my" ，且存在下标 18 ，满足 s[18..25] == "squirrel" 且 |33 -
 18| <= 15 。
因此返回 [16,33] 作为结果。 

 示例 2： 

 
输入：s = "abcd", a = "a", b = "a", k = 4
输出：[0]
解释：存在 1 个美丽下标：[0]。
- 下标 0 是美丽下标，因为 s[0..0] == "a" ，且存在下标 0 ，满足 s[0..0] == "a" 且 |0 - 0| <= 4 。
因此返回 [0] 作为结果。 

 

 提示： 

 
 1 <= k <= s.length <= 5 * 10⁵ 
 1 <= a.length, b.length <= 5 * 10⁵ 
 s、a、和 b 只包含小写英文字母。 
 

 Related Topics 双指针 字符串 二分查找 字符串匹配 哈希函数 滚动哈希 👍 12 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution3008{
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
    vector<int> beautifulIndices(string s, string a, string b, int k) {
        vector<int> a_indices = kmp_search(s, a);
        vector<int> b_indices = kmp_search(s, b);
        vector<int> result;
        for (int i = 0, j = 0; i < a_indices.size(); i++) {
            while (j < b_indices.size() && b_indices[j] < a_indices[i] - k) {
                j++;
            }
            if (j < b_indices.size() && b_indices[j] <= a_indices[i] + k) {
                result.push_back(a_indices[i]);
            }
        }
        return result;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3008;
int main() {
    Solution solution;

    return 0;
}