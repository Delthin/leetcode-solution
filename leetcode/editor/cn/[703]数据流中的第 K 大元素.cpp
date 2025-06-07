/**
设计一个找到数据流中第 k 大元素的类（class）。注意是排序后的第 k 大元素，不是第 k 个不同的元素。 

 请实现 KthLargest 类： 

 
 KthLargest(int k, int[] nums) 使用整数 k 和整数流 nums 初始化对象。 
 int add(int val) 将 val 插入数据流 nums 后，返回当前数据流中第 k 大的元素。 
 

 

 示例 1： 

 
 输入： ["KthLargest", "add", "add", "add", "add", "add"] [[3, [4, 5, 8, 2]], [3], 
[5], [10], [9], [4]] 
 

 输出：[null, 4, 5, 5, 8, 8] 

 解释： 

 KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]); kthLargest.add(3); // 
返回 4 kthLargest.add(5); // 返回 5 kthLargest.add(10); // 返回 5 kthLargest.add(9); /
/ 返回 8 kthLargest.add(4); // 返回 8 

 

 示例 2： 

 
 输入： ["KthLargest", "add", "add", "add", "add"] [[4, [7, 7, 7, 7, 8, 3]], [2], [
10], [9], [9]] 
 

 输出：[null, 7, 7, 7, 8] 

 解释： KthLargest kthLargest = new KthLargest(4, [7, 7, 7, 7, 8, 3]);
 kthLargest.add(2); // 返回 7
 kthLargest.add(10); // 返回 7
 kthLargest.add(9); // 返回 7
 kthLargest.add(9); // 返回 8

 
提示：

 
 0 <= nums.length <= 10⁴ 
 1 <= k <= nums.length + 1 
 -10⁴ <= nums[i] <= 10⁴ 
 -10⁴ <= val <= 10⁴ 
 最多调用 add 方法 10⁴ 次 
 

 Related Topics 树 设计 二叉搜索树 二叉树 数据流 堆（优先队列） 👍 499 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution703{
//leetcode submit region begin(Prohibit modification and deletion)
class KthLargest {
    priority_queue<int, vector<int>, greater<>> pq;
    int _k;
public:
    KthLargest(int k, vector<int>& nums) {
        _k = k;
        for (int num: nums) {
            pq.push(num);
            if (pq.size() > _k) {
                pq.pop();
            }
        }
    }
    
    int add(int val) {
        pq.push(val);
        if (pq.size() > _k) {
            pq.pop();
        }
        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution703;
int main() {
    vector<int> vec = {4,5,8,2};
    KthLargest kth(3, vec);
    kth.add(3);


    return 0;
}