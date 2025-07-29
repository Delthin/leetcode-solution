/**
数组 arr 中 大于 前面和后面相邻元素的元素被称为 峰值 元素。 

 给你一个整数数组 nums 和一个二维整数数组 queries 。 

 你需要处理以下两种类型的操作： 

 
 queries[i] = [1, li, ri] ，求出子数组 nums[li..ri] 中 峰值 元素的数目。
 
 queries[i] = [2, indexi, vali] ，将 nums[indexi] 变为 vali 。 
 

 请你返回一个数组 answer ，它依次包含每一个第一种操作的答案。
 

 注意： 

 
 子数组中 第一个 和 最后一个 元素都 不是 峰值元素。 
 

 

 示例 1： 

 
 输入：nums = [3,1,4,2,5], queries = [[2,3,4],[1,0,4]] 
 

 输出：[0] 

 解释： 

 第一个操作：我们将 nums[3] 变为 4 ，nums 变为 [3,1,4,4,5] 。 

 第二个操作：[3,1,4,4,5] 中峰值元素的数目为 0 。 

 示例 2： 

 
 输入：nums = [4,1,4,2,1,5], queries = [[2,2,4],[1,0,2],[1,0,4]] 
 

 输出：[0,1] 

 解释： 

 第一个操作：nums[2] 变为 4 ，它已经是 4 了，所以保持不变。 

 第二个操作：[4,1,4] 中峰值元素的数目为 0 。 

 第三个操作：第二个 4 是 [4,1,4,2,1] 中的峰值元素。 

 

 提示： 

 
 3 <= nums.length <= 10⁵ 
 1 <= nums[i] <= 10⁵ 
 1 <= queries.length <= 10⁵ 
 queries[i][0] == 1 或者 queries[i][0] == 2 
 对于所有的 i ，都有： 
 
 queries[i][0] == 1 ：0 <= queries[i][1] <= queries[i][2] <= nums.length - 1 
 queries[i][0] == 2 ：0 <= queries[i][1] <= nums.length - 1, 1 <= queries[i][2] <
= 10⁵ 
 
 

 Related Topics 树状数组 线段树 数组 👍 14 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution3187{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    template <typename T>
    struct FenwickTree {
        int n;
        vector<T> tree;

        FenwickTree(int size) : n(size), tree(size + 1, 0) {}

        static int lowbit(int x) {
            return x & -x;
        }

        // 将 a[x] 增加 val
        void add(int x, T val) {
            for (int i = x; i <= n; i += lowbit(i)) {
                tree[i] += val;
            }
        }

        // 查询 a[1...x] 的和
        T query(int x) {
            T res = 0;
            for (int i = x; i > 0; i -= lowbit(i)) {
                res += tree[i];
            }
            return res;
        }

        // 查询 a[l...r] 的和
        T query_range(int l, int r) {
            if (l > r) return 0;
            return query(r) - query(l - 1);
        }
    };
    void update(int index, int new_value, vector<int>& nums, FenwickTree<int>& tree) {
        if (nums[index] == new_value) {
            return;
        }
        if (index > 0 && index < nums.size() - 1) {
            if (nums[index] > nums[index - 1] && nums[index] > nums[index + 1]) {
                tree.add(index+1, -1);
            }
            if (new_value > nums[index - 1] && new_value > nums[index + 1]) {
                tree.add(index+1, 1);
            }
        }
        if (index > 1 && nums[index - 1] > nums[index - 2]) {
            if (nums[index - 1] > nums[index]) {
                tree.add(index, -1);
            }
            if (nums[index - 1] > new_value) {
                tree.add(index, 1);
            }
        }
        if (index < nums.size() - 2 && nums[index + 1] > nums[index + 2]) {
            if (nums[index + 1] > nums[index]) {
                tree.add(index + 2, -1);
            }
            if (nums[index + 1] > new_value) {
                tree.add(index + 2, 1);
            }
        }
        nums[index] = new_value;
    }

public:
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        FenwickTree<int> tree(n);
        for (int i = 1; i < n - 1; ++i) {
            if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
                tree.add(i + 1, 1);
            }
        }
        vector<int> answer;
        for (const auto& query : queries) {
            if (query[0] == 1) {
                int l = query[1] + 2, r = query[2];
                answer.push_back(tree.query_range(l, r));
            } else {
                int index = query[1];
                int new_value = query[2];
                // 处理自身和前后元素
                update(index, new_value, nums, tree);
            }
        }
        return answer;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution3187;
int main() {
    Solution solution;
    vector<int> nums = {4,1,4,2,1,5};
    vector<vector<int>> queries = {{2,2,4}, {1, 0, 2}, {1,0,4}};
    vector<int> answer = solution.countOfPeaks(nums, queries);
    for (int i : answer) {
        cout << i << endl;
    }
    return 0;
}