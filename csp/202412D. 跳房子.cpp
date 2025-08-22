#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
vector<int> max_kpi;

struct Node {
    int max_val;
    int max_idx;
};
vector<Node> tr;

Node merge(const Node&a, const Node& b) {
    if (a.max_val > b.max_val) {
        return a;
    }
    if (a.max_val < b.max_val) {
        return b;
    }
    if (a.max_idx > b.max_idx) {
        return a;
    }
    return b;
}

void pushup(int u) {
    tr[u] = merge(tr[u <<1], tr[u << 1 | 1]);
}

void build(int u, int l, int r) {
    if (l == r) {
        tr[u] = {max_kpi[l], l};
        return;
    }
    int mid = (l + r) >> 1;
    build(u <<1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

Node query(int u, int l, int r, int L, int R) {
    if (L <= l && r <= R) {
        return tr[u];
    }
    int mid = (l + r) >> 1;
    if (R <= mid) {
        return query(u << 1, l, mid, L, R);
    }
    if (L > mid) {
        return query(u << 1 | 1, mid + 1, r, L, R);
    }
    Node left_res = query(u << 1, l, mid, L, R);
    Node right_res = query(u << 1 | 1, mid + 1, r, L, R);
    return merge(left_res, right_res);
}

int main() {
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> k(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> k[i];
    }
    max_kpi.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int target = i - a[i]; // 跳到i了先后退
        max_kpi[i] = min(n, target + k[target]);// 往i跳，下一步能到的最大位置
    }
    tr.resize(n * 4);
    build(1, 1, n);
    int pos = 1;
    int ans = 0;
    // 贪心，跳到k+i最大的点，在i+1到k+i之间找max_kpi最大的点
    while (pos < n) {
        int max_pos = query(1, 1, n, pos + 1, min(n, pos + k[pos])).max_idx;
        int target = max(1, max_pos - a[max_pos]);
        if (target == pos) {
            ans = -1;
            break;
        }
        ans++;
        pos = target;
    }
    cout << ans << endl;
    return 0;
}