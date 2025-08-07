//
// Created by lisiyi on 25-8-5.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    long long ans = 0;
    int l = 0, r = 0;
    for (; r < n; r++) {
        if (s[r] == '0') {
            l = r;
            continue;
        }
        while (s[l] == '0' && l <= r) {
            l++;
        }
        ans += max(0, r - l + 1 - m + 1);
    }
    cout << ans << endl;
    return 0;
}