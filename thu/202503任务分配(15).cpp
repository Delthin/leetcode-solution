//
// Created by lisiyi on 25-8-3.
//
#include <bits/stdc++.h>
using namespace std;

void sub1(int n, vector<int>& father, vector<int>& time, vector<int>& _widget) {
    // n <= 6 暴力排列
    function<int(int)> test = [&](int id) {
        vector<int> widget = _widget;
        widget[id] = INT_MAX;//无限用
        int res = INT_MAX;
        vector<int> permutation(n);
        iota(permutation.begin(), permutation.end(), 1);// 分的时间
        do {
            function<bool(int, int)> check = [&](int i, int max_t) {
                if (i == 0) return true;
                if (i == id) return check(father[i], max_t);
                int t = time[permutation[i - 1]];
                max_t = max(t, max_t);
                if (max_t > widget[i]) return false;
                return check(father[i], max_t);
            };
            bool pass = true;
            for (int i = 1; i <= n; i++) {
                if (!check(i, 0)) {
                    pass = false;
                    break;
                }
            }
            if (pass) {
                int t = time[permutation[id - 1]];
                res = min(res, (max(0, t - _widget[id])));
            }
        } while (next_permutation(permutation.begin(), permutation.end()));
        return res;
    };
    int ans = INT_MAX;
    for (int i = 1; i <= 6; i++) {
        int r = test(i);
        if (r != INT_MAX) {
            ans = min(ans, r);
        }
    }
    cout << ans << endl;
}

void sub4(int n, vector<int>& father, vector<int>& time, vector<int>& widget) {
    // f_i = i - 1 贪心
    // 最上面分最大的
    sort(time.begin(), time.end());
    int res = 0;
    int max_time = 0;
    for (int i = n; i >= 1; i--) {
        if (widget[i] >= time[n - i + 1]) {
            max_time = max(max_time, time[n - i + 1]);
            continue;
        }
        res = time[n - i + 1] - widget[i];
        break;
    }
    cout << res << endl;
}

void sub5(int n, vector<int>& father, vector<int>& time, vector<int>& widget) {
    // f_i = 1 堆暴力
    sort(time.begin(), time.end());

    // 1. 计算初始状态下的真实限制 W_orig
    std::vector<long long> W_orig;
    long long w1 = widget[1];
    W_orig.push_back(w1);
    for (int i = 2; i <= n; ++i) {
        W_orig.push_back(std::min((long long)widget[i], w1));
    }

    // 2. 将真实限制排序
    std::sort(W_orig.begin(), W_orig.end());

    // 3. 计算并输出最大差额
    long long max_deficit = 0;
    for (int i = 0; i < n; ++i) {
        max_deficit = std::max(max_deficit, (long long)time[i + 1] - W_orig[i]);
    }

    std::cout << max_deficit << std::endl;
}

int main() {
    int n;
    cin >> n;
    vector<int> father(n + 1, 0);
    bool is_4 = true;
    bool is_5 = true;
    for (int i = 2; i <= n; i++) {
        cin >> father[i];
        if (father[i] != i - 1) is_4 = false;
        if (father[i] != 1) is_5 = false;
    }
    vector<int> time(n + 1, 0);// sort之后第一个是0，要注意只能正向sort
    for (int i = 1; i <= n; i++) {
        cin >> time[i];
    }
    vector<int> widget(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> widget[i];
    }
    if (n == 1) {
        cout << max(0, time[1] - widget[1]) << endl;
    }
    else if (is_4) {
        sub4(n, father, time, widget);
    } else if (is_5) {
        sub5(n, father, time, widget);
    } else if (n <= 6) {
        sub1(n, father, time, widget);
    }
}

