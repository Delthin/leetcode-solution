#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    vector<int> h(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    // 贪心，保持一增一减即可
    int ans = 1;
    int tmp = n;
    // 先假设第一步是増
    bool up = h[2] > h[1];
    if (h[2] == h[1]) {
        tmp--;
    }
    for (int i = 3; i <= n; i++) {
        if (h[i] == h[i - 1]) {
            tmp--;
        } else if (h[i] > h[i - 1]) {
            if (up) {
                tmp--;
            }
            up = true;
        } else {
            if (!up) {
                tmp--;
            }
            up = false;
        }
    }
    ans = max(ans, tmp);
    // 再假设第一步是减
    tmp = n;
    bool down = h[2] < h[1];
    if (h[2] == h[1]) {
        tmp--;
    }
    for (int i = 3; i <= n; i++) {
        if (h[i] == h[i - 1]) {
            tmp--;
        } else if (h[i] < h[i - 1]) {
            if (down) {
                tmp--;
            }
            down = true;
        } else {
            if (!down) {
                tmp--;
            }
            down = false;
        }
    }
    ans = max(ans, tmp);
    cout << ans << endl;
    return 0;
}
