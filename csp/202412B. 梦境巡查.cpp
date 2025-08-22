#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
vector<int> a;
vector<int> b;

int main() {
    cin >> n;
    a.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> a[i];
    }
    b.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<int> sum(n + 1, 0);
    sum[0] = a[0] - b[0];
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i] - b[i];
    }
    vector<int> max_after(n + 1, 0);
    max_after[n] = sum[n];
    for (int i = n - 1; i >= 0; i--) {
        max_after[i] = max(max_after[i + 1], sum[i]);
    }
    int before_w = 0;
    for (int i = 1; i <= n; i++) {
        // 走到i为止的最大消耗
        before_w = max(before_w, sum[i - 1]);
        // 从i开始的最大消耗
        int after_w = max_after[i] + b[i];
        int w = max({before_w, after_w, 0});
        cout << w << " \n"[i == n];
    }
    return 0;
}