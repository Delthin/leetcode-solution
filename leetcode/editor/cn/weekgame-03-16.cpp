#include <bits/stdc++.h>

using namespace std;

class Solution1 {
public:
    int maxSum(vector<int>& nums) {
        unordered_set<int> us;
        int ans = *max_element(nums.begin(), nums.end());
        us.insert(ans);
        for (int num: nums) {
            if (num > 0 && us.count(num) == 0) {
                ans += num;
                us.insert(num);
            }
        }
        return ans;
    }
};

class Solution2 {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        static constexpr int MAXINT = 0x3f3f3f3f;
        vector<int> dist(nums.size(), MAXINT);
        unordered_map<int, vector<int>> nums_to_index;
        for (int i = 0; i < nums.size(); i++) {
            if (nums_to_index.find(nums[i]) != nums_to_index.end()) {
                vector<int>& indexs = nums_to_index.find(nums[i])->second;
                int first_index = indexs[0];
                int last_index = indexs[indexs.size() - 1];
                int dist_first = first_index + nums.size() - i;
                int dist_last = i - last_index;
                dist[i] = min({dist[i], dist_last, dist_first});
                dist[last_index] = min(dist[last_index], dist_last);
                dist[first_index] = min(dist[first_index], dist_first);
                indexs.push_back(i);
            } else {
                nums_to_index[nums[i]] = vector<int> {i};
            }
        }
        vector<int> ans(queries.size(), -1);
        for (int i = 0; i < queries.size(); i++) {
            if (dist[queries[i]] != MAXINT) {
                ans[i] = dist[queries[i]];
            }
        }
        return ans;
    }
};

class Solution3 {
private:
    vector<vector<int>> nums_after_query(vector<int>& nums, vector<int>& query) {
        vector<vector<int>> ret;
        int l = query[0], r = query[1], val = query[2];

    }
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {

    }
};

class Solution4 {

private:
    unordered_map<int, pair<int, int>> num_to_prosum;
    bool isBeautifulNumber(int num) {
        int product = 1;
        int sum = 0;
        while (num > 0) {
            if (num_to_prosum.find(num) != num_to_prosum.end()) {
                product *= num_to_prosum[num].first;
                sum += num_to_prosum[num].second;
                break;
            }
            product *= (num % 10);
            sum += (num % 10);
            num /= 10;
        }
        num_to_prosum[num] = {product, sum};
        return (product % sum == 0);
    }
public:
    int beautifulNumbers(int l, int r) {
        vector<pair<int, int>> bn(1000000001);
        for (int i = 0; i <= 9; i++) {
            bn[i] = {i, i};
        }
        for (int i = 10; i < l; i++) {
            bn[i] = {bn[i / 10] *}
        }
        int ans = 0;
        for (int i = l; i <= r; i++) {
            if (isBeautifulNumber(i)) {
                ans ++;
            }
        }
        return ans;
    }
};

int main(int argc, char *argv[]) {
    Solution2 solution2;
    vector<int> nums = {14,14,4,2,19,19,14,19,14};
    vector<int> queries = {6};
    solution2.solveQueries(nums, queries);
}
