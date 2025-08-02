//
// Created by lisiyi on 25-8-2.
//
// 17:55->18:06
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int m = 0;
    cin >> m;
    vector<int> permutation(5, 0);
    iota(permutation.begin(), permutation.end(), 0);
    auto check = [&] (int id, int a, int b) {
        if (id == 1) {
            for (int i = 0; i < 4; i++) {
                if ((permutation[i] == a && permutation[i + 1] == b) ||
                    (permutation[i] == b && permutation[i + 1] == a)) {
                    return true;
                }
            }
            return false;
        } else {
            for (int i = 0; i < 5; i++) {
                if (permutation[i] == a) {
                    if (i == 0) {
                        if (permutation[i + 1] != b) {
                            return true;
                        }
                    } else if (i == 4) {
                        if (permutation[i - 1] != b) {
                            return true;
                        }
                    } else {
                        if (permutation[i - 1] != b && permutation[i + 1] != b) {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
    };
    vector<tuple<int, int, int>> checks;
    while (m--) {
        int id, a, b;
        char A, B;
        cin >> id >> A >> B;
        a = A - 'A';
        b = B - 'A';
        checks.emplace_back(id, a, b);
    }
    int ans = 0;
    do {
        bool flag = true;
        for (auto [id, a, b]: checks) {
            if (!check(id, a, b)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            ans++;
        }
    } while (next_permutation(permutation.begin(), permutation.end()));
    cout << ans << endl;
    return 0;
}