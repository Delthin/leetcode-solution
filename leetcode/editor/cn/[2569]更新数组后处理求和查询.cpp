/**
给你两个下标从 0 开始的数组 nums1 和 nums2 ，和一个二维数组 queries 表示一些操作。总共有 3 种类型的操作： 

 
 操作类型 1 为 queries[i] = [1, l, r] 。你需要将 nums1 从下标 l 到下标 r 的所有 0 反转成 1 并且所有 1 反转成 
0 。l 和 r 下标都从 0 开始。 
 操作类型 2 为 queries[i] = [2, p, 0] 。对于 0 <= i < n 中的所有下标，令 nums2[i] = nums2[i] + 
nums1[i] * p 。 
 操作类型 3 为 queries[i] = [3, 0, 0] 。求 nums2 中所有元素的和。 
 

 请你返回一个 数组，包含 所有第三种操作类型 的答案。 

 

 示例 1： 

 
输入：nums1 = [1,0,1], nums2 = [0,0,0], queries = [[1,1,1],[2,1,0],[3,0,0]]
输出：[3]
解释：第一个操作后 nums1 变为 [1,1,1] 。第二个操作后，nums2 变成 [1,1,1] ，所以第三个操作的答案为 3 。所以返回 [3] 。
 

 示例 2： 

 
输入：nums1 = [1], nums2 = [5], queries = [[2,0,0],[3,0,0]]
输出：[5]
解释：第一个操作后，nums2 保持不变为 [5] ，所以第二个操作的答案是 5 。所以返回 [5] 。
 

 

 提示： 

 
 1 <= nums1.length,nums2.length <= 10⁵ 
 nums1.length = nums2.length 
 1 <= queries.length <= 10⁵ 
 queries[i].length = 3 
 0 <= l <= r <= nums1.length - 1 
 0 <= p <= 10⁶ 
 0 <= nums1[i] <= 1 
 0 <= nums2[i] <= 10⁹ 
 

 Related Topics 线段树 数组 👍 113 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2569{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {

 struct SegTree {
    // 1. 节点与标记的定义
    struct Node { long long val; }; // 区间1的数量
    struct Tag  { long long add; }; // 区间翻转次数

    // 2. 节点与标记的初始(单位)值
    Node E_NODE = {0}; // 查询空区间的返回值, 单位元是操作的初始状态，例如加法的0，乘法的1;查询空区间时，会返回 E_NODE
    Tag  E_TAG  = {0}; // 懒标记的初始值, 表示无操作

    // 3. 合并两个子节点信息到父节点 (pushup)
    Node merge(const Node& a, const Node& b) {
        return {a.val + b.val};
    }

    // 4. 合并两个懒标记 (下传时复合) 当一个已有懒标记的节点再次收到新标记时调
    // 参数: a - 节点上旧的标记, b - 新来的标记 返回: 两者复合后的新标记
    Tag compose(const Tag& a, const Tag& b) {
        return {a.add + b.add};
    }

    // 5. 将懒标记应用到节点
    // 参数: n - 要被修改的节点, t - 应用到该节点的标记, len - 该节点的区间长度 返回: 应用标记后节点的新状态
    Node apply(const Node& n, const Tag& t, int len) {
        if (t.add & 1) {
            return {len - n.val};
        }
        return n;
    }

    // 6. 判断标记是否为空/无操作的值 (用于pushdown)
    bool is_empty_tag(const Tag& t) {
        return t.add == 0;
    }
};
SegTree SEGT; // 实例化核心逻辑
vector<SegTree::Node> tr;
vector<SegTree::Tag> lazy;
vector<int> initial_arr;

void apply_tag(int u, int len, const SegTree::Tag& t) {
	// 将懒标记 t 应用到编号为 u 的节点
    tr[u] = SEGT.apply(tr[u], t, len);
    lazy[u] = SEGT.compose(lazy[u], t);
}

void pushup(int u) { // 从左右子节点更新父节点
    tr[u] = SEGT.merge(tr[u << 1], tr[u << 1 | 1]);
}

void pushdown(int u, int len) {
	// 将父节点的懒标记下传给子节点
    if (!SEGT.is_empty_tag(lazy[u])) {
    	// 分别给左右打上标记，再清空父
        apply_tag(u << 1, len - (len / 2), lazy[u]);
        apply_tag(u << 1 | 1, len / 2, lazy[u]);
        lazy[u] = SEGT.E_TAG;
    }
}

void build(int u, int l, int r) {
	// u: 当前节点 l,r: 当前节点表示区间
    lazy[u] = SEGT.E_TAG;
    if (l == r) {
        tr[u] = {initial_arr[l]};
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void update(int u, int l, int r, int L, int R, const SegTree::Tag& t) {
	// u: 当前节点, [l,r]: 当前节点区间, [L,R]: 目标修改区间, t: 修改的标记
    if (L <= l && r <= R) { // 完全覆盖
        apply_tag(u, r - l + 1, t);
        return;
    }
    pushdown(u, r - l + 1);
    int mid = l + r >> 1;
    if (L <= mid) update(u << 1, l, mid, L, R, t);
    if (R > mid) update(u << 1 | 1, mid + 1, r, L, R, t);
    pushup(u);
}

SegTree::Node query(int u, int l, int r, int L, int R) {
	// u: 当前节点, [l,r]: 当前节点区间, [L,R]: 目标查询区间
    if (L <= l && r <= R) return tr[u];
    pushdown(u, r - l + 1);
    int mid = l + r >> 1;
    if (R <= mid) return query(u << 1, l, mid, L, R);
    if (L > mid) return query(u << 1 | 1, mid + 1, r, L, R);
    return SEGT.merge(query(u << 1, l, mid, L, R), query(u << 1 | 1, mid + 1, r, L, R));
}

public:
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        initial_arr = nums1;
        int n = nums1.size();
        tr.resize(n * 4);
        lazy.resize(n * 4);
        build(1, 0, n - 1);
        vector<long long> result;
        long long sum = accumulate(nums2.begin(), nums2.end(), 0LL);
        for (const auto& q : queries) {
            if (q[0] == 1) { // 操作类型 1
                int l = q[1], r = q[2];
                SegTree::Tag t = {1}; // 翻转标记
                update(1, 0, n - 1, l, r, t);
            } else if (q[0] == 2) { // 操作类型 2
                int p = q[1];
                sum += query(1, 0, n - 1, 0, n - 1).val * p;
            } else if (q[0] == 3) { // 操作类型 3
                result.push_back(sum);
            }
        }
        return result;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2569;
int main() {
    Solution solution;

    return 0;
}