/**
象棋骑士有一个独特的移动方式，它可以垂直移动两个方格，水平移动一个方格，或者水平移动两个方格，垂直移动一个方格(两者都形成一个 L 的形状)。 

 象棋骑士可能的移动方式如下图所示: 

 

 我们有一个象棋骑士和一个电话垫，如下所示，骑士只能站在一个数字单元格上(即蓝色单元格)。 

 

 给定一个整数 n，返回我们可以拨多少个长度为 n 的不同电话号码。 

 你可以将骑士放置在任何数字单元格上，然后你应该执行 n - 1 次移动来获得长度为 n 的号码。所有的跳跃应该是有效的骑士跳跃。 

 因为答案可能很大，所以输出答案模 10⁹ + 7. 

 

 
 

 示例 1： 

 
输入：n = 1
输出：10
解释：我们需要拨一个长度为1的数字，所以把骑士放在10个单元格中的任何一个数字单元格上都能满足条件。
 

 示例 2： 

 
输入：n = 2
输出：20
解释：我们可以拨打的所有有效号码为[04, 06, 16, 18, 27, 29, 34, 38, 40, 43, 49, 60, 61, 67, 72, 76
, 81, 83, 92, 94]
 

 示例 3： 

 
输入：n = 3131
输出：136006598
解释：注意取模
 

 

 提示： 

 
 1 <= n <= 5000 
 

 Related Topics 动态规划 👍 198 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution935{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
    using LL = long long;
    static const LL MOD = 1e9 + 7;

    struct Matrix {
        // 模数，如果需要的话
        int dim;
        vector<vector<LL> > mat;

        // 构造函数
        Matrix(int d) : dim(d) {
            mat.resize(dim, vector<LL>(dim, 0));
        }

        // 矩阵乘法
        Matrix operator*(const Matrix &other) const {
            Matrix result(dim);
            for (int i = 0; i < dim; ++i) {
                for (int j = 0; j < dim; ++j) {
                    for (int k = 0; k < dim; ++k) {
                        result.mat[i][j] = (result.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
                    }
                }
            }
            return result;
        }

        Matrix operator^(LL exp) const {
            return matrix_power(*this, exp);
        }

        Matrix operator=(const Matrix &other) {
            dim = other.dim;
            mat = other.mat;
            return *this;
        }

        static Matrix matrix_power(Matrix base, LL exp) {
            // 构造一个单位矩阵作为结果的初始值
            Matrix result(base.dim);
            for (int i = 0; i < base.dim; ++i) {
                result.mat[i][i] = 1;
            }

            while (exp > 0) {
                if (exp & 1) {
                    // 如果 exp 的当前最低位是 1
                    result = result * base;
                }
                base = base * base; // base 自乘
                exp >>= 1; // exp 右移一位
            }
            return result;
        }
    };

public:
    int knightDialer(int n) {
        vector<vector<int>> base (10, vector<int>(10, 0));
        base[0][4] = base[0][6] = 1;
        base[1][6] = base[1][8] = 1;
        base[2][7] = base[2][9] = 1;
        base[3][4] = base[3][8] = 1;
        base[4][0] = base[4][3] = base[4][9] = 1;
        base[5] = vector<int>(10, 0);
        base[6][0] = base[6][1] = base[6][7] = 1;
        base[7][2] = base[7][6] = 1;
        base[8][1] = base[8][3] = 1;
        base[9][2] = base[9][4] = 1;
        Matrix base_mat(10);
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                base_mat.mat[i][j] = base[i][j];
            }
        }
        Matrix res = base_mat ^ (n - 1);
        LL ans = 0;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                ans = (ans + res.mat[i][j]) % MOD;
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution935;
int main() {
    Solution solution;

    return 0;
}