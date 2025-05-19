#include <bits/stdc++.h>

using namespace std;

class Solution1 {
private:
    int bits(int num) {
        int ret = 0;
        while (num > 0) {
            ret += num % 10;
            num /= 10;
        }
        return ret;
    }
public:
    int smallestIndex(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            if (bits(nums[i]) == i) return i;
        }
        return -1;
    }
};

class Solution2 {
    int bits(int num) {
        int ret = 0;
        while (num > 0) {
            ret += num % 10;
            num /= 10;
        }
        return ret;
    }
public:
    int minSwaps(vector<int>& nums) {
        int n = nums.size();

        vector<pair<int, int>> indexed(n);
        for (int i = 0; i < n; i++) {
            indexed[i] = {i, bits(nums[i])};
        }

        sort(indexed.begin(), indexed.end(), [&nums](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.second != b.second) {
                return a.second < b.second;
            }
            return nums[a.first] < nums[b.first];
        });

        int swapCount = 0;
        vector<bool> visited(n, false);

        for (int i = 0; i < n; i++) {
            if (visited[i] || indexed[i].first == i) {
                continue;
            }

            int cycleSize = 0;
            int j = i;

            while (!visited[j]) {
                visited[j] = true;
                j = indexed[j].first;
                cycleSize++;
            }

            swapCount += (cycleSize - 1);
        }

        return swapCount;
    }
};

class Solution3 {
public:
    const int D[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    int minMoves(vector<string>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        if (matrix[m - 1][n - 1] == '#') {
            return -1;
        }
        vector<vector<pair<int, int>>> portals(26);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] != '.' && matrix[i][j] != '#') {
                    portals[matrix[i][j] - 'A'].emplace_back(i, j);
                }
            }
        }
        vector<vector<int>> dis(m, vector<int>(n, INT_MAX));
        dis[0][0] = 0;
        deque<pair<int, int>> q = {{0, 0}};
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop_front();
            int idx = matrix[x][y] - 'A';
            int d = dis[x][y];

            if (x == m - 1 && y == n - 1) {
                return d;
            }

            if (matrix[x][y] != '.') {
                for (auto& [nx, ny]: portals[idx]) {
                    if (d < dis[nx][ny]) {
                        q.emplace_front(nx, ny);
                        dis[nx][ny] = d;
                    }
                }
                portals[idx].clear();
            }

            for (auto& [dx, dy]: D) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < m && ny >=0 && ny < n && matrix[nx][ny] != '#' && d + 1 < dis[nx][ny]) {
                    dis[nx][ny] = d + 1;
                    q.emplace_back(nx, ny);
                }
            }
        }
        return -1;
    }
};

class Solution4 {
private:
    long long operation(long long l, long long r) {
        long long minOp = log(l) / log(4) + 1;
        long long min2 = pow(4, minOp) - l;
        long long maxOp = log(r) / log(4) + 1;
        long long max2 = r - pow(4, maxOp - 1);
        long long ans = 0;
        if (maxOp > minOp) {
            ans += min2 * minOp + (max2 + 1) * maxOp;
        }
        else {
            ans = minOp * (r - l + 1);
        }
        for (long long i = minOp + 1; i < maxOp; i++) {
            ans += (pow(4, i) - pow(4, i - 1)) * i;
        }
        return (ans + 1) / 2;
    }
public:
    long long minOperations(vector<vector<int>>& queries) {
        long long ans = 0;
        for (auto query:queries) {
            ans += operation(query[0], query[1]);
        }
        return ans;
    }
};

int main(int argc, char *argv[]) {
    Solution3 solution3;
    vector<string> queries = {"HH", ".C"};
    solution3.minMoves(queries);
}
