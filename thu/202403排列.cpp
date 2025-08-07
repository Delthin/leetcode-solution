//
// Created by lisiyi on 25-8-3.
//

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void enumerate(int n, vector<pair<int, int>>& checks) {
    vector<int> permutation(n);
    iota(permutation.begin(), permutation.end(), 1);
    bool special_judge_3 = true;
    for (auto& check : checks) {
        if (check.first != check.second) {
            special_judge_3 = false;
            break;
        }
    }
    bool flag =false;
    if (special_judge_3) {
        flag = true;
    }
    if (!flag) {
        do {
            bool valid = true;
            for (int i = 0; i < checks.size(); i++) {
                int p = checks[i].first, x = checks[i].second;
                int cnt = 0;
                for (int j = 0; j < p; j++) {
                    if (permutation[j] <= permutation[p - 1]) {
                        cnt++;
                    }
                }
                if (cnt != x) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                flag = true;
                break;
            }
        } while (next_permutation(permutation.begin(), permutation.end()));
    }
    if (flag) {
        for (int i = 0; i < n; i++) {
            cout << permutation[i];
            if (i != n - 1) {
                cout << " ";
            }
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    Node *l=nullptr, *r=nullptr;
    int val=0, sz=1; // val: 节点值, sz: 子树大小
    unsigned pri;    // 随机优先级

    explicit Node(int v) : val(v), pri(rng()) {
    }
};

int size(Node* t) { return t ? t->sz : 0; }

void pull(Node* t) { // pushup: 从子节点更新父节点信息
    if (!t) return;
    t->sz = 1 + size(t->l) + size(t->r);
    // --- 扩展点: 在此更新聚合信息 (如 sum, max_v) ---
    // t->sum = t->val + (t->l ? t->l->sum : 0) + (t->r ? t->r->sum : 0);
}

void push(Node* t) { // pushdown: 下传懒标记

}

// --- 核心操作: 分裂与合并 ---

// 按权值分裂
void split_by_val(Node* t, int v, Node*& a, Node*& b) {
    if (!t) { a = b = nullptr; return; }
    push(t);
    if (t->val <= v) {
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

// 按权值操作 (用于维护有序集合，如Splay)
void insert_val(Node*& root, int val) {
    Node *a, *b;
    split_by_val(root, val, a, b);
    root = merge(merge(a, new Node(val)), b);
}

void erase_val(Node*& root, int val) {
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

Node* get_max_node(Node* root) {
    while (root->r) {
        root = root->r;
    }
    return root;
}

void solve (int n, vector<pair<int, int>>& checks) {
    // 对每一步，确立a[p_i] = kth_smallest(available_nums,p_k)，然后和上一轮的空隙用可用最大数字填充
    vector<int> permutation(n, -1);
    Node* root = nullptr;
    for (int i = 1; i <= n; i++) {
        insert_val(root, i);
    }
    int prev_p = n + 1;
    for (const auto& check : checks) {
        int p = check.first, x = check.second;
        Node* kth_node = get_kth_node(root, x);
        if (!kth_node) {
            cout << -1 << endl;
            return;
        }
        int val = kth_node->val;
        permutation[p - 1] = val;
        erase_val(root, val);
        for (int i = prev_p - 1; i >= p; i--) {
            if (permutation[i] == -1) {
                permutation[i] = get_max_node(root)->val;
                erase_val(root, permutation[i]);
            }
        }
        prev_p = p;
    }
    for (int i = prev_p - 1; i >= 0; i--) {
        if (permutation[i] == -1) {
            permutation[i] = get_max_node(root)->val;
            erase_val(root, permutation[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << permutation[i];
        if (i != n - 1) {
            cout << " ";
        }
    }
    cout << endl;
}

int main() {
    int T;
    cin >> T;
    while (T --) {
        int n, k;
        cin >> n >> k;
        vector<pair<int, int>> checks(k);
        // 每一行有两个数字 p 和 x ，表示下标小于等于 p 的数字中，值小于等于 a_p 的恰好为 x 个，保证每个限制条件中的 p 各不相同。
        // 翻译为a[p] 的值，必须是在最终被放入 a[1]...a[p] 这 p 个位置的所有数字里，排名第 x 小的那个数

        for (int i = 0; i < k; i++) {
            int p, x;
            cin >> p >> x;
            checks[i] = {p, x};
        }
        // 按p从大到小贪心处理
        sort(checks.begin(), checks.end(), greater<>());
        // 预处理一些矛盾情况
        bool preprocess_flag = true;
        for (int i = 0; i < k; i++) {
            int p = checks[i].first, x = checks[i].second;
            if (x > p) {
                preprocess_flag = false;
                break;
            }
        }
        if (!preprocess_flag) {
            cout << -1 << endl;
            continue;
        }

        // enumerate(n, checks); // 暴力枚举
        solve(n, checks);
    }
    return 0;
}