//
// Created by lisiyi on 25-8-5.
//
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool check(int i, int j, int k, int c)
{
    int arc1 = j - i;
    int arc2 = k - j;
    int arc3 = c - (k - i);

    if (c % 2 == 0) { // 如果周长是偶数
        return arc1 < c / 2 && arc2 < c / 2 && arc3 < c / 2;
    } else { // 如果周长是奇数
        return arc1 <= c / 2 && arc2 <= c / 2 && arc3 <= c / 2;
    }
}

int main()
{
    ll n, c;
    cin >> n >> c;
    vector<ll> freq(c, 0);
    vector<ll> prefix(c + 1, 0);
    for (int _ = 0; _ < n; _++) {
        int i;
        cin >> i;
        freq[i]++;
    }
    for (int i = 0; i < c; i++) {
        prefix[i + 1] = prefix[i] + freq[i];
    }

    ll total = n * (n - 1) * (n - 2) / 6;
    ll single = 0;
    // 本身选3
    for (int i = 0; i < c; i++) {
        if (freq[i] >= 3)
            single += freq[i] * (freq[i] - 1) * (freq[i] - 2) / 6;
    }
    ll right = 0;
    // 直角除去对面都可以
    if (c % 2 == 0) {
        for (int i = 0; i < c / 2; i++) {
            if (freq[i] && freq[i + c / 2]) {
                ll n_i = freq[i], n_oppo = freq[i + c / 2];
                // 还要加上两点在同一点的情况
                ll case1 = n_i * n_oppo * (n - n_i - n_oppo);
                ll case2 = n_i * (n_i - 1) / 2 * n_oppo;
                ll case3 = n_i * n_oppo * (n_oppo - 1) / 2;
                right += case1 + case2 + case3;
            }
        }
    }
    ll obtuse = 0;
    // 钝角前方半圆任选2
    for (int i = 0; i < c; i++) {
        if (!freq[i])
            continue;
        auto query = [&](int start, int end) {
            if (start <= end) {
                return prefix[end + 1] - prefix[start];
            } else { // 环状情况
                return (prefix[c] - prefix[start]) + prefix[end + 1];
            }
        };
        ll points = query(i + 1, (i + (c - 1) / 2 + c) % c);
        obtuse += freq[i] * points * (points - 1) / 2;
        // 自身选2
        obtuse += freq[i] * (freq[i] - 1) / 2 * points;
    }
    ll ans = total - single - right - obtuse;
    cout << ans << endl;
    return 0;
}