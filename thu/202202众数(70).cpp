// ios_base::sync_with_stdio(false);
// cin.tie(nullptr);
// endl -> "\n" 加速
// 维护众数，每次改变都删除插入到set
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Block {
    int x;
    int c;
};

vector<unordered_map<int, ll>> cnts;
vector<vector<Block>> blocks;

// 用{-cnts[i][x], x}方便排序
vector<set<pair<ll, int>>> candidates;

void update(int i, int k, int x) {
    if (cnts[i].count(x)) {
        candidates[i].erase({-cnts[i][x], x});
    }
    cnts[i][x] += k;
    if (cnts[i][x] == 0) {
        cnts[i].erase(x);
    } else {
        candidates[i].insert({-cnts[i][x], x});
    }
}

void insert(int i, int k, int x) {

    blocks[i].push_back({x, k});
    update(i, k, x);
}

void remove(int i, int k) {
    auto& vec = blocks[i];
    while (k > 0 && !vec.empty()) {
        Block& b = vec.back();
        int t = min(k, b.c);
        update(i, -t, b.x);
        b.c -= t;
        k -= t;
        if (b.c == 0) {
            vec.pop_back();
        }
    }
}

void query(int i) {
    ll res = -1;
    if (!candidates[i].empty()) {
        res = candidates[i].begin()->second;
    }
    cout << res << "\n";
}

void solve1() {
    int n, q;
    cin >> n >> q;
    cnts.resize(n);
    blocks.resize(n);
    candidates.resize(n);
    while (q--) {
        int op, i;
        cin >> op >> i;
        if (op == 1) {
            int k, x;
            cin >> k >> x;
            insert(i, k, x);
        } else if (op == 2) {
            int k;
            cin >> k;
            remove(i, k);
        } else {
            query(i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve1();
    return 0;
}