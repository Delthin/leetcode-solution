/**
假设你是球队的经理。对于即将到来的锦标赛，你想组合一支总体得分最高的球队。球队的得分是球队中所有球员的分数 总和 。 

 然而，球队中的矛盾会限制球员的发挥，所以必须选出一支 没有矛盾 的球队。如果一名年龄较小球员的分数 严格大于 一名年龄较大的球员，则存在矛盾。同龄球员之间不会
发生矛盾。 

 给你两个列表 scores 和 ages，其中每组 scores[i] 和 ages[i] 表示第 i 名球员的分数和年龄。请你返回 所有可能的无矛盾球队中得
分最高那支的分数 。 

 

 示例 1： 

 输入：scores = [1,3,5,10,15], ages = [1,2,3,4,5]
输出：34
解释：你可以选中所有球员。 

 示例 2： 

 输入：scores = [4,5,6,5], ages = [2,1,2,1]
输出：16
解释：最佳的选择是后 3 名球员。注意，你可以选中多个同龄球员。
 

 示例 3： 

 输入：scores = [1,2,3,5], ages = [8,9,10,1]
输出：6
解释：最佳的选择是前 3 名球员。
 

 

 提示： 

 
 1 <= scores.length, ages.length <= 1000 
 scores.length == ages.length 
 1 <= scores[i] <= 10⁶ 
 1 <= ages[i] <= 1000 
 

 Related Topics 数组 动态规划 排序 👍 236 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1626{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n =scores.size();
        vector<pair<int, int>> members(n);
        for (int i = 0; i < n; i++) {
            members[i] = {scores[i], ages[i]};
        }
        sort(members.begin(), members.end());
        vector<int> dp(n, 0);
        int res = members[0].first;
        dp[0] = members[0].first;
        for (int i = 1; i < n; ++i) {
            auto [score_i, age_i] = members[i];
            dp[i] = score_i;
            for (int j = 0; j < i; ++j) {
                auto [score_j, age_j] = members[j];
                if (age_j <= age_i) {
                    dp[i] = max(dp[i], dp[j] + score_i);
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1626;
int main() {
    Solution solution;
    vector<int> scores = {1,3,5,10,15};
    vector<int> ages = {1,2,3,4,5};
    cout << solution.bestTeamScore(scores, ages) << endl;
    return 0;
}