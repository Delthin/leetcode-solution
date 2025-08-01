/**
给你两个整数数组 nums1 和 nums2 ，它们长度都为 n 。 

 两个数组的 异或值之和 为 (nums1[0] XOR nums2[0]) + (nums1[1] XOR nums2[1]) + ... + (nums1[
n - 1] XOR nums2[n - 1]) （下标从 0 开始）。 

 
 比方说，[1,2,3] 和 [3,2,1] 的 异或值之和 等于 (1 XOR 3) + (2 XOR 2) + (3 XOR 1) = 2 + 0 + 2 
= 4 。 
 

 请你将 nums2 中的元素重新排列，使得 异或值之和 最小 。 

 请你返回重新排列之后的 异或值之和 。 

 

 示例 1： 

 输入：nums1 = [1,2], nums2 = [2,3]
输出：2
解释：将 nums2 重新排列得到 [3,2] 。
异或值之和为 (1 XOR 3) + (2 XOR 2) = 2 + 0 = 2 。 

 示例 2： 

 输入：nums1 = [1,0,3], nums2 = [5,3,4]
输出：8
解释：将 nums2 重新排列得到 [5,4,3] 。
异或值之和为 (1 XOR 5) + (0 XOR 4) + (3 XOR 3) = 4 + 4 + 0 = 8 。
 

 

 提示： 

 
 n == nums1.length 
 n == nums2.length 
 1 <= n <= 14 
 0 <= nums1[i], nums2[i] <= 10⁷ 
 

 Related Topics 位运算 数组 动态规划 状态压缩 👍 53 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1879{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int minimumXORSum(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        vector<int> f(1 << n, INT_MAX);
        f[0] = 0;
        for (int s = 1; s < 1 << n; s++) {
            int i = __builtin_popcount(s) - 1;
            for (int j = 0; j < n; j++) {
                if (s >> j & 1) {
                    f[s] = min(f[s], f[s ^ 1 << j] + (nums1[i] ^ nums2[j]));
                }
            }
        }
        return f[(1 << n) - 1];
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1879;
int main() {
    Solution solution;

    return 0;
}