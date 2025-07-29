/**
给你一个下标从 0 开始的正整数数组 heights ，其中 heights[i] 表示第 i 栋建筑的高度。 

 如果一个人在建筑 i ，且存在 i < j 的建筑 j 满足 heights[i] < heights[j] ，那么这个人可以移动到建筑 j 。 

 给你另外一个数组 queries ，其中 queries[i] = [ai, bi] 。第 i 个查询中，Alice 在建筑 ai ，Bob 在建筑 bi 。
 

 请你能返回一个数组 ans ，其中 ans[i] 是第 i 个查询中，Alice 和 Bob 可以相遇的 最左边的建筑 。如果对于查询 i ，Alice 和 
Bob 不能相遇，令 ans[i] 为 -1 。 

 

 示例 1： 

 
输入：heights = [6,4,8,5,2,7], queries = [[0,1],[0,3],[2,4],[3,4],[2,2]]
输出：[2,5,-1,5,2]
解释：第一个查询中，Alice 和 Bob 可以移动到建筑 2 ，因为 heights[0] < heights[2] 且 heights[1] < 
heights[2] 。
第二个查询中，Alice 和 Bob 可以移动到建筑 5 ，因为 heights[0] < heights[5] 且 heights[3] < heights[
5] 。
第三个查询中，Alice 无法与 Bob 相遇，因为 Alice 不能移动到任何其他建筑。
第四个查询中，Alice 和 Bob 可以移动到建筑 5 ，因为 heights[3] < heights[5] 且 heights[4] < heights[
5] 。
第五个查询中，Alice 和 Bob 已经在同一栋建筑中。
对于 ans[i] != -1 ，ans[i] 是 Alice 和 Bob 可以相遇的建筑中最左边建筑的下标。
对于 ans[i] == -1 ，不存在 Alice 和 Bob 可以相遇的建筑。
 

 示例 2： 

 
输入：heights = [5,3,8,2,6,1,4,6], queries = [[0,7],[3,5],[5,2],[3,0],[1,6]]
输出：[7,6,-1,4,6]
解释：第一个查询中，Alice 可以直接移动到 Bob 的建筑，因为 heights[0] < heights[7] 。
第二个查询中，Alice 和 Bob 可以移动到建筑 6 ，因为 heights[3] < heights[6] 且 heights[5] < heights[
6] 。
第三个查询中，Alice 无法与 Bob 相遇，因为 Bob 不能移动到任何其他建筑。
第四个查询中，Alice 和 Bob 可以移动到建筑 4 ，因为 heights[3] < heights[4] 且 heights[0] < heights[
4] 。
第五个查询中，Alice 可以直接移动到 Bob 的建筑，因为 heights[1] < heights[6] 。
对于 ans[i] != -1 ，ans[i] 是 Alice 和 Bob 可以相遇的建筑中最左边建筑的下标。
对于 ans[i] == -1 ，不存在 Alice 和 Bob 可以相遇的建筑。
 

 

 提示： 

 
 1 <= heights.length <= 5 * 10⁴ 
 1 <= heights[i] <= 10⁹ 
 1 <= queries.length <= 5 * 10⁴ 
 queries[i] = [ai, bi] 
 0 <= ai, bi <= heights.length - 1 
 

 Related Topics 栈 树状数组 线段树 数组 二分查找 单调栈 堆（优先队列） 👍 57 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2940{
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
    int N = 0;
    SegTree_NoLazy SEGT; // 实例化核心逻辑
    vector<SegTree_NoLazy::Node> tr;
    vector<long long> initial_arr;

    // 从左右子节点更新父节点
    void pushup(int u) {
        tr[u] = SEGT.merge(tr[u << 1], tr[u << 1 | 1]);
    }

    // 构建线段树
    // u: 当前节点编号, l,r: 当前节点表示的区间
    void build(int u, int l, int r) {
        if (l == r) {
            tr[u] = {initial_arr[l]}; // 叶子节点直接从原始数组赋值
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

    int query_binary(int u, int l, int r, int L, int v) {
        // 二分递归查询区间 [L, N - 1] 中，大于v的最左建筑
        if (tr[u].max_v <= v) {
            return -1; // 如果区间内没有大于v的建筑，返回-1
        }
        if (l == r) {
            return l; // 找到最左边的建筑
        }
        int mid = l + r >> 1;
        if (L <= mid) { // 如果查询区间左端点在左子树
            // 检查左子树是否有大于等于v的建筑
            int pos = query_binary(u << 1, l, mid, L, v);
            if (pos != -1) {
                return pos;
            }
        }
        return query_binary(u << 1 | 1, mid + 1, r, L, v);
    }
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        N = heights.size();
        initial_arr = vector<long long>(heights.begin(), heights.end());
        tr = vector<SegTree_NoLazy::Node>(N * 4);
        build(1, 0, N - 1);
        vector<int> ans;
        for (auto& query: queries) {
            int a = query[0], b = query[1];
            if (a > b) swap(a, b);// 确保 a <= b
            if (a == b || heights[a] < heights[b]) {
                ans.push_back(b);
                continue;
            }
            ans.push_back(query_binary(1, 0, N - 1, b, heights[a]));
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2940;
int main() {
    Solution solution;

    return 0;
}