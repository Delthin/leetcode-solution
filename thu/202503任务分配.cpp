//
// Created by lisiyi on 25-8-3.
//
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> father;
vector<int> times;
vector<int> widget;
vector<vector<int>> adj;

void solve() {
    auto check = [&] (int k) {
        bool success = false;
        for (int i = 1; i <= n; i++) {
            widget[i] += k;
            vector<int> c(n + 1, 0);// 每个点的实际限制
            function<void(int, int)> dfs = [&] (int u, int cur) {
                c[u] = min(widget[u], cur);
                for (int v : adj[u]) {
                    dfs(v, c[u]);
                }
            };
            dfs(1, INT_MAX);
            sort(c.begin(), c.end());
            bool flag = true;
            for (int j = 1; j <= n; j++) {
                if (c[j] < times[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                success = true;
                widget[i] -= k;
                break;
            }
            widget[i] -= k;
        }
        return success;
    };
    int l = -1, r = n - 1;// 二分答案范围0 -> n - 1
    while (l + 1 < r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << endl;
}

void solve_nb() {
    int s[15000001];
    int c[15000001];
    c[1] = widget[1];
    for (int i = 2; i <= n; i++) {
        c[i] = min(widget[i], c[father[i]]);
    }
    for (int i = 1; i <= n; i++) {
        ++s[times[i]], --s[c[i]];
    }
    for (int i = 1; i <= n; i++) {
        s[i] += s[i - 1];
    }
    int mismatch_l = 0, mismatch_r = 0;
    for (int i = 1; i <= n; i++) {
        if (s[i] < 0) {
            mismatch_l = i;
            break;
        }
    }
    if (!mismatch_l) {
        cout << 0 << endl;
        return;
    }
    for (int i = n; i >= 1; i--) {
        if (s[i] < 0) {
            mismatch_r = i;
            break;
        }
    }
    cout << mismatch_r - mismatch_l + 1 << endl;
}


void sub4() {
    // f_i = i - 1 贪心
    // 最上面分最大的
    int res = 0;
    int max_time = 0;
    for (int i = n; i >= 1; i--) {
        if (widget[i] >= times[n - i + 1]) {
            max_time = max(max_time, times[n - i + 1]);
            continue;
        }
        res = times[n - i + 1] - widget[i];
        break;
    }
    cout << res << endl;
}

void sub5() {

}

int main() {
    cin >> n;
    father.resize(n + 1, 0);
    times.resize(n + 1, 0);
    widget.resize(n + 1, 0);
    adj.resize(n + 1);
    bool is_4 = true;
    for (int i = 2; i <= n; i++) {
        cin >> father[i];
        adj[father[i]].push_back(i);
        if (father[i] != i - 1) is_4 = false;
    }
    for (int i = 1; i <= n; i++) {
        cin >> times[i];
    }
    sort(times.begin(), times.end());
    for (int i = 1; i <= n; i++) {
        cin >> widget[i];
    }
    if (n == 1) {
        cout << max(0, times[1] - widget[1]) << endl;
    }
    else if (is_4) {
        sub4();
    } else {
        solve_nb();
    }
    return 0;
}

