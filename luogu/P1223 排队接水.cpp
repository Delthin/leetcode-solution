#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> t(n);
    for(int i = 0; i < n; i++) {
        cin >> t[i].first;
        t[i].second = i;
    }
    sort(t.begin(), t.end());
    ll total = 0;
    ll cur = 0;
    for(int i = 0; i < n; i++) {
        cout << t[i].second + 1 << " \n"[i == n - 1];
        if (i > 0) {
            cur += t[i - 1].first;
            total += cur;
        }
    }
    cout << fixed << setprecision(2) << (double)total / n << endl;
    return 0;
}