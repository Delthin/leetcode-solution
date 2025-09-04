#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXSUM = 500005;


int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int first;
    cin >> first;
    a[0] = 0;
    for (int i = 1; i < n; i++) {
        cin >> a[i];
        a[i] -= first;
        // 对数列平移，使第一个数为0，不改变方差
    }
    // 对每个数操作等价于交换差分
    // 单谷时答案最小，所以每次操作可以将差分放在低谷的左或右边
    vector<ll> d(n - 1, 0);
    for (int i = 0; i < n - 1; i++) {
        d[i] = a[i + 1] - a[i];
    }
    sort(d.begin(), d.end());
    vector<ll> sum(n, 0);// 差分前缀和
    for (int i = 0; i < n - 1; i++) {
        sum[i + 1] = sum[i] + d[i];
    }
    // 方差的n^2倍就是 (1/n) * sigma(na_i - sum)^2
    // = (1/n) * sigma(na_i^2 - 2 * na_i * sum + sum^2)
    // = n * sigma(a_i^2) - sum^2
    // dp表示用了i个差分，目前和为j的最小的平方和（用dp值和j计算方差）
    // vector<vector<ll>> dp(n, vector<ll>(MAXSUM, LONG_LONG_MAX));
    vector<ll> dp(MAXSUM, LONG_LONG_MAX);
    dp[0] = 0;
    int max_sum = 0;
    for (int i = 1; i < n; i++) {
        ll d_i = d[i - 1];
        ll s_i = sum[i];
        if (d_i == 0) continue;
        // 前面影响后面就从后遍历
        for (int j = max_sum; j >= 0; j--) {
            if (dp[j] == LONG_LONG_MAX) continue;
            ll sum_sq = dp[j];
            // 当前差分放在低谷的左边
            ll new_sum_l = j + i * d_i;
            ll sum_sq_l = sum_sq + 2 * j * d_i + i * d_i * d_i;
            dp[new_sum_l] = min(dp[new_sum_l], sum_sq_l);
            // 当前差分放在低谷的右边
            ll new_sum_r = j + s_i;
            ll sum_sq_r = sum_sq + s_i * s_i;
            dp[new_sum_r] = min(dp[new_sum_r], sum_sq_r);
            // 当前状态已经使用，清空防止下一轮使用
            dp[j] = LONG_LONG_MAX;
        }
        max_sum += max(i * d_i, s_i); // 动态更新j的遍历上限
    }
    ll min_ans = LONG_LONG_MAX;
    for (int i = 0; i <= max_sum; i++) {
        if (dp[i] != LONG_LONG_MAX) {
            ll sum_sq = dp[i];
            min_ans = min(min_ans, (ll)n * sum_sq - (ll)i * i);
        }
    }
    cout << min_ans << endl;
    return 0;
}