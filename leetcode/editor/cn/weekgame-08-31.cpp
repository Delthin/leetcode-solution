#include <bits/stdc++.h>

using namespace std;

class Solution1 {
public:
    vector<int> recoverOrder(vector<int>& order, vector<int>& friends) {
        set<int> st(friends.begin(), friends.end());
        vector<int> ans;
        for (int i = 0; i < order.size(); i++) {
            if (st.count(order[i])) {
                ans.push_back(order[i]);
            }
        }
        return ans;
    }
};

class Solution2 {
public:
    vector<int> minDifference(int n, int k) {
        vector<int> prime_factors;
        for (int i = 2; i <= n / i; i++) {
            if (n % i == 0) { // i 是 n 的一个质因子
                int count = 0;
                while (n % i == 0) {
                    n /= i;
                    count++;
                    prime_factors.push_back(i);
                }
            }
        }
        if (n > 1) {
            prime_factors.push_back(n);
        }
        vector<int> ans;
        vector<int> path(k, 1);
        int min_diff = INT_MAX;
        function<void(int)> dfs = [&](int idx) {
            if (idx == prime_factors.size()) {
                int max_val = 0;
                int min_val = INT_MAX;
                for (int val: path) {
                    max_val = max(max_val, val);
                    min_val = min(min_val, val);
                }
                if (max_val - min_val < min_diff) {
                    min_diff = max_val - min_val;
                    ans = path;
                }
                return;
            }
            int p = prime_factors[idx];
            for (int i = 0; i < k; i++) {
                if (i > 0 && path[i] == path[i - 1]) {
                    continue;
                }
                path[i] *= p;
                dfs(idx + 1);
                path[i] /= p;
            }
        };
        dfs(0);
        return ans;
    }
};

class Solution3 {
public:
    long long maxProduct(vector<int>& nums) {
        if (nums.size() < 2) return 0;
        unordered_set<int> st(nums.begin(), nums.end());
        // 没有公共置位且乘积最大，从nums倒序
        sort(nums.begin(), nums.end(), greater<int>());
        int limit = 1 << ((int)log2(nums[0]) + 1);
        vector<int> dp(limit, 0);
        for (int num: nums) {
            dp[num] = num;
        }
        int num_bits = log2(limit);
        for (int i = 0; i < num_bits; ++i) {
            for (int mask = 0; mask < limit; ++mask) {
                if (mask & (1 << i)) {
                    dp[mask] = max(dp[mask], dp[mask ^ (1 << i)]);
                }
            }
        }
        long long ans = 0;
        int all_bits_mask = limit - 1;
        for (int num:nums) {
            int comple = all_bits_mask ^ num;
            int p = dp[comple];
            ans = max(ans, (long long)num * p);
        }
        return ans;
    }
};

class Solution4 {
private:

public:
    int minMoves(int sx, int sy, int tx, int ty) {
        if (sx == sy && sx == 0) {
            if (tx == 0 && ty == 0) {
                return 0;
            }
            else {
                return -1;
            }
        }
        // 将终点和初始步数 0 加入队列
        int moves = 0;
        while (true) {
            if (tx == sx && ty == sy) {
                return moves;
            }
            moves++;
            if (tx < sx || ty < sy) {
                return -1;
            }

            if (tx > 2 * ty) {
                if (tx % 2 != 0) return -1;
                tx /= 2;
            }
            else if (ty > 2 * tx) {
                if (ty % 2!= 0) return -1;
                ty /= 2;
            }
            else if (tx > ty) {
                // 逆向从 (x, y) 到 (x - y, y)
                tx = tx - ty;
            } else if (tx < ty) {
                // 逆向从 (x, y) 到 (x, y - x)
                ty = ty - tx;
            } else if (tx == ty) {
                if (sx == 0) tx = 0;
                else if (sy == 0) ty = 0;
                else {
                    return -1;
                }
            }

        }

        // 无法到达起点
        return -1;
    }
};


int main() {
    Solution3 s;
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    cout << s.maxProduct(nums) << endl;
    return 0;
}