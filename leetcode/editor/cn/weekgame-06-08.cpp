#include <bits/stdc++.h>

using namespace std;

class Solution1 {
private:
public:
    bool canMakeEqual(vector<int>& nums, int k) {
        int find = -1;
        int count = 0;
        vector<int> tmp = nums;
        for (int i = 0; i < tmp.size() - 1; i++) {
            if (tmp[i] != find) {
                count++;
                tmp[i] = find;
                tmp[i + 1] = tmp[i + 1] == 1 ? -1 : 1;
            }
        }

        if (tmp[nums.size() - 1] == find && count <= k) return true;
        count = 0;
        find = 1;
        tmp = nums;
        for (int i = 0; i < tmp.size() - 1; i++) {
            if (tmp[i] != find) {
                count++;
                tmp[i] = find;
                tmp[i + 1] = tmp[i + 1] == 1 ? -1 : 1;
            }
        }
        if (tmp[nums.size() - 1] != find) return false;
        return count <= k;
    }
};

class Solution2 {
public:
    int countPermutations(vector<int>& complexity) {
        int n = complexity.size();
        if (n == 1) return 1;
        for (int i = 1; i < n; i++) {
            if (complexity[i] <= complexity[0]) {
                return 0;
            }
        }
        // vector<pair<int, int>> vec;
        //
        // for (int i = 0; i < n; i++) {
        //     vec.emplace_back(i, complexity[i]);
        // }
        // sort(vec.begin(), vec.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        //     if (a.second != b.second)
        //         return a.second < b.second;
        //     return a.first < b.first;
        // });
        // if (vec[0].first != 0 || vec[1].second == vec[0].second) return 0;
        // int unlocked_options = 1;
        const long long MOD = 1e9 + 7;
        long long ans = 1;
        for (int i = 1; i < n; i++) {
            ans = (ans * i) % MOD;
        }
        return ans;
    }
};

class Solution3 {
public:
    int countPartitions(vector<int>& nums, int k) {
        int n = nums.size();
        long long MOD = 1e9 + 7;
        int l = 0;
        vector<long long> dp(n + 1, 0);
        vector<long long> sumDp(n + 1, 0);
        dp[0] = 1;
        sumDp[0] = 1;
        deque<int> dqMin;
        deque<int> dqMax;
        for (int r = 0; r < nums.size(); r++) {
            while (!dqMin.empty() && nums[dqMin.back()] > nums[r]) {
                dqMin.pop_back();
            }
            while (!dqMax.empty() && nums[dqMax.back()] < nums[r]) {
                dqMax.pop_back();
            }
            dqMax.push_back(r);
            dqMin.push_back(r);
            int minIdx = 0;
            int maxIdx = 0;
            while (true) {
                minIdx = dqMin.front();
                maxIdx = dqMax.front();
                if (abs(nums[minIdx] - nums[maxIdx]) <= k) break;
                if (minIdx <= l) dqMin.pop_front();
                if (maxIdx <= l) dqMax.pop_front();
                l++;
            }
            if (l <= r) {
                long long prevSum = (l == 0) ? 0 : sumDp[l - 1];
                dp[r + 1] = (sumDp[r] - prevSum + MOD) % MOD;
            } else {
                dp[r + 1] = 0;
            }
            sumDp[r + 1] = (sumDp[r] + dp[r + 1]) % MOD;
        }
        return dp[n] % MOD;
    }
};

class Solution4 {
private:
    bool isConsecutive(char a, char b) {
        return abs(a - b) == 1 || (a == 'a' && b == 'z') || (a == 'z' && b == 'a');
    }

    bool isLexSmaller(const string& a, const string& b) {
        int n = min(a.size(), b.size());
        for (int i = 0; i < n; i++) {
            if (a[i] != b[i]) {
                return a[i] < b[i];
            }
        }
        return a.size() < b.size();
    }
    unordered_map<string, string> memo;
public:
    string lexicographicallySmallestString(string s) {
        if (memo.count(s)) return memo[s];
        string smallest = s;
        if (s == "") return s;
        for (int i = 0; i < s.size() - 1; i++) {
            if (isConsecutive(s[i], s[i+1])) {
                string next = s.substr(0, i);
                if (i < s.size() - 2) {
                    next += s.substr(i+2);
                }
                string candidate = lexicographicallySmallestString(next);

                if (isLexSmaller(candidate, smallest)) {
                    smallest = candidate;
                }
            }
        }
        memo[s] = smallest;
        return smallest;
    }
};

std::vector<int> counts(3, 3);
std::vector<std::vector<int>> containers(3, std::vector<int>(3));
long long solution_count = 0;

// 最终解决方案的打印函数
void print_final_solution() {
    std::cout << "--> Solution #" << solution_count << ": ";
    for (int c = 0; c < 3; ++c) {
        std::cout << "C" << c + 1 << ":[";
        for (int i = 0; i < 3; ++i) {
            std::cout << containers[c][i] << (i == 2 ? "" : ",");
        }
        std::cout << "] ";
    }
    std::cout << std::endl;
}

// 递归核心函数
void solve(int container_idx, int item_idx) {
    // 终止条件: 成功填满了所有容器 (0, 1, 2)
    if (container_idx == 3) {
        solution_count++;
        print_final_solution(); // 打印找到的这个解
        return;
    }

    // 计算下一个要填充的位置
    int next_container_idx = container_idx;
    int next_item_idx = item_idx + 1;
    if (next_item_idx == 3) {
        next_container_idx++;
        next_item_idx = 0;
    }

    // 核心约束：保证容器内物品有序（非递减），防止重复
    // 只有在填充容器内非第一个物品时，才需要此约束
    int start_shape_idx = 0;
    if (item_idx > 0) {
        // 直接用容器里存的数字（0,1,2）作为下一轮的起始索引
        start_shape_idx = containers[container_idx][item_idx - 1];
    }

    // 遍历可选择的物品
    for (int i = start_shape_idx; i < 3; ++i) {
        // 如果这种形状还有剩余
        if (counts[i] > 0) {
            // 1. 做出选择
            containers[container_idx][item_idx] = i;
            counts[i]--;

            // 2. 进入下一层递归
            solve(next_container_idx, next_item_idx);

            // 3. 撤销选择 (回溯)
            counts[i]++;
        }
    }
}

int main() {
    std::cout << "Starting calculation...\n";

    // 从第0个容器的第0个位置开始
    solve(0, 0);

    std::cout << "----------------------------------------\n";
    std::cout << "Final Total Combinations Found: " << solution_count << std::endl;

    return 0;
}