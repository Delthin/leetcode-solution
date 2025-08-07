//
// Created by lisiyi on 25-8-5.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node *l=nullptr, *r=nullptr;
    ll level=0;
    int sz=1; // level: 飞船等级, sz: 子树大小（用于查询中位数）
    unsigned pri;    // 随机优先级
    ll lazy_add=0;
    explicit Node(ll v) : level(v), pri(rng()) {

    }
};

int size(Node* t) { return t ? t->sz : 0; }

void pull(Node* t) { // pushup: 从子节点更新父节点信息
    if (!t) return;
    t->sz = 1 + size(t->l) + size(t->r);
}

void push(Node* t) {
    if (!t || t->lazy_add == 0) return; // 优化：懒标记为0就不用下传
    t->level += t->lazy_add;
    if (t->l) t->l->lazy_add += t->lazy_add;
    if (t->r) t->r->lazy_add += t->lazy_add;
    t->lazy_add = 0;
}

// --- 核心操作: 分裂与合并 ---
// 按位序分裂 (前 k 个)
void split_by_rank(Node* t, int k, Node*& a, Node*& b) {
    if (!t) { a = b = nullptr; return; }
    push(t);
    if (size(t->l) >= k) {
        b = t; split_by_rank(t->l, k, a, b->l); pull(b);
    } else {
        a = t; split_by_rank(t->r, k - size(t->l) - 1, a->r, b); pull(a);
    }
}

// 按权值分裂
void split_by_val(Node* t, ll v, Node*& a, Node*& b) {
    if (!t) { a = b = nullptr; return; }
    push(t);
    if (t->level <= v) {
        a = t; split_by_val(t->r, v, a->r, b); pull(a);
    } else {
        b = t; split_by_val(t->l, v, a, b->l); pull(b);
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

void erase_by_rank(Node*& root, int pos) {
    Node *a, *b, *c;
    split_by_rank(root, pos - 1, a, b);
    split_by_rank(b, 1, b, c); // b 就是要被删除的节点
    root = merge(a, c);
    // if (b) delete b; // 若需手动管理内存
}

// 按权值操作 (用于维护有序集合，如Splay)
void insert_val(Node*& root, ll val) {
    Node *a, *b;
    split_by_val(root, val, a, b);
    root = merge(merge(a, new Node(val)), b);
}

void erase_val(Node*& root, ll val) {
    Node *a, *b, *c;
    split_by_val(root, val, a, c);
    split_by_val(a, val - 1, a, b); // b中存的是所有值为val的节点
    if (b) b = merge(b->l, b->r); // 删除一个
    root = merge(merge(a, b), c);
}

Node* get_kth_node(Node* t, int k) {
    if (!t || k <= 0 || k > size(t)) return nullptr;
    while(t) {
        push(t);
        int left_sz = size(t->l);
        if (k == left_sz + 1) break;
        if (k <= left_sz) t = t->l;
        else { k -= left_sz + 1; t = t->r; }
    }
    return t;
}

ll get_node_val(Node* node) {
    push(node);
    return node->level;
}

Node* union_trees(Node* a, Node* b) {
    if (!a || !b) return a ? a : b;

    // 确保 a 的优先级更高
    if (a->pri < b->pri) swap(a, b);

    push(a);

    Node *b_left, *b_right;
    // 用 a 的根节点的 level 去分割 b
    split_by_val(b, a->level, b_left, b_right);

    // 递归地合并子树
    a->l = union_trees(a->l, b_left);
    a->r = union_trees(a->r, b_right);

    pull(a); // 更新 a 的 size
    return a;
}

int n;

vector<Node*> roots;

void op1() {
    // 造船：给出正整数 x,v，建造一艘等级为 v 的飞船，加入到第 x 支舰队中；
    int x, v;
    cin >> x >> v;
    Node* root = roots[x];
    insert_val(root, v);
    roots[x] = root;
}

void op2() {
    // 训练：给出正整数 x,v，对第 x 支舰队进行训练，使它的所有飞船等级上升 v ；
    int x, v;
    cin >> x >> v;
    Node* root = roots[x];
    if (root) (root)->lazy_add += v;
    roots[x] = root;
}

void op3() {
    // 移动：给出正整数 x,y，将第 x 支舰队里中位数等级的飞船移动到第 y 支舰队中。如果第 x 支舰队是空的，则这个操作不产生效果。如果第 x 支舰队里中位数等级的飞船不止一个，则移动其中的任意一个；
    int x, y;
    cin >> x >> y;
    Node* x_root = roots[x], *y_root = roots[y];
    if (!x_root) return;
    int mid_rank = (x_root->sz + 1) / 2;
    Node* mid_node = get_kth_node(x_root, mid_rank);
    ll mid_val = get_node_val(mid_node);
    // 这里要按位置移动，因为可能有多个相同值（其实效果也一样）
    erase_by_rank(x_root, mid_rank);
    insert_val(y_root, mid_val);
    roots[x] = x_root;
    roots[y] = y_root;
}

void op4() {
    // 查询：给出正整数 x，询问第 x 支舰队中飞船等级的中位数。如果第 x 支舰队是空的，则应当回答 0 ；
    int x;
    cin >> x;
    Node* root = roots[x];
    if (!root) {
        cout << 0 << endl;
        return;
    }
    int mid_rank = (root->sz + 1) / 2;
    Node* mid_node = get_kth_node(root, mid_rank);
    cout << mid_node->level << endl;
}

void op5() {
    // 合并：给出正整数 x,y，将第 x 支舰队的所有飞船转移到第 y 支舰队中，第 x 支舰队变为空的；
    int x, y;
    cin >> x >> y;
    Node* x_root = roots[x];
    Node* y_root = roots[y];
    // 甚至可以不用启发式合并
    // if ((*x_root)->sz > (*y_root)->sz) {
    //     swap(*x_root, *y_root);
    // }
    // while (*x_root) {
    //     ll root_level = get_node_val(*x_root);
    //     erase_val(*x_root, root_level);
    //     insert_val(*y_root, root_level);
    // }
    roots[y] = union_trees(y_root, x_root);
    roots[x] = nullptr;
}

void op6() {
    // 删除：给出正整数 x,v，将第 x 支舰队中等级不超过 v 的飞船删除。
    int x, v;
    cin >> x >> v;
    Node* root = roots[x];
    if (!root) return;
    Node *a, *b;
    split_by_val(root, v, a, b);
    roots[x] = b;
}

int main() {
    int q;
    cin >> n >> q;
    roots.resize(n + 1);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) op1();
        else if (op == 2) op2();
        else if (op == 3) op3();
        else if (op == 4) op4();
        else if (op == 5) op5();
        else op6();
    }
    return 0;
}