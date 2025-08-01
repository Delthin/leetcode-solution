/**
给你一个长度为 n 的整数数组 nums ，这个数组中至多有 50 个不同的值。同时你有 m 个顾客的订单 quantity ，其中，整数 quantity[
i] 是第 i 位顾客订单的数目。请你判断是否能将 nums 中的整数分配给这些顾客，且满足： 

 
 第 i 位顾客 恰好 有 quantity[i] 个整数。 
 第 i 位顾客拿到的整数都是 相同的 。 
 每位顾客都满足上述两个要求。 
 

 如果你可以分配 nums 中的整数满足上面的要求，那么请返回 true ，否则返回 false 。 

 

 示例 1： 

 
输入：nums = [1,2,3,4], quantity = [2]
输出：false
解释：第 0 位顾客没办法得到两个相同的整数。
 

 示例 2： 

 
输入：nums = [1,2,3,3], quantity = [2]
输出：true
解释：第 0 位顾客得到 [3,3] 。整数 [1,2] 都没有被使用。
 

 示例 3： 

 
输入：nums = [1,1,2,2], quantity = [2,2]
输出：true
解释：第 0 位顾客得到 [1,1] ，第 1 位顾客得到 [2,2] 。
 

 

 提示： 

 
 n == nums.length 
 1 <= n <= 10⁵ 
 1 <= nums[i] <= 1000 
 m == quantity.length 
 1 <= m <= 10 
 1 <= quantity[i] <= 10⁵ 
 nums 中至多有 50 个不同的数字。 
 

 Related Topics 位运算 数组 动态规划 回溯 状态压缩 👍 63 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1655{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        map<int, int> freq;
        for (int num:nums) {
            freq[num]++;
        }
        vector<int> cnt;
        for (auto& [num, count]:freq) {
            cnt.emplace_back(count);
        }
        int n = cnt.size();
        int m = quantity.size();
        int size = 1 << m;
        vector<int> sum(size, 0);
        for (int s = 1; s < size; s++) {
            for (int j = 0; j < m; j++) {
                if (s >> j & 1) {
                    sum[s] = sum[s ^ 1 << j] + quantity[j];
                    break;
                }
            }
        }
        // 用 dp[i][j] 表示：cnt 数组中的前 i - 1 个元素，能否满足顾客的子集合 j 的订单需求。
        // vector<vector<bool>> f(n + 1, vector<bool>(size, false));
        // f[0][0] = true;
        // for (int i = 1; i <= n; i++) {
        //     for (int s = 0; s < size; s++) {
        //         if (f[i - 1][s]) {
        //             f[i][s] = true;
        //             continue;
        //         }
        //         for (int sub = s; sub > 0; sub = sub - 1 & s) {
        //             if (cnt[i - 1] >= sum[sub]) {
        //                 f[i][s] = f[i][s] | f[i - 1][s^sub];
        //             }
        //         }
        //     }
        // }
        // return f[n][size - 1];
        vector<bool> f(size, false);
        f[0] = true;
        for (int i = 0; i < n; i++) {
            for (int s = size - 1; s > 0; s--) {
                if (f[s]) continue;
                for (int sub = s; sub > 0; sub = sub - 1 & s) {
                    if (cnt[i] >= sum[sub]) {
                        f[s] = f[s] | f[s ^ sub];
                    }
                }
            }
        }
        return f[size - 1];
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1655;
int main() {
    Solution solution;

    return 0;
}