/**
给你一个字符串 s ，请你统计并返回这个字符串中 回文子串 的数目。 

 回文字符串 是正着读和倒过来读一样的字符串。 

 子字符串 是字符串中的由连续字符组成的一个序列。 

 

 示例 1： 

 
输入：s = "abc"
输出：3
解释：三个回文子串: "a", "b", "c"
 

 示例 2： 

 
输入：s = "aaa"
输出：6
解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa" 

 

 提示： 

 
 1 <= s.length <= 1000 
 s 由小写英文字母组成 
 

 Related Topics 双指针 字符串 动态规划 👍 1413 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution647{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int countSubstrings(string s) {
        int result = 0;
        for (int i = 0; i < s.size(); i++) {
            result += extend(s, i, i, s.size()); // 以i为中心
            result += extend(s, i, i + 1, s.size()); // 以i和i+1为中心
        }
        return result;
    }
    int extend(const string& s, int i, int j, int n) {
        int res = 0;
        while (i >= 0 && j < n && s[i] == s[j]) {
            i--;
            j++;
            res++;
        }
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution647;
int main() {
    Solution solution;

    return 0;
}