// O(nlogn)，按位与->乘法（因子为1和0) popcount->求和
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    const int MOD = 991127;
    vector<ll> dp(n, 0);
    dp[0] = 1;
    // 双重求和转换为一重求和
    // dp_i = sum_{j=0}^{i-1} dp_j * popcount(a_i & a_j) 把总体按位与求和分散到每一位
    //      = sum_{k=0}^{29} sum_{j=0}^{i-1} dp_j * bitk(i) * bitk(j)
    // bitk(i) 表示 i 的第 k 位是否为1，把按位与化为了乘法
    //      = sum_{k=0}^{29} bitk(i) * sum_{j=0}^{i-1} (dp[j] * bitk(j)) 交换求和顺序，形成前缀和
    // 从内层循环开始枚举
    vector<ll> bit_sums(30, 0);
    for (int k = 0; k < 30; k++) {
        if (a[0] >> k & 1) {
            bit_sums[k] += dp[0];
            bit_sums[k] %= MOD;
        }
    }
    for (int i = 1; i < n; i++) {
        ll dp_i = 0;
        for (int k = 0; k < 30; k++) {
            if (a[i] >> k & 1) {
                dp_i += bit_sums[k];
                dp_i %= MOD;
            }
        }
        dp[i] = dp_i;
        for (int k = 0; k < 30; k++) {
            if (a[i] >> k & 1) {
                bit_sums[k] += dp_i;
                bit_sums[k] %= MOD;
            }
        }
    }
    cout << dp[n - 1] << endl;
    return 0;
}
