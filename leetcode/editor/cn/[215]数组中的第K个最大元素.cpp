/**
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。 

 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。 

 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。 

 

 示例 1: 

 
输入: [3,2,1,5,6,4], k = 2
输出: 5
 

 示例 2: 

 
输入: [3,2,3,1,2,4,5,5,6], k = 4
输出: 4 

 

 提示： 

 
 1 <= k <= nums.length <= 10⁵ 
 -10⁴ <= nums[i] <= 10⁴ 
 

 Related Topics 数组 分治 快速选择 排序 堆（优先队列） 👍 2631 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution215{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<>> pq;
        for (int i = 0; i < k; i++) {
            pq.push(nums[i]);
        }
        for (int i = k; i < nums.size(); i++) {
            if (nums[i] > pq.top()) {
                pq.pop();
                pq.push(nums[i]);
            }
        }
        return pq.top();
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution215;
int main() {
    Solution solution;

    return 0;
}