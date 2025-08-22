#include <bits/stdc++.h>

using namespace std;

class Solution1 {
    using ll = long long;
public:
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        vector<ll> sum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            sum[i + 1] = sum[i] + prices[i] * strategy[i];
        }
        ll profit = sum[n] - sum[k];
        ll ans = sum[n];
        //前k/2设为0
        //不用操作
        for (int i = k / 2; i < k; i++) {
            // 后k/2设为1
            profit += prices[i];
        }
        ans = max(ans, profit);
        for (int i = k; i < n; i++) {
            // 滑窗，先去头从0到strategy[i - k]，直接加就行
            profit += prices[i - k] * strategy[i - k];
            // 中间k/2处由1变成0
            profit -= prices[i - k / 2];
            // 加上新的
            profit += prices[i] * (1 - strategy[i]);
            ans = max(ans, profit);
        }
        return ans;
    }
};

class Solution2 {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int mod = 1e9 + 7;
        for (auto q: queries) {
            int l = q[0];
            int r = q[1];
            int k = q[2];
            int v = q[3];
            for (int i = l; i <= r; i+=k) {
                nums[i] = (int)((long long)nums[i] * v % mod);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans ^= nums[i];
        }
        return ans;
    }
};

class Solution3 {

public:
    long long minArraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> dp(n + 1, 0);// 处理完前i个后的最小和
        unordered_map<int, long long> dp_map; // 每个余数对应最小dp值
        dp_map[0] = 0;
        long long sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += nums[i - 1];
            int r = sum % k;
            dp[i] = dp[i - 1] + nums[i - 1]; // 不删除nums[i - 1]结尾的子数组
            if (dp_map.find(r) != dp_map.end()) {
                dp[i] = min(dp[i], dp_map[r]); // 可以在前面找到一个最小的dp，删除从j到i-1的子数组
            }
            if (dp_map.find(r) == dp_map.end() || dp_map[r] > dp[i]) {
                dp_map[r] = dp[i];
            }
        }
        return dp[n];
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
    Solution4 s;
    cout << s.minMoves(1, 0, 4480, 36448) << endl;
    return 0;
}