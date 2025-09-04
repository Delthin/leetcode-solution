#include <bits/stdc++.h>

using namespace std;

class Solution1 {
public:
    int gcdOfOddEvenSums(int n) {
        int sumOdd = 0;
        int sumEven = 0;
        for (int i = 1; i <= n * 2; i++) {
            if (i % 2 == 1) {
                sumOdd += i;
            }
            else {
                sumEven += i;
            }
        }
        return __gcd(sumOdd, sumEven);
    }
};

class Solution2 {
public:
    bool partitionArray(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> cnt;
        int max_size = 0;
        for (int num: nums) {
            cnt[num]++;
            max_size = max(max_size, cnt[num]);
        }
        return (max_size * k <=n) && (n % k == 0);
    }
};

class Solution3 {

    struct DSU {
        vector<int> parent;
        vector<int> sz; // 可选：用于按秩合并
        vector<int> component_max;
        DSU(int n, vector<int>& nums) {
            parent.resize(n + 1);
            iota(parent.begin(), parent.end(), 0);
            sz.assign(n + 1, 1);
            component_max = nums;
        }
        int find(int i) {
            if (parent[i] == i)
                return i;
            return parent[i] = find(parent[i]); // 路径压缩
        }
        bool unite(int i, int j) {
            int root_i = find(i);
            int root_j = find(j);
            if (root_i != root_j) {
                if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
                parent[root_j] = root_i;
                sz[root_i] += sz[root_j];
                component_max[root_i] = max(component_max[root_i], component_max[root_j]);
                return true;
            }
            return false; // 已经在同一集合中
        }
    };

public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        DSU dsu(n, nums);
        stack<int> st;
        // 找左侧第一个大于的
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                st.pop();
            }
            if (!st.empty()) {
                dsu.unite(st.top(), i);
            }
            st.push(i);
        }
        // 找右侧最后一个小于的
        for (int i = 0; i < n; i++) {
            for (int j = n - 1; j > i; j--) {
                if (nums[j] < nums[i]) {
                    dsu.unite(i, j);
                    break;
                }
            }
        }
        for (int i = 0; i < n; i++) {
            ans[i] = dsu.component_max[dsu.find(i)];
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
    Solution4 s;
    cout << s.minMoves(1, 0, 4480, 36448) << endl;
    return 0;
}