#include <bits/stdc++.h>
using namespace std;

const int N = 4e7 + 10;

int primes[N], count_primes;
int euler[N];
bool is_composite[N];

void get_eulers_linear(int n)
{
    euler[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!is_composite[i]) {
            primes[count_primes++] = i;
            euler[i] = i - 1;
        }
        for (int j = 0; j < count_primes && (long long)i * primes[j] <= n; j++)
        {
            int t = i * primes[j];
            is_composite[t] = true;
            if (i % primes[j] == 0) {
                // p 是 i 的最小质因子
                euler[t] = euler[i] * primes[j];
                break;
            }
            // p 不是 i 的最小质因子
            euler[t] = euler[i] * (primes[j] - 1);
        }
    }
}

vector<bool> first_win(N, false);
vector<int> first_win_count(N, 0);

void init(int k, int R) {
    get_eulers_linear(2 * R + 2 * k);
    first_win[0] = true;
    first_win[1] = false;
    first_win[2] = true;
    first_win_count[1] = 0;
    first_win_count[2] = 1;
    for (int i = 3; i <= R; i++) {
        int s1 = euler[i];
        int s2 = euler[2 * i];

        bool can_win = false;
        if (!first_win[s1]) {
            can_win = true;
        }
        if (i != s2 && !first_win[s2]) {
            can_win = true;
        }
        if (i > k) {
            int s3 = euler[i - k];
            if (i != s3 && !first_win[s3]) {
                can_win = true;
            }
        }
        first_win[i] = can_win;
        first_win_count[i] = first_win_count[i - 1] + first_win[i];
    }
}


int main() {
    int L,R,K;
    cin >> L >> R >> K;
    init(K, R);
    double ans = 0;
    double total = 0;
    for (int r = L; r <= R; r++) {
        if (first_win[r]) {
            double rate = 1;
            total++;
            for (int l = 1; l <= r; l++) {
                int len = r - l + 1;
                double cur_rate = ((double)first_win_count[r] - first_win_count[l - 1]) / len;
                rate = min(rate, cur_rate);
            }
            ans += rate;
        }
    }
    ans /= total;
    cout << ans << endl;
    return 0;
}