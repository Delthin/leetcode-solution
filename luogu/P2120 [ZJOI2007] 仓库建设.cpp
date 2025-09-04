#include <bits/stdc++.h>
using namespace std;
using ll = long long;



int main() {
    int n = 0;
    cin >> n;
    vector<ll> x(n);
    vector<ll> p(n);
    vector<ll> s_p(n + 1);
    vector<ll> c(n);
    vector<ll> s_px(n + 1);
    for (int i = 0; i < n;i ++) {
        cin >> x[i] >> p[i] >> c[i];
        s_p[i + 1] = s_p[i] + p[i];
        s_px[i + 1] = s_px[i] + p[i] * x[i];
    }
    const ll INF = 4e18;
    vector<ll> dp(n + 1, INF);// 表示在i-1处建厂的最小总费用
    auto X = [&] (ll j) {
        return s_p[j];
    };
    auto Y = [&] (ll j) {
        return dp[j] + s_px[j];
    };
    auto K = [&] (ll i) {
        return x[i - 1];
    };
    // K和X都单调增
    deque<int> dq;
    dq.push_back(0);
    dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        // ll min_prev = INF;
        // for (int j = 0; j < i; j++) {
        //     // 上一处在j-1建厂（j=0代表不建）
        //     ll cost = 0;
        //     for (int k = j; k < i - 1; k++) {
        //         cost += p[k] * (x[i - 1] - x[k]);
        //     }
        //     min_prev = min(dp[j] + cost, min_prev);
        // }
        // dp[i] = min_prev + c[i - 1];
        while (dq.size() >= 2) {
            int j1 = dq.front();
            int j2 = dq[1];
            if (Y(j2) - Y(j1) <= K(i) * (X(j2) - X(j1))) {
                dq.pop_front();
            } else {
                break;
            }
        }
        int best_j = dq.front();
        dp[i] = dp[best_j] + x[i - 1] * (s_p[i - 1] - s_p[best_j]) + s_px[best_j] - s_px[i - 1] + c[i - 1];
        while (dq.size() >= 2) {
            int j_last = dq.back();
            int j_prev = dq[dq.size() - 2];
            if ((Y(j_last) - Y(j_prev)) * (X(i) - X(j_last)) >= (Y(i) - Y(j_last)) * (X(j_last) - X(j_prev))) {
                dq.pop_back();
            } else {
                break;
            }
        }
        dq.push_back(i);
    }
    cout << dp[n] << endl;
    return 0;
}