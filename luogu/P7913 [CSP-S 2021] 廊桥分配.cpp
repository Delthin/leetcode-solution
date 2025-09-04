#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, m1, m2;
    cin >> n >> m1 >> m2;
    vector<pair<int, int>> t1(m1), t2(m2);
    for (int i = 0; i < m1; i++) {
        cin >> t1[i].first >> t1[i].second;
    }
    for (int i = 0; i < m2; i++) {
        cin >> t2[i].first >> t2[i].second;
    }
    sort(t1.begin(), t1.end());
    sort(t2.begin(), t2.end());
    vector<int> sum1(n + 1, 0), sum2(n + 1,0);// 廊桥数量为i时，对应的飞机数
    // 记录每种廊桥数量下，对应刚好此种数量的飞机数，然后使用前缀和
    auto simulate = [&](vector<int>& sum, vector<pair<int, int>>& t) {
        int m = t.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq_in;// 小根堆, first为离开时间，second为当前廊桥内飞机数
        priority_queue<int, vector<int>, greater<>> pq_empty;// 小根堆，记录当前空的廊桥
        for (int i = 1; i <= n; i++) {
            pq_empty.push(i);
        }
        for (int i = 0; i < m; i++) {
            while (!pq_in.empty() && t[i].first >= pq_in.top().first) {
                pq_empty.push(pq_in.top().second);
                pq_in.pop();
            }
            if (pq_empty.empty()) {
                continue;
            }
            int idx = pq_empty.top();
            pq_empty.pop();
            pq_in.push({t[i].second, idx});
            sum[idx]++;
        }
        for (int i = 1; i <= n; i++) {
            sum[i] += sum[i - 1];
        }
    };
    simulate(sum1, t1);
    simulate(sum2, t2);
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, sum1[i] + sum2[n - i]);
    }
    cout << ans << endl;
    return 0;
}
