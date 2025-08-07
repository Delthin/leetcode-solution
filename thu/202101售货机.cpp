#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
    int n, x;
    cin >> n >> x;
    x--;
    vector<int> a(n);
    vector<int> b(n);
    vector<double> p(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int b_i;
        cin >> b_i;
        b[i] = b_i - 1;
        cin >> p[i];
    }
    double ans = 0;
    vector<bool> visited(n, false);
    function<double(int)> dfs = [&](int i) {
        int next = b[i];
        double res = a[i];
        if (visited[x])
            return 0.0;

        if (!visited[i] && !visited[next]) {
            visited[i] = true;
            res += dfs(i) * p[i];
            visited[i] = false;
            visited[next] = true;
            res += dfs(next) * (1 - p[i]);
            visited[next] = false;
        } else if (!visited[i]) {
            // 必然为i
            visited[i] = true;
            res += dfs(i);
            visited[i] = false;
        } else if (!visited[next]) {
            // 必然为next
            visited[next] = true;
            res += dfs(next);
            visited[next] = false;
        }
        return res;
    };
    for (int i = 0; i < n; i++) {
        ans += dfs(i);
    }
    ans /= n;
    cout << fixed << setprecision(9) << ans << endl;

    return 0;
}