/**
给你一个整数数组 nums 和一个整数 k 。 

 找到 nums 中满足以下要求的最长子序列： 

 
 子序列 严格递增 
 子序列中相邻元素的差值 不超过 k 。 
 

 请你返回满足上述要求的 最长子序列 的长度。 

 子序列 是从一个数组中删除部分元素后，剩余元素不改变顺序得到的数组。 

 

 示例 1： 

 输入：nums = [4,2,1,4,3,4,5,8,15], k = 3
输出：5
解释：
满足要求的最长子序列是 [1,3,4,5,8] 。
子序列长度为 5 ，所以我们返回 5 。
注意子序列 [1,3,4,5,8,15] 不满足要求，因为 15 - 8 = 7 大于 3 。
 

 示例 2： 

 输入：nums = [7,4,5,1,8,12,4,7], k = 5
输出：4
解释：
满足要求的最长子序列是 [4,5,8,12] 。
子序列长度为 4 ，所以我们返回 4 。
 

 示例 3： 

 输入：nums = [1,5], k = 1
输出：1
解释：
满足要求的最长子序列是 [1] 。
子序列长度为 1 ，所以我们返回 1 。
 

 

 提示： 

 
 1 <= nums.length <= 10⁵ 
 1 <= nums[i], k <= 10⁵ 
 

 Related Topics 树状数组 线段树 队列 数组 分治 动态规划 单调队列 👍 95 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2407{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    struct SegTree_NoLazy {
        struct Node { long long max_v; };
        Node E_NODE = {(long long)-1e18}; // 最大值的单位元是负无穷
        Node merge(const Node& a, const Node& b) {
            Node res;
            res.max_v = max(a.max_v, b.max_v);
            return res;
        }
    };
SegTree_NoLazy SEGT; // 实例化核心逻辑
vector<SegTree_NoLazy::Node> tr;

// 从左右子节点更新父节点
void pushup(int u) {
    tr[u] = SEGT.merge(tr[u << 1], tr[u << 1 | 1]);
}

// 构建线段树
// u: 当前节点编号, l,r: 当前节点表示的区间
void build(int u, int l, int r) {
    tr[u] = {0};
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

// 单点修改
// u: 当前节点, [l,r]: 当前节点区间, p: 目标修改点的下标, val: 新的值
void update(int u, int l, int r, int p, long long val) {
    if (l == r) {
        tr[u] = {val}; // 到达叶子节点，直接更新
        return;
    }
    int mid = l + r >> 1;
    if (p <= mid) { // 目标点在左子树
        update(u << 1, l, mid, p, val);
    } else { // 目标点在右子树
        update(u << 1 | 1, mid + 1, r, p, val);
    }
    pushup(u); // 子节点更新后，回溯时更新父节点
}

// 区间查询
// u: 当前节点, [l,r]: 当前节点区间, [L,R]: 目标查询区间
SegTree_NoLazy::Node query(int u, int l, int r, int L, int R) {
    if (L <= l && r <= R) { // 当前区间被查询区间完全覆盖
        return tr[u];
    }
    int mid = l + r >> 1;
    // 根据查询区间与左右子区的关系，决定递归方向
    if (R <= mid) { // 查询区间完全在左子树
        return query(u << 1, l, mid, L, R);
    }
    if (L > mid) { // 查询区间完全在右子树
        return query(u << 1 | 1, mid + 1, r, L, R);
    }
    // 查询区间横跨左右子树，合并两边的结果
    SegTree_NoLazy::Node left_res = query(u << 1, l, mid, L, R);
    SegTree_NoLazy::Node right_res = query(u << 1 | 1, mid + 1, r, L, R);
    return SEGT.merge(left_res, right_res);
}
public:
    int lengthOfLIS(vector<int>& nums, int k) {
        int m = *max_element(nums.begin(), nums.end());
        tr.resize(m * 4);
        build(1, 1, m);
        for (int x: nums) {
            if (x == 1) {// 防止R < L
                update(1, 1, m, 1, 1);
                continue;
            }
            int res = query(1, 1, m, max(1, x - k), x - 1).max_v;
            update(1, 1, m, x, res + 1);
        }
        return query(1, 1, m, 1, m).max_v;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2407;
int main() {
    Solution solution;

    return 0;
}