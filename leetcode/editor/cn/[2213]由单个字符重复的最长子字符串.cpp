/**
给你一个下标从 0 开始的字符串 s 。另给你一个下标从 0 开始、长度为 k 的字符串 queryCharacters ，一个下标从 0 开始、长度也是 k 
的整数 下标 数组 queryIndices ，这两个都用来描述 k 个查询。 

 第 i 个查询会将 s 中位于下标 queryIndices[i] 的字符更新为 queryCharacters[i] 。 

 返回一个长度为 k 的数组 lengths ，其中 lengths[i] 是在执行第 i 个查询 之后 s 中仅由 单个字符重复 组成的 最长子字符串 的 长
度 。 

 

 示例 1： 

 
输入：s = "babacc", queryCharacters = "bcb", queryIndices = [1,3,3]
输出：[3,3,4]
解释：
- 第 1 次查询更新后 s = "bbbacc" 。由单个字符重复组成的最长子字符串是 "bbb" ，长度为 3 。
- 第 2 次查询更新后 s = "bbbccc" 。由单个字符重复组成的最长子字符串是 "bbb" 或 "ccc"，长度为 3 。
- 第 3 次查询更新后 s = "bbbbcc" 。由单个字符重复组成的最长子字符串是 "bbbb" ，长度为 4 。
因此，返回 [3,3,4] 。 

 示例 2： 

 
输入：s = "abyzz", queryCharacters = "aa", queryIndices = [2,1]
输出：[2,3]
解释：
- 第 1 次查询更新后 s = "abazz" 。由单个字符重复组成的最长子字符串是 "zz" ，长度为 2 。
- 第 2 次查询更新后 s = "aaazz" 。由单个字符重复组成的最长子字符串是 "aaa" ，长度为 3 。
因此，返回 [2,3] 。
 

 

 提示： 

 
 1 <= s.length <= 10⁵ 
 s 由小写英文字母组成 
 k == queryCharacters.length == queryIndices.length 
 1 <= k <= 10⁵ 
 queryCharacters 由小写英文字母组成 
 0 <= queryIndices[i] < s.length 
 

 Related Topics 线段树 数组 字符串 有序集合 👍 44 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution2213{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
 struct SegTree_NoLazy {
    // 1. 节点定义
    struct Node {
        // 节点需要维护的值，例如区间和、最大值等
        int max_len;
        int prefix;
        int suffix;
    };

};
SegTree_NoLazy SEGT; // 实例化核心逻辑
    vector<SegTree_NoLazy::Node> tr;
    string initial_arr;

    // 从左右子节点更新父节点
    void pushup(int u, int l, int r) {
        int mid = l + r >> 1;
        // 左半边到initial_arr[mid]为止
        // 右半边从initial_arr[mid + 1]开始
        tr[u].prefix = tr[u << 1].prefix;
        tr[u].suffix = tr[u << 1 | 1].suffix;
        tr[u].max_len = max(tr[u << 1].max_len, tr[u << 1 | 1].max_len);
        // 合并两个子区间时，如果前一个区间（记作 a）的末尾字符等于后一个区间（记作 b）的第一个字符，则可以合并这两个区间：
        // 如果 a 的 suf 等于 a 的长度，那么就可以把 b 的 pre 加到 a 的 pre 上；
        // 如果 b 的 pre 等于 b 的长度，那么就可以把 a 的 suf 加到 b 的 suf 上；
        // a.suf + b.pre 可以考虑成为合并后的区间的 max。
        if (initial_arr[mid] == initial_arr[mid + 1]) {
            if (tr[u << 1].suffix == mid - l + 1) tr[u].prefix += tr[u << 1 | 1].prefix;
            if (tr[u << 1 | 1].prefix == r - mid) tr[u].suffix += tr[u << 1].suffix;
            tr[u].max_len = max(tr[u].max_len, tr[u << 1].suffix + tr[u << 1 | 1].prefix);
        }
 }

 // 构建线段树
 // u: 当前节点编号, l,r: 当前节点表示的区间
 void build(int u, int l, int r) {
     if (l == r) {
         tr[u] = {1, 1, 1}; // 叶子节点直接从原始数组赋值
         return;
     }
     int mid = l + r >> 1;
     build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u, l, r);
    }

    // 单点修改
    // u: 当前节点, [l,r]: 当前节点区间, p: 目标修改点的下标, val: 新的值
    void update(int u, int l, int r, int p, char val) {
        if (l == r) {
            initial_arr[p] = val; // 更新原始数组
            return;
        }
        int mid = l + r >> 1;
        if (p <= mid) { // 目标点在左子树
            update(u << 1, l, mid, p, val);
        } else { // 目标点在右子树
            update(u << 1 | 1, mid + 1, r, p, val);
        }
        pushup(u, l, r); // 子节点更新后，回溯时更新父节点
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        initial_arr = s;
        int n = s.size();
        tr.resize(n * 4);
        build(1, 0, n - 1);
        vector<int> res;
        for (int i = 0; i < queryCharacters.size(); ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            res.push_back(tr[1].max_len);
        }
        return res;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution2213;
int main() {
    Solution solution;
    string s = "babacc";
    string queryCharacters = "bcb";
    vector<int> queryIndices = {1, 3, 3};
    vector<int> result = solution.longestRepeating(s, queryCharacters, queryIndices);
    for (int i = 0; i < result.size(); ++i) {
        cout << result[i] << endl;
    }
    return 0;
}