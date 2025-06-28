/**
一个魔法师有许多不同的咒语。 

 给你一个数组 power ，其中每个元素表示一个咒语的伤害值，可能会有多个咒语有相同的伤害值。 

 已知魔法师使用伤害值为 power[i] 的咒语时，他们就 不能 使用伤害为 power[i] - 2 ，power[i] - 1 ，power[i] + 1
 或者 power[i] + 2 的咒语。 

 每个咒语最多只能被使用 一次 。 

 请你返回这个魔法师可以达到的伤害值之和的 最大值 。 

 

 示例 1： 

 
 输入：power = [1,1,3,4] 
 

 输出：6 

 解释： 

 可以使用咒语 0，1，3，伤害值分别为 1，1，4，总伤害值为 6 。 

 示例 2： 

 
 输入：power = [7,1,6,6] 
 

 输出：13 

 解释： 

 可以使用咒语 1，2，3，伤害值分别为 1，6，6，总伤害值为 13 。 

 

 提示： 

 
 1 <= power.length <= 10⁵ 
 1 <= power[i] <= 10⁹ 
 

 Related Topics 数组 哈希表 双指针 二分查找 动态规划 计数 排序 👍 56 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution3186{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        using ll = long long;
        unordered_map<int, int> um;
        for (int i : power) {
            um[i]++;
        }
        int n = um.size();
        vector<ll> p_unique;
        for (auto & it : um) {
            p_unique.emplace_back(it.first);
        }
        sort(p_unique.begin(),p_unique.end());
        vector<ll> dp(n, 0);
        dp[0] = p_unique[0] * um[p_unique[0]];
        for (int i = 1; i < n; i++) {
            // 往前找到不在范围内的加自己
            ll before = dp[i];
            for (int j = i - 1; j >= 0; j--) {
                if (p_unique[j] < p_unique[i] - 2) {
                    before = dp[j];
                    break;
                }
            }
            dp[i] = max(before + p_unique[i] * (ll)um[p_unique[i]], dp[i - 1]);
        }
        return dp[n - 1];
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3186;
int main() {
    Solution solution;
    vector<int> power = {7, 1, 6, 3};
    solution.maximumTotalDamage(power);
    return 0;
}