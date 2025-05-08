/**
给你两个下标从 1 开始的整数数组 nums 和 changeIndices ，数组的长度分别为 n 和 m 。 

 一开始，nums 中所有下标都是未标记的，你的任务是标记 nums 中 所有 下标。 

 从第 1 秒到第 m 秒（包括 第 m 秒），对于每一秒 s ，你可以执行以下操作 之一 ： 

 
 选择范围 [1, n] 中的一个下标 i ，并且将 nums[i] 减少 1 。 
 如果 nums[changeIndices[s]] 等于 0 ，标记 下标 changeIndices[s] 。 
 什么也不做。 
 

 请你返回范围 [1, m] 中的一个整数，表示最优操作下，标记 nums 中 所有 下标的 最早秒数 ，如果无法标记所有下标，返回 -1 。 

 

 示例 1： 

 
输入：nums = [2,2,0], changeIndices = [2,2,2,2,3,2,2,1]
输出：8
解释：这个例子中，我们总共有 8 秒。按照以下操作标记所有下标：
第 1 秒：选择下标 1 ，将 nums[1] 减少 1 。nums 变为 [1,2,0] 。
第 2 秒：选择下标 1 ，将 nums[1] 减少 1 。nums 变为 [0,2,0] 。
第 3 秒：选择下标 2 ，将 nums[2] 减少 1 。nums 变为 [0,1,0] 。
第 4 秒：选择下标 2 ，将 nums[2] 减少 1 。nums 变为 [0,0,0] 。
第 5 秒，标​​​​​记 changeIndices[5] ，也就是标记下标 3 ，因为 nums[3] 等于 0 。
第 6 秒，标​​​​​记 changeIndices[6] ，也就是标记下标 2 ，因为 nums[2] 等于 0 。
第 7 秒，什么也不做。
第 8 秒，标记 changeIndices[8] ，也就是标记下标 1 ，因为 nums[1] 等于 0 。
现在所有下标已被标记。
最早可以在第 8 秒标记所有下标。
所以答案是 8 。
 

 示例 2： 

 
输入：nums = [1,3], changeIndices = [1,1,1,2,1,1,1]
输出：6
解释：这个例子中，我们总共有 7 秒。按照以下操作标记所有下标：
第 1 秒：选择下标 2 ，将 nums[2] 减少 1 。nums 变为 [1,2] 。
第 2 秒：选择下标 2 ，将 nums[2] 减少 1 。nums 变为 [1,1] 。
第 3 秒：选择下标 2 ，将 nums[2] 减少 1 。nums 变为 [1,0] 。
第 4 秒：标​​​​​记 changeIndices[4] ，也就是标记下标 2 ，因为 nums[2] 等于 0 。
第 5 秒：选择下标 1 ，将 nums[1] 减少 1 。nums 变为 [0,0] 。
第 6 秒：标​​​​​记 changeIndices[6] ，也就是标记下标 1 ，因为 nums[1] 等于 0 。
现在所有下标已被标记。
最早可以在第 6 秒标记所有下标。
所以答案是 6 。
 

 示例 3： 

 
Input: nums = [0,1], changeIndices = [2,2,2]
Output: -1
Explanation: 这个例子中，无法标记所有下标，因为下标 1 不在 changeIndices 中。
所以答案是 -1 。
 

 

 提示： 

 
 1 <= n == nums.length <= 2000 
 0 <= nums[i] <= 10⁹ 
 1 <= m == changeIndices.length <= 2000 
 1 <= changeIndices[i] <= n 
 

 Related Topics 数组 二分查找 👍 33 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution3048{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        int n = nums.size();
        int m = changeIndices.size();
        if (n > m) return -1;
        vector<int> last_index(n);
        auto check = [&] (int time) {
            for (int i = 0; i < n; i++) {
                last_index[i] = -1;
            }
            for (int i = 0; i < time; i++) {
                int mark = changeIndices[i] - 1;
                last_index[mark] = i;
            }
            if (find(last_index.begin(), last_index.end(), -1) != last_index.end()) return false;
            int operations = 0;
            for (int i = 0; i < time; i++) {
                int mark = changeIndices[i] - 1;
                if (last_index[mark] == i) {
                    if (nums[mark] > operations) {
                        return false;
                    }
                    operations -= nums[mark];
                } else {
                    operations++;
                }
            }
            return true;
        };
        int l = n - 1, r = m + 1;
        while (l + 1 < r) {
            int mid = l + (r - l) / 2;
            (check(mid) ? r : l) = mid;
        }
        return r > m ? -1 : r;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3048;
int main() {
    Solution solution;

    return 0;
}