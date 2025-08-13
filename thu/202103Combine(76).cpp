//从小枚举，尽可能剪枝
// 76分，剩下的要卷积、快速数论变换 NTT 快速沃尔什变换 FWT等等
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll n;
vector<ll> a;
vector<ll> b;
vector<ll> c;
vector<ll> s_a;
vector<ll> s_b;
vector<ll> s_c;

void solve1() {
    for (int k = 2; k <= n; k++) {
        for (int i = 1; i < k; i++) {
            c[k] += a[i] * b[k - i];
        }
    }
}

void solve2() {
    for (int k = 1; k <= n - 1;k++) {
        // i - j = k
        for (int j = 1; j <= n - k; j++) {
            c[k] += a[j + k] * b[j];
        }
    }
}

void solve3() {
    // 从小的枚举剪枝，能减少大量无效枚举
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i * j > n) break;
            c[i * j] += a[i] * b[j];
        }
    }
}

void solve4() {
    for (int k = 1; k <= n; k++) {
        // i / j = k
        for (int j = 1; j <= n; j++) {
            if (k * j > n) break;
            c[k] += a[k * j] * b[j];
        }
    }
}

void solve5() {
    // i / j 的下界 = k，也就是i <= k * j < i + j
    for (int k = 1; k <= n; k++) {
        for (int j = 1; j <= n; j++) {
            if (k * j > n) break;
            c[k] += (s_a[min(n, (ll)k * j + j - 1)] - s_a[k * j - 1]) * b[j];
        }
    }
}

void solve6() {
    // i and j = k
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if ((i & j) == k) {
                    c[k] += a[i] * b[j];
                }
            }
        }
    }
}

void solve7() {
    // i or j = k
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if ((i | j) == k) {
                    c[k] += a[i] * b[j];
                }
            }
        }
    }
}

void solve8() {
    // i xor j = k
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            // 那么i xor k = j;
            c[k] += a[i] * b[i ^ k];
        }
    }
}

void solve9() {
    // min(i, j) = k
    for (int k = 1; k <= n; k++) {
        c[k] += a[k] * b[k];
        c[k] += (s_a[n] - s_a[k]) * b[k];
        c[k] += (s_b[n] - s_b[k]) * a[k];
    }
}

void solve10() {
    // max(i, j) = k
    for (int k = 1; k <= n; k++) {
        c[k] += a[k] * b[k];
        c[k] += (s_a[k - 1]) * b[k];
        c[k] += (s_b[k - 1]) * a[k];
    }
}


int main() {
    cin >> n;
    int p;
    cin >> p;
    a.resize(n + 1);
    b.resize(n + 1);
    c.resize(n + 1, 0);
    s_a.resize(n + 1, 0);
    s_b.resize(n + 1, 0);
    s_c.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        s_a[i] = s_a[i - 1] + a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        s_b[i] = s_b[i - 1] + b[i];
    }
    function<void()> func;
    map<int, decltype(func)> mp = {{1, solve1}, {2, solve2}, {3, solve3},
    {4, solve4}, {5, solve5}, {6, solve6}, {7, solve7}, {8, solve8}, {9, solve9}, {10, solve10}};
    func = mp[p];
    func();
    for (int i = 1; i <= n; i++) {
        cout << c[i] << " \n"[i == n];
    }
    return 0;
}