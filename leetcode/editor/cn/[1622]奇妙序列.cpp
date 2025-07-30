/**
请你实现三个 API append，addAll 和 multAll 来实现奇妙序列。 

 请实现 Fancy 类 ： 

 
 Fancy() 初始化一个空序列对象。 
 void append(val) 将整数 val 添加在序列末尾。 
 void addAll(inc) 将所有序列中的现有数值都增加 inc 。 
 void multAll(m) 将序列中的所有现有数值都乘以整数 m 。 
 int getIndex(idx) 得到下标为 idx 处的数值（下标从 0 开始），并将结果对 10⁹ + 7 取余。如果下标大于等于序列的长度，请返回 -
1 。 
 

 

 示例： 

 
输入：
["Fancy", "append", "addAll", "append", "multAll", "getIndex", "addAll", 
"append", "multAll", "getIndex", "getIndex", "getIndex"]
[[], [2], [3], [7], [2], [0], [3], [10], [2], [0], [1], [2]]
输出：
[null, null, null, null, null, 10, null, null, null, 26, 34, 20]

解释：
Fancy fancy = new Fancy();
fancy.append(2);   // 奇妙序列：[2]
fancy.addAll(3);   // 奇妙序列：[2+3] -> [5]
fancy.append(7);   // 奇妙序列：[5, 7]
fancy.multAll(2);  // 奇妙序列：[5*2, 7*2] -> [10, 14]
fancy.getIndex(0); // 返回 10
fancy.addAll(3);   // 奇妙序列：[10+3, 14+3] -> [13, 17]
fancy.append(10);  // 奇妙序列：[13, 17, 10]
fancy.multAll(2);  // 奇妙序列：[13*2, 17*2, 10*2] -> [26, 34, 20]
fancy.getIndex(0); // 返回 26
fancy.getIndex(1); // 返回 34
fancy.getIndex(2); // 返回 20
 

 

 提示： 

 
 1 <= val, inc, m <= 100 
 0 <= idx <= 10⁵ 
 总共最多会有 10⁵ 次对 append，addAll，multAll 和 getIndex 的调用。 
 

 Related Topics 设计 线段树 数学 👍 92 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1622{
//leetcode submit region begin(Prohibit modification and deletion)
class Fancy {
    static const long long P = 1e9 + 7;
    struct SegTree {
        struct Node { long long sum; };
        struct Tag  { long long mul, add; };
        Node E_NODE = {0};
        Tag  E_TAG  = {1, 0}; // 乘法单位元1，加法单位元0
        Node merge(const Node& a, const Node& b) { return {(a.sum + b.sum) % P}; }
        // 新标记t(mul2,add2)作用于旧标记lz(mul1,add1)
        // lz -> lz*t
        Tag compose(const Tag& lz, const Tag& t) {
            return {(lz.mul * t.mul) % P, (lz.add * t.mul + t.add) % P};
        }
        // 标记t(mul,add)作用于节点n
        Node apply(const Node& n, const Tag& t, int len) {
            return {(n.sum * t.mul + (long long)len * t.add) % P};
        }
        bool is_empty_tag(const Tag& t) { return t.mul == 1 && t.add == 0; }
    };
    SegTree SEGT; // 实例化核心逻辑
    vector<SegTree::Node> tr;
    vector<SegTree::Tag> lazy;

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
    int count;
    const int n = 100000;
public:
    Fancy() {
        tr.resize(n << 2, SEGT.E_NODE);
        lazy.resize(n << 2, SEGT.E_TAG);
        count = 0;
    }
    
    void append(int val) {
        update(1, 0, n - 1, count, count, {1, val});
        count++;
    }
    
    void addAll(int inc) {
        if (count == 0) return;
        update(1, 0, n - 1, 0, count - 1, {1, inc});
    }
    
    void multAll(int m) {
        if (count == 0) return;
        update(1, 0, n - 1, 0, count - 1, {m, 0});
    }
    
    int getIndex(int idx) {
        if (idx >= count) return -1;
        return query(1, 0, n - 1, idx, idx).sum;
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1622;
int main() {
    Solution solution;

    return 0;
}