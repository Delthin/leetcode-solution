/**
给你一个非负整数数组 nums 和一个整数 k 。每次操作，你可以选择 nums 中 任一 元素并将它 增加 1 。 

 请你返回 至多 k 次操作后，能得到的 nums的 最大乘积 。由于答案可能很大，请你将答案对 10⁹ + 7 取余后返回。 

 

 示例 1： 

 输入：nums = [0,4], k = 5
输出：20
解释：将第一个数增加 5 次。
得到 nums = [5, 4] ，乘积为 5 * 4 = 20 。
可以证明 20 是能得到的最大乘积，所以我们返回 20 。
存在其他增加 nums 的方法，也能得到最大乘积。
 

 示例 2： 

 输入：nums = [6,3,3,2], k = 2
输出：216
解释：将第二个数增加 1 次，将第四个数增加 1 次。
得到 nums = [6, 4, 3, 3] ，乘积为 6 * 4 * 3 * 3 = 216 。
可以证明 216 是能得到的最大乘积，所以我们返回 216 。
存在其他增加 nums 的方法，也能得到最大乘积。
 

 

 提示： 

 
 1 <= nums.length, k <= 10⁵ 
 0 <= nums[i] <= 10⁶ 
 

 Related Topics 贪心 数组 堆（优先队列） 👍 39 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2233{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {

public:
    int maximumProduct(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<>> pq;
        for (int num: nums) pq.push(num);
        for (int i = 0; i < k; i++) {
            pq.push(pq.top() + 1);
            pq.pop();
        }
        long long res = 1;
        const int MOD = 1e9 + 7;
        while (!pq.empty()) {
            res = (res * pq.top()) % MOD;
            pq.pop();
        }
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2233;
int main() {
    Solution solution;

    return 0;
}