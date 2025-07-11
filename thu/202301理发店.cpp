#include <bits/stdc++.h>
using namespace std;

class person {
public:
    int a;
    int b;
};

// 给定洗发顺序下的可能时间，直接暴力遍历剪发顺序
int simulate(const vector<person>& people) {
    int n = people.size();
    vector<int> wash_start(n), wash_end(n);
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        wash_start[i] = current_time;
        current_time += people[i].a;
        wash_end[i] = current_time;
    }
    int min_end = INT_MAX;
    vector<int> order(n);
    for (int i = 0; i < n; i++) {
        order[i] = i;
    }
    do {
        int time = 0;
        for (int i = 0; i < n; i++) {
            time = max(time, wash_end[order[i]]) + people[order[i]].b;
        }
        min_end = min(min_end, time);
    } while (next_permutation(order.begin(), order.end()));

    return min_end;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<person> people(n);
        for (int i = 0; i < n; i++) {
            cin >> people[i].a >> people[i].b;
        }

        int min_time = INT_MAX;

        vector<int> wash_order(n);
        for (int i = 0; i < n; ++i) {
            wash_order[i] = i;
        }

        do {
            vector<person> order(n);
            for (int i = 0; i < n; ++i) {
                order[i] = people[wash_order[i]];
            }
            int time = simulate(order);
            min_time = min(min_time, time);
        } while (next_permutation(wash_order.begin(), wash_order.end()));

        cout << min_time << endl;
    }
    return 0;
}

// 两个全排列！关键是记录好每个顾客的洗发开始和结束时间。
// next_permutation要重载<运算符！！可以用idx的全排列，然后根据idx来计算每个时间。
