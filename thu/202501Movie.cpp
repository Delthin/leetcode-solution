//
// Created by lisiyi on 25-7-18.
//
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        string line;
        cin >> line;
        int h, m, s;
        stringstream ss(line);
        char colon;
        // 可以直接用ss读取分割
        ss >> h >> colon >> m >> colon >> s;
        int time = h * 3600 + m * 60 + s;
        int x;
        cin >> x;
        int frame = time * x;
        cout << frame << endl;
    }
    return 0;
}