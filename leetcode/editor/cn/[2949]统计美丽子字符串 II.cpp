/**
给你一个字符串 s 和一个正整数 k 。 

 用 vowels 和 consonants 分别表示字符串中元音字母和辅音字母的数量。 

 如果某个字符串满足以下条件，则称其为 美丽字符串 ： 

 
 vowels == consonants，即元音字母和辅音字母的数量相等。 
 (vowels * consonants) % k == 0，即元音字母和辅音字母的数量的乘积能被 k 整除。 
 

 返回字符串 s 中 非空美丽子字符串 的数量。 

 子字符串是字符串中的一个连续字符序列。 

 英语中的 元音字母 为 'a'、'e'、'i'、'o' 和 'u' 。 

 英语中的 辅音字母 为除了元音字母之外的所有字母。 

 

 示例 1： 

 
输入：s = "baeyh", k = 2
输出：2
解释：字符串 s 中有 2 个美丽子字符串。
- 子字符串 "baeyh"，vowels = 2（["a","e"]），consonants = 2（["y","h"]）。
可以看出字符串 "aeyh" 是美丽字符串，因为 vowels == consonants 且 vowels * consonants % k == 0 。
- 子字符串 "baeyh"，vowels = 2（["a","e"]），consonants = 2（["b","y"]）。
可以看出字符串 "baey" 是美丽字符串，因为 vowels == consonants 且 vowels * consonants % k == 0 。
可以证明字符串 s 中只有 2 个美丽子字符串。
 

 示例 2： 

 
输入：s = "abba", k = 1
输出：3
解释：字符串 s 中有 3 个美丽子字符串。
- 子字符串 "abba"，vowels = 1（["a"]），consonants = 1（["b"]）。
- 子字符串 "abba"，vowels = 1（["a"]），consonants = 1（["b"]）。
- 子字符串 "abba"，vowels = 2（["a","a"]），consonants = 2（["b","b"]）。
可以证明字符串 s 中只有 3 个美丽子字符串。
 

 示例 3： 

 
输入：s = "bcdf", k = 1
输出：0
解释：字符串 s 中没有美丽子字符串。
 

 

 提示： 

 
 1 <= s.length <= 5 * 10⁴ 
 1 <= k <= 1000 
 s 仅由小写英文字母组成。 
 

 Related Topics 哈希表 数学 字符串 数论 前缀和 👍 22 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2949{
//leetcode submit region begin(Prohibit modification and deletion)
    class Solution {
        int p_sqrt(int n) {
            int res = 1;
            for (int i = 2; i * i <= n; i++) {
                int i2 = i * i;
                while (n % i2 == 0) {
                    res *= i;
                    n /= i2;
                }
                if (n % i == 0) {
                    res *= i;
                    n /= i;
                }
            }
            if (n > 1) {
                res *= n;
            }
            return res;
        }

        const int AEIOU_MASK = 1065233;

    public:
        long long beautifulSubstrings(string s, int k) {
            k = p_sqrt(k * 4);
            // 把 pair 压缩成 long long（或者 int）就可以用 umap 了
            map<pair<int, int>, int> cnt;
            cnt[{k - 1, 0}]++; // 添加 (k-1, sum)
            long long ans = 0;
            int sum = 0;
            for (int i = 0; i < s.length(); i++) {
                int bit = (AEIOU_MASK >> (s[i] - 'a')) & 1;
                sum += bit * 2 - 1; // 1 -> 1    0 -> -1
                ans += cnt[{i % k, sum}]++;
            }
            return ans;
        }
    };

//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2949;
int main() {
    Solution solution;

    return 0;
}