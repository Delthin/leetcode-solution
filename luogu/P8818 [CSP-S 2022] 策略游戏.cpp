#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node {
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    int min_abs_plus = INT_MAX;
    int min_abs_minus = INT_MAX;
};

Node merge(const Node &a, const Node &b)
{
    Node res;
    res.min_val = min(a.min_val, b.min_val);
    res.max_val = max(a.max_val, b.max_val);
    res.min_abs_plus = min(a.min_abs_plus, b.min_abs_plus);
    res.min_abs_minus = min(a.min_abs_minus, b.min_abs_minus);
    return res;
}

struct SegTree {
    vector<Node> tr;
    vector<int> arr;

    SegTree(vector<int> a, int n) {
        tr.resize(4 * n + 1);
        arr = a;
        build(1, 1, n);
    }

    void pushup(int u)
    {
        tr[u] = merge(tr[u << 1], tr[u << 1 | 1]);
    }

    void build(int u, int l, int r)
    {
        if (l == r) {
            int min_abs_plus = INT_MAX;
            int min_abs_minus = INT_MAX;
            if (arr[l] > 0) {
                min_abs_plus = arr[l];
            } else if (arr[l] < 0) {
                min_abs_minus = -arr[l];
            } else {
                min_abs_plus = 0;
                min_abs_minus = 0;
            }
            tr[u] = {arr[l], arr[l], min_abs_plus, min_abs_minus};
            return;
        }
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pushup(u);
    }

    Node query(int u, int l, int r, int L, int R)
    {
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
        Node left = query(u << 1, l, mid, L, R);
        Node right = query(u << 1 | 1, mid + 1, r, L, R);
        return merge(left, right);
    }
};

int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> A(n + 1, 0);
    for (int i = 1; i <= n ;i++) {
        cin >> A[i];
    }
    SegTree row(A, n);
    vector<int> B(m + 1, 0);
    for (int i = 1; i <= m; i++) {
        cin >> B[i];
    }
    SegTree col(B, m);
    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        ll ans = LONG_LONG_MIN;
        Node row_node = row.query(1, 1, n, l1, r1);
        Node col_node = col.query(1, 1, m, l2, r2);
        int row_min = row_node.min_val;
        int row_max = row_node.max_val;
        int col_min = col_node.min_val;
        int col_max = col_node.max_val;
        int row_min_abs_plus = row_node.min_abs_plus;
        int row_min_abs_minus = row_node.min_abs_minus;
        // 分类讨论, A选正还是选负
        if (row_max >= 0) {
            ans = max({ans, (ll)row_max * col_min, (ll)row_min_abs_plus * col_min});
        }
        if (row_min <= 0) {
            ans = max({ans, (ll)row_min * col_max, -(ll)row_min_abs_minus * col_max});
        }
        // if (col_min <=0 && col_max <= 0) {
        //     // 行选正选负
        //     if (row_max >= 0) {
        //         ans = max(ans, (ll)row_min_abs_plus * col_min);
        //     }
        //     if (row_min <= 0) {
        //         ans = max(ans, (ll)row_min * col_max);
        //     }
        // } else if (col_min >= 0 && col_max >= 0) {
        //     // 行选正选负
        //     if (row_max >= 0) {
        //         ans = max(ans, (ll)row_max * col_min);
        //     }
        //     if (row_min <= 0) {
        //         ans = max(ans, -(ll)row_min_abs_minus * col_max);
        //     }
        // } else {
        //     // 列里有正有负
        //     if (row_max >= 0) {
        //         ans = max(ans, (ll)row_min_abs_plus * col_min);
        //     }
        //     if (row_min <= 0) {
        //         ans = max(ans, -(ll)row_min_abs_minus * col_max);
        //     }
        // }
        cout << ans << endl;
    }
    return 0;
} 