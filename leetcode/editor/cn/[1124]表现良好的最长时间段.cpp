//给你一份工作时间表 hours，上面记录着某一位员工每天的工作小时数。 
//
// 我们认为当员工一天中的工作小时数大于 8 小时的时候，那么这一天就是「劳累的一天」。 
//
// 所谓「表现良好的时间段」，意味在这段时间内，「劳累的天数」是严格 大于「不劳累的天数」。 
//
// 请你返回「表现良好时间段」的最大长度。 
//
// 
//
// 示例 1： 
//
// 
//输入：hours = [9,9,6,0,6,6,9]
//输出：3
//解释：最长的表现良好时间段是 [9,9,6]。 
//
// 示例 2： 
//
// 
//输入：hours = [6,6,6]
//输出：0
// 
//
// 
//
// 提示： 
//
// 
// 1 <= hours.length <= 10⁴ 
// 0 <= hours[i] <= 16 
// 
//
// Related Topics 栈 数组 哈希表 前缀和 单调栈 👍 574 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution1124{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        int n = hours.size();
        int prefix = 0;
        unordered_map<int, int> prefix2minIdx;

        int ans = 0;
        for (int i = 1; i <= n; i++) {
            prefix = prefix + (hours[i - 1] > 8 ? 1 : -1);
            if (prefix > 0) {
                ans = i;
            } else {
                if (prefix2minIdx.find(prefix - 1) != prefix2minIdx.end()) {
                    ans = max(ans, i - prefix2minIdx[prefix - 1]);
                }
            }
            if (prefix2minIdx.find(prefix) == prefix2minIdx.end()) {
                prefix2minIdx[prefix] = i;
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1124;
int main() {
    Solution solution;

    return 0;
}