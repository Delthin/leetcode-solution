// //
// // Created by lisiyi on 25-8-2.
// //
// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;
//
// struct Block {
//     ll w, c;
//     Block *pre, *nxt;
// };
//
// struct MyStack {
//     vector<Block> blocks;
//     ll sum = 0;
//
//     void add(ll w, ll c) {
//         // 可以进行合并
//         if (!blocks.empty()) {
//             Block& b = blocks.back();
//             if (b.w == w) {
//                 b.c += c;
//             } else {
//                 blocks.push_back({w, c});
//             }
//         } else {
//             blocks.push_back({w, c});
//         }
//         sum += w * c;
//     }
//
//     void add(Block& block) {
//         if (!blocks.empty()) {
//             Block& b = blocks.back();
//             if (b.w == block.w) {
//                 b.c += block.c;
//             } else {
//                 blocks.push_back(block);
//             }
//         } else {
//             blocks.push_back(block);
//         }
//         sum += block.w * block.c;
//     }
// };
//
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int n, m;
//     cin >> n >> m;
//     vector<MyStack> stacks(n + 1);
//     while (m--) {
//         int op;
//         cin >> op;
//         if (op == 1) {
//             ll x, w, c;
//             cin >> x >> w >> c;
//             MyStack& ms = stacks[x];
//             ms.add(w, c);
//             cout << ms.sum << endl;
//         } else if (op == 2) {
//             ll x, c;
//             cin >> x >> c;
//             MyStack& ms = stacks[x];
//             ll sum = 0;
//             while (c > 0) {
//                 Block& b = ms.blocks.back();
//                 if (b.c > c) {
//                     b.c -= c;
//                     sum += b.w * c;
//                     ms.sum -= b.w * c;
//                     break;
//                 } else {
//                     sum += b.w * b.c;
//                     c -= b.c;
//                     ms.sum -= b.w * b.c;
//                     ms.blocks.pop_back();
//                 }
//             }
//             cout << sum << endl;
//         } else if (op == 3) {
//             int x, y;
//             cin >> x >> y;
//             MyStack& msx = stacks[x];
//             MyStack& msy = stacks[y];
//             for (auto it = msx.blocks.rbegin(); it != msx.blocks.rend(); ++it) {
//                 msy.add(*it);
//             }
//             msx.blocks.clear();
//             msx.blocks.shrink_to_fit();
//             msx.sum = 0;
//             cout << msy.sum << endl;
//         }
//     }
//     return 0;
// }
// 核心前提条件
// merge(L, R) 操作有一个绝对的前提：在序列意义上，L 树中的所有元素都必须排在 R 树中所有元素的前面。
//
// 当我们执行 root = merge(root, new_node) 时，root 代表整个旧序列，new_node 是要追加到末尾的新元素，这个前提自然满足。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node *l=nullptr, *r=nullptr;
    ll val=0, sz=0; // val: 节点权重, sz: 子树含有元素数量
    ll c; // 当前节点包含的元素数量
    unsigned pri;    // 随机优先级
    bool rev_tag=false; // 翻转懒标记
    ll sum = 0;

    explicit Node(int w, ll c) : val(w), c(c), sz(c), pri(rng()), sum(w * c) {
    }
};

ll size(Node* t) { return t ? t->sz : 0; }

void pull(Node* t) { // pushup: 从子节点更新父节点信息
    if (!t) return;
    t->sz = t->c + size(t->l) + size(t->r);
    t->sum = t->val * t->c;
    if (t->l) t->sum += t->l->sum;
    if (t->r) t->sum += t->r->sum;
}

void apply_rev(Node* t) {
    if (!t) return;
    // 1. 更新/翻转懒标记
    t->rev_tag ^= 1;
    // 2. 立刻应用结构变化
    swap(t->l, t->r);
}

void push(Node* t) { // pushdown: 下传懒标记
    if (!t || !t->rev_tag) return;
    apply_rev(t->l);
    apply_rev(t->r);
    t->rev_tag = false;
}

// --- 核心操作: 分裂与合并 ---
// 按数量分裂 (后 k个)（栈顶的k个）
void split_by_rank(Node* t, ll k, Node*& a, Node*& b) {
    // a返回分裂除去后k个元素的树，b返回后k个元素的树
    if (!t) { a = b = nullptr; return; }
    push(t);
    if (size(t->r) >= k) {
        // 右子树的元素数量大于等于k，说明要分裂的元素在右子树
        a = t; split_by_rank(t->r, k, a->r, b); pull(a);
    } else if (size(t->r) + t->c >= k) {
        // 右子树的元素数量加上当前节点的元素数量大于等于k，说明要分裂的元素在当前节点
        t->c = t->c - (k - size(t->r));
        // ll b_c = k - size(t->r);
        // Node* origin_r = t->r;
        a = t;
        a->r = nullptr;
        pull(a);
        // b = new Node(t->val, b_c);
        // b->r = origin_r;
        // pull(b);
    } else {
        // 右子树的元素数量加上当前节点的元素数量小于k，说明要分裂的元素在左子树
        b = t; split_by_rank(t->l, k - size(t->r) - t->c, a, b->l); pull(b);
    }
}

Node* merge(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;
    if (a->pri < b->pri) { // 设 pri 越小优先级越高
        push(a); a->r = merge(a->r, b); pull(a); return a;
    } else {
        push(b); b->l = merge(a, b->l); pull(b); return b;
    }
}

void reverse_lazy(Node*& root) {
    if (!root) return;
    apply_rev(root);
}

struct MyStack {
    Node* root = nullptr;

    ll push(ll w, ll c) {
        root = merge(root, new Node(w, c));
        return root->sum;
    }
    ll pop(ll c) {
        Node* a, * b;
        ll ori_sum = root->sum;
        split_by_rank(root, c, a, b);
        root = a;
        return ori_sum - (root ? root->sum : 0);
    }
    ll add_from_x(MyStack& x) {
        ll y_sum = root ? root->sum : 0;
        if (!x.root) return y_sum;
        ll x_sum = x.root->sum;
        reverse_lazy(x.root);
        root = merge(root, x.root);
        x.root = nullptr;
        return x_sum + y_sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<MyStack> stacks(n + 1);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            ll x, w, c;
            cin >> x >> w >> c;
            MyStack& ms = stacks[x];
            cout << ms.push(w, c) << endl;
        } else if (op == 2) {
            ll x, c;
            cin >> x >> c;
            MyStack& ms = stacks[x];
            cout << ms.pop(c) << endl;
        } else if (op == 3) {
            int x, y;
            cin >> x >> y;
            MyStack& msx = stacks[x];
            MyStack& msy = stacks[y];
            cout << msy.add_from_x(msx) << endl;
        }
    }
    return 0;
}

