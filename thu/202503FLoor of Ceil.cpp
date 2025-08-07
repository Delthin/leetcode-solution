//
// Created by lisiyi on 25-8-4.
//
#include <bits/stdc++.h>
using namespace std;

int get_min(int x, int n, int m) {
    while (m > 0 && x > 1) {
        x = (x + 1) / 2;
        m--;
    }
    while (n > 0 && x > 0) {
        x /= 2;
        n--;
    }
    return x;
}

int get_max(int x, int n, int m) {
    while (n > 0 && x > 0) {
        x /= 2;
        n--;
    }
    while (m > 0 && x > 1) {
        x = (x + 1) / 2;
        m--;
    }
    return x;
}

int main(int argc, char *argv[]) {
    int T;
    cin >> T;
    while (T--) {
        int x, n, m;
        cin >> x >> n >> m;
        cout << get_min(x, n, m) << " " << get_max(x, n, m) << endl;
    }
    return 0;
}

