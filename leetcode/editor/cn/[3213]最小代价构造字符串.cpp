/**
给你一个字符串 target、一个字符串数组 words 以及一个整数数组 costs，这两个数组长度相同。 

 设想一个空字符串 s。 

 你可以执行以下操作任意次数（包括 零 次）： 

 
 选择一个在范围 [0, words.length - 1] 的索引 i。 
 将 words[i] 追加到 s。 
 该操作的成本是 costs[i]。 
 

 返回使 s 等于 target 的 最小 成本。如果不可能，返回 -1。 

 

 示例 1： 

 
 输入： target = "abcdef", words = ["abdef","abc","d","def","ef"], costs = [100,1,1
,10,5] 
 

 输出： 7 

 解释： 

 
 选择索引 1 并以成本 1 将 "abc" 追加到 s，得到 s = "abc"。 
 选择索引 2 并以成本 1 将 "d" 追加到 s，得到 s = "abcd"。 
 选择索引 4 并以成本 5 将 "ef" 追加到 s，得到 s = "abcdef"。 
 

 示例 2： 

 
 输入： target = "aaaa", words = ["z","zz","zzz"], costs = [1,10,100] 
 

 输出： -1 

 解释： 

 无法使 s 等于 target，因此返回 -1。 

 

 提示： 

 
 1 <= target.length <= 5 * 10⁴ 
 1 <= words.length == costs.length <= 5 * 10⁴ 
 1 <= words[i].length <= target.length 
 所有 words[i].length 的总和小于或等于 5 * 10⁴ 
 target 和 words[i] 仅由小写英文字母组成。 
 1 <= costs[i] <= 10⁴ 
 

 Related Topics 数组 字符串 动态规划 后缀数组 👍 19 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution3213{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    using ULL = unsigned long long;
    struct StringHasher {
    private:
        long long P1, P2, M1, M2;
        vector<long long> h1, h2, p1, p2;
        static const auto &get_params() {
            static const auto params = [] {
                mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
                auto dist = uniform_int_distribution<long long>(8e8, 9e8);
                long long p1 = dist(rng), p2 = dist(rng);
                while (p2 == p1) p2 = dist(rng);
                return std::make_tuple(p1, p2, 1000000007LL, 1'070'777'777LL);
            }();
            return params;
        }
    public:
        // 构造函数
        StringHasher(const std::string &s) {
            // 从静态函数获取共享的哈希参数
            std::tie(P1, P2, M1, M2) = get_params();
            int n = s.length();
            h1.resize(n + 1, 0);
            h2.resize(n + 1, 0);
            p1.resize(n + 1, 0);
            p2.resize(n + 1, 0);
            p1[0] = p2[0] = 1;
            for (int i = 0; i < n; ++i) {
                p1[i + 1] = (p1[i] * P1) % M1;
                p2[i + 1] = (p2[i] * P2) % M2;
                // 建议偏移，避免 s[i] 值为 0 引起的问题
                h1[i + 1] = (h1[i] * P1 + (s[i] - 'a' + 1)) % M1;
                h2[i + 1] = (h2[i] * P2 + (s[i] - 'a' + 1)) % M2;
            }
        }

        ULL get_hash(int l, int r) {
            long long hash1 = (h1[r + 1] - (h1[l] * p1[r - l + 1]) % M1 + M1) % M1;
            long long hash2 = (h2[r + 1] - (h2[l] * p2[r - l + 1]) % M2 + M2) % M2;
            return (ULL) hash1 << 32 | hash2;
        }

        std::pair<long long, long long> get_pair_hash(int l, int r) {
            long long hash1 = (h1[r + 1] - (h1[l] * p1[r - l + 1]) % M1 + M1) % M1;
            long long hash2 = (h2[r + 1] - (h2[l] * p2[r - l + 1]) % M2 + M2) % M2;
            return {hash1, hash2};
        }
    };
public:
    int minimumCost(string target, vector<string>& words, vector<int>& costs) {
        vector<int> dp(target.length() + 1, INT_MAX / 2);
        dp[0] = 0;
        StringHasher target_hasher(target);
        // 对长度进行dp
        map<int, unordered_map<long long, int>> min_cost;
        for (int j = 0; j < words.size(); ++j) {
            StringHasher word_hasher(words[j]);
            int len = words[j].length();
            ULL hash = word_hasher.get_hash(0, len - 1);
            if (min_cost[len].count(hash) == 0) {
                min_cost[len][hash] = costs[j];
            } else {
                min_cost[len][hash] = min(min_cost[len][hash], costs[j]);
            }
        }
        for (int i = 0; i < target.length(); ++i) {
            for (auto& [len, um]: min_cost) {
                if (i + len > target.length()) continue;
                auto it = um.find(target_hasher.get_hash(i, i + len - 1));
                if (it != um.end()) {
                    dp[i + len] = min(dp[i + len], dp[i] + it->second);
                }
            }
        }
        return dp[target.length()] == INT_MAX / 2 ? -1 : dp[target.length()];
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3213;
int main() {
    Solution solution;
    string target = "abcdef";
    vector<string> words = {"abdef", "abc", "d", "def", "ef"};
    vector<int> costs = {100, 1, 1, 10, 5};
    cout << solution.minimumCost(target, words, costs) << endl;
    return 0;
}