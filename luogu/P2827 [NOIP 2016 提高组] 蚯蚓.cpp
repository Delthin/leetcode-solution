#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct tuple_q {
    queue<int> ori;
    queue<int> l;
    queue<int> s;
    int u, v, q;
    int delta;

    int pop_max() {
        // {value, queue_index}, 0: ori, 1: l, 2: s
        vector<pair<int, int>> candidates;

        if (!ori.empty()) {
            candidates.emplace_back(ori.front(), 0);
        }
        if (!l.empty()) {
            candidates.emplace_back(l.front(), 1);
        }
        if (!s.empty()) {
            candidates.emplace_back(s.front(), 2);
        }
        if (candidates.empty()) {
            // 或者抛出异常
            return INT_MIN;
        }

        // 找到值最大的元素
        auto max_it = max_element(candidates.begin(), candidates.end());

        int max_val = max_it->first;
        int queue_idx = max_it->second;

        // 从找到的队列中弹出元素
        switch (queue_idx) {
            case 0:
                ori.pop();
                break;
            case 1:
                l.pop();
                break;
            case 2:
                s.pop();
                break;
        }

        return max_val + delta;
    }
};

int main() {
    int n, m, q, u, v, t;
    cin >> n >> m >> q >> u >> v >> t;
    vector<int> a(n);
    for(int i = 0; i < n ; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end(), greater<int>());
    tuple_q que;
    que.u = u;
    que.v = v;
    que.delta = 0;
    que.q = q;
    for(int i = 0; i < n; i++) {
        que.ori.push(a[i]);
    }
    int end_m = m / t * t;
    for (int i = 1; i <= m; i++) {
        int cur_max = que.pop_max();
        if (i % t == 0) {
            cout << cur_max;
            if (i < end_m) {
                cout << " ";
            }
        }
        que.add(cur_max);
    }
    cout << endl;
    int end_nm = (n + m) / t * t;
    for (int i = 1; i <= n + m; i++) {
        int cur_max = que.pop_max();
        if (i % t == 0) {
            cout << cur_max;
            if (i < end_nm) {
                cout << " ";
            }
        }
    }
    cout << endl;
    return 0;
}