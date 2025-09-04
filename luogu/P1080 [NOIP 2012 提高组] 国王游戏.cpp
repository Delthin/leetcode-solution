#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> mul(vector<int>& num, int multiplier) {
    if (multiplier == 0) return {0};
    vector<int> result;
    long long carry = 0; // 使用 long long 防止乘法溢出
    for (size_t i = 0; i < num.size() || carry; i++) {
        if (i < num.size()) carry += (long long)num[i] * multiplier;
        result.push_back(carry % 10);
        carry /= 10;
    }
    // 结果可能为0，但vector中至少要有一个0
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}

vector<int> div(vector<int>& num, int divisor, int& remainder) {
    vector<int> result;
    remainder = 0;
    // 从高位开始处理
    for (int i = num.size() - 1; i >= 0; i--) {
        // 上一位的余数 * 10 + 当前位
        remainder = remainder * 10 + num[i];
        // 计算商
        result.push_back(remainder / divisor);
        // 更新余数
        remainder %= divisor;
    }
    // 结果是反的，需要翻转
    reverse(result.begin(), result.end());
    // 去除前导零
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}

bool cmp(vector<int>& num1, vector<int>& num2) {
    if (num1.size() != num2.size()) {
        return num1.size() > num2.size();
    }
    // 从高位到低位比较
    for (int i = num1.size() - 1; i >= 0; i--) {
        if (num1[i] != num2[i]) {
            return num1[i] > num2[i];
        }
    }
    return true; // A == B，也返回true
}

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> p(n);
    int king_a = 0;
    int king_b = 0;
    cin >> king_a >> king_b;
    vector<int> cur_a;
    while (king_a) {
        cur_a.push_back(king_a % 10);
        king_a /= 10;
    }
    for(int i = 0; i < n; i++) {
        cin >> p[i].first >> p[i].second;
    }
    sort(p.begin(), p.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first * a.second < b.first * b.second;
    });
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        int cur_b = p[i].second;
        int rem = 0;
        vector<int> cur_ans = div(cur_a, cur_b, rem);
        if (!cmp(ans, cur_ans)) {
            ans = cur_ans;
        }
        cur_a = mul(cur_a, p[i].first);
    }
    reverse(ans.begin(), ans.end());
    for(int an : ans) {
        cout << an;
    }
    cout << endl;
    return 0;
}