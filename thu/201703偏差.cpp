#include <bits/stdc++.h>
using namespace std;

using ULL = unsigned long long;
struct StringHasher {
private:
    long long P1, P2, M1, M2;
    vector<long long> h1, h2, p1, p2;
    static const auto &get_params() {
        static const auto params = [] {
            mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
            auto dist = uniform_int_distribution<long long>(8e8, 9e8);
            long long p1 = dist(rng), p2 = dist(rng);
            while (p2 == p1) p2 = dist(rng);
            return make_tuple(p1, p2, 1000000007LL, 1'070'777'777LL);
        }();
        return params;
    }
public:
    // 构造函数
    StringHasher(const vector<int>& vec) {
        // 从静态函数获取共享的哈希参数
        tie(P1, P2, M1, M2) = get_params();
        int n = vec.size();
        h1.resize(n + 1, 0);
        h2.resize(n + 1, 0);
        p1.resize(n + 1, 0);
        p2.resize(n + 1, 0);
        p1[0] = p2[0] = 1;
        for (int i = 0; i < n; ++i) {
            p1[i + 1] = (p1[i] * P1) % M1;
            p2[i + 1] = (p2[i] * P2) % M2;
            h1[i + 1] = (h1[i] * P1 + (vec[i] + 1)) % M1;
            h2[i + 1] = (h2[i] * P2 + (vec[i] + 1)) % M2;
        }
    }

    ULL get_hash(int l, int r) {
        long long hash1 = (h1[r + 1] - (h1[l] * p1[r - l + 1]) % M1 + M1) % M1;
        long long hash2 = (h2[r + 1] - (h2[l] * p2[r - l + 1]) % M2 + M2) % M2;
        return (ULL) hash1 << 32 | hash2;
    }

};

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        int m;
        cin >> m;
        vector<int> b(m);
        for (int i = 0; i < m; ++i) {
            cin >> b[i];
        }
        int k_cnt = 0, abs_k_min = INT_MAX, l_cnt = 0, l_min = n - 1, l_max = 0;
        unordered_set<int> possible_k;
        vector<int> da(n + 1);
        vector<int> db(m + 1);
        // 通过哈希值比较差分数组
        for (int i = 0; i < n - 1; ++i) {
            da[i + 1] = a[i + 1] - a[i];
        }
        for (int i = 0; i < m - 1; ++i) {
            db[i + 1] = b[i + 1] - b[i];
        }
        StringHasher hasher_a(da);
        StringHasher hasher_b(db);
        for (int i = 1; i <= n - m + 1; ++i) {
            if (hasher_a.get_hash(i, i + m - 2) == hasher_b.get_hash(1, m - 1)) {
                int k = b[0] - a[i - 1];
                possible_k.insert(k);
                l_cnt++;
                l_min = min(l_min, i);
                l_max = max(l_max, i);
            }
        }
        for (int k: possible_k) {
            k_cnt++;
            abs_k_min = min(abs_k_min, abs(k));
        }
        if (k_cnt == 0) {
            abs_k_min = 0;
            l_min = 0;
        }
        cout << k_cnt << ' ' << abs_k_min << ' ' << l_cnt << ' ' << l_min << ' ' << l_max << endl;
    }
    return 0;
}
