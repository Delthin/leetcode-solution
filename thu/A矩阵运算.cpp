#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<ll>>;
using vec = vector<ll>;

matrix mul(matrix& a, matrix& b) {
    int n = a.size();
    int d = b[0].size();
    int K = a[0].size();
    matrix res(n, vec(d, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            for (int k = 0; k < K; k++) {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return res;
}

int main() {
    int n, d;
    cin >> n >> d;
    matrix Q(n, vec(d, 0));
    matrix K_T(d, vec(n, 0));
    matrix res(n, vec(d, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cin >> Q[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cin >> K_T[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cin >> res[i][j];
        }
    }
    res = mul(K_T, res);
    res = mul(Q, res);
    for (int i = 0; i < n; i++) {
        int w;
        cin >> w;
        for (int j = 0; j < d; j++) {
            res[i][j] *= w;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) {
            cout << res[i][j];
            if (j < d - 1) cout << " ";
            else cout << endl;
        }
    }
    return 0;
}