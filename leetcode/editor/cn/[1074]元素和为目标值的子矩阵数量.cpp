//给出矩阵 matrix 和目标值 target，返回元素总和等于目标值的非空子矩阵的数量。 
//
// 子矩阵 x1, y1, x2, y2 是满足 x1 <= x <= x2 且 y1 <= y <= y2 的所有单元 matrix[x][y] 的集合。 
//
//
// 如果 (x1, y1, x2, y2) 和 (x1', y1', x2', y2') 两个子矩阵中部分坐标不同（如：x1 != x1'），那么这两个子矩阵
//也不同。 
//
// 
//
// 示例 1： 
//
// 
//
// 
//输入：matrix = [[0,1,0],[1,1,1],[0,1,0]], target = 0
//输出：4
//解释：四个只含 0 的 1x1 子矩阵。
// 
//
// 示例 2： 
//
// 
//输入：matrix = [[1,-1],[-1,1]], target = 0
//输出：5
//解释：两个 1x2 子矩阵，加上两个 2x1 子矩阵，再加上一个 2x2 子矩阵。
// 
//
// 示例 3： 
//
// 
//输入：matrix = [[904]], target = 0
//输出：0
// 
//
// 
//
// 提示： 
//
// 
// 1 <= matrix.length <= 100 
// 1 <= matrix[0].length <= 100 
// -1000 <= matrix[i][j] <= 1000 
// -10^8 <= target <= 10^8 
// 
//
// Related Topics 数组 哈希表 矩阵 前缀和 👍 249 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution1074{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    long long sonSum(vector<vector<long long>>& sum, int r1, int c1, int r2, int c2) {
        return sum[r2+1][c2+1]-sum[r2+1][c1]-sum[r1][c2+1]+sum[r1][c1];
    }
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<long long>> sum(m + 1, vector<long long>(n + 1, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n;j++) {
                sum[i + 1][j + 1] = sum[i + 1][j] + sum[i][j + 1] - sum[i][j] + matrix[i][j];
            }
        }
        int ans = 0;
        for (int j = 0; j < n; j++) {
            for (int c = j; c < n; c++) {
                unordered_map<long long, int> freq;
                freq[0] = 1;
                for (int r = 0; r < m; r++) {
                    long long now = sonSum(sum, 0, j, r, c);
                    long long hashSum = now - target;
                    if (freq.find(hashSum) != freq.end()) {
                        ans += freq[hashSum];
                    }
                    freq[now]++;
                }
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1074;
int main() {
    Solution solution;

    return 0;
}