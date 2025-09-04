#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Edge {
    int to;
    ll capacity;
    int rev;
};

struct MaxFlow {
    int n;
    vector<vector<Edge>> adj;
    vector<int> level;
    vector<int> iter;
    MaxFlow(int size): n(size), adj(size + 1) {}
    void add_edge(int u, int v, ll cap) {
        adj[u].push_back({v, cap, (int)adj[v].size()});
        adj[v].push_back({u, 0, (int)adj[u].size() - 1});
    }
    bool bfs(int s, int t) {
        level.assign(n + 1, -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const auto& edge: adj[u]) {
                if (edge.capacity > 0 && level[edge.to] < 0) {
                    level[edge.to] = level[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1;
    }
    ll dfs(int u, int t, ll f) {
        if (u == t) return f;
        for (int& i = iter[u]; i < adj[u].size(); i++) {
            Edge& e = adj[u][i];
            if (e.capacity >0 && level[u] < level[e.to]) {
                ll d = dfs(e.to, t, min(f, e.capacity));
                if (d > 0) {
                    e.capacity -= d;
                    adj[e.to][e.rev].capacity += d;
                    return d;
                }
            }
        }
        return 0;
    }
    ll solve(int s, int t) {
        ll max_flow = 0;
        while (bfs(s, t)) {
            iter.assign(n + 1, 0);
            ll f;
            while ((f = dfs(s, t, 1e18)) > 0) {
                max_flow += f;
            }
        }
        return max_flow;
    }
};

int main() {
    int m,n;
    cin >> m >> n;
    MaxFlow mf(m + n + 2);
    int s = m + n + 1;
    int t = m + n + 2;
    ll total = 0;
    string line;
    getline(cin, line);
    for (int i = 1; i <= m; i++) {
        getline(cin, line);
        stringstream ss(line);
        int p;
        ss >> p;
        int v;
        while (ss >> v) {
            mf.add_edge(i, v + m, 1e18);
        }
        mf.add_edge(s, i, p);
        total += p;
    }
    for (int i = 1; i <= n; i++) {
        int c;
        cin >> c;
        mf.add_edge(i + m, t, c);
    }
    ll cost = mf.solve(s,t);
    for (int i = 1; i <= m; i++) {
        if (mf.level[i] != -1) {
            cout << i << " ";
        }
    }
    cout << endl;
    for (int i = 1; i <= n; i++) {
        if (mf.level[i + m] != -1) {
            cout << i << " ";
        }
    }
    cout << endl;
    total -= cost;
    cout << total << endl;
    return 0;
}

