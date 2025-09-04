#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int>a(n * 2 + 1,0);
        for (int i = 1; i <= n * 2; i++) {
            cin >> a[i];
        }
        int out_l = 1, out_r = n * 2;
        deque<int> ans_out;
        deque<int> ans_in;
        // 默认先用左边的
        ans_out.push_back(0);
        int in_l = find(a.begin() + out_l + 1, a.begin() + out_r + 1, a[out_l]) - a.begin();
        int in_r = in_l;
        out_l++;
        ans_in.push_front(0);
        auto check = [&]() {
            for (int i = 1; i < n; i++) {
                // 找in_l和in_r与out_l和out_r相等的
                int out_l_num = a[out_l];
                int out_r_num = a[out_r];
                int in_l_num = a[in_l - 1];
                int in_r_num = a[in_r + 1];
                if (out_l_num == in_l_num && out_l < in_l - 1) {
                    // 外左内左
                    ans_out.push_back(0);
                    ans_in.push_front(0);
                    out_l++;
                    in_l--;
                } else if (out_l_num == in_r_num) {
                    // 外左内右
                    ans_out.push_back(0);
                    ans_in.push_front(1);
                    out_l++;
                    in_r++;
                } else if (out_r_num == in_l_num) {
                    // 外右内左
                    ans_out.push_back(1);
                    ans_in.push_front(0);
                    out_r--;
                    in_l--;
                } else if (out_r_num == in_r_num && out_r > in_r + 1) {
                    // 外右内右
                    ans_out.push_back(1);
                    ans_in.push_front(1);
                    out_r--;
                    in_r++;
                } else {
                    return false;
                    break;
                }
            }
            for (int i = 0; i < n; i++) {
                cout << "LR"[ans_out[i]];
            }
            for (int i = 0; i < n; i++) {
                cout << "LR"[ans_in[i]];
            }
            cout << endl;
            return true;
        };
        if (!check()) {
            // 左边不行就从右边开始
            out_l = 1, out_r = n * 2;
            ans_out.clear();
            ans_in.clear();
            ans_out.push_back(1);
            in_l = find(a.begin() + out_l, a.begin() + out_r, a[out_r]) - a.begin();
            in_r = in_l;
            out_r--;
            ans_in.push_front(0);
            if (!check()) {
                cout << "-1" << endl;
            }
        }
    }
    return 0;
}
