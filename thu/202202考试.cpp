//
// Created by lisiyi on 25-8-2.
//
#include <bits/stdc++.h>
using namespace std;

using LL = long long;
static const LL MOD = 7654321;

struct Matrix {
    // 模数，如果需要的话
    int dim;
    vector<vector<LL>> mat;

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

int main() {
    int T;
    cin >> T;
    Matrix base(4);
    base.mat[0][1] = 1;
    base.mat[2][3] = 1;
    base.mat[1][0] = 1;
    base.mat[1][3] = 1;
    base.mat[3][1] = 1;
    base.mat[3][2] = 1;
    vector<LL> memo(10001, -1);
    auto solve = [&] (int n) {
        if (memo[n] != -1) return memo[n];
        Matrix t = base;
        t = t ^ (n - 1);
        LL ans = 0;
        for (int i = 0; i < 4; i ++) {
            ans = (ans + t.mat[0][i]) % MOD;
        }
        memo[n] = ans;
        return ans;
    };
    while (T--) {
        int n;
        cin >> n;
        cout << solve(n) << endl;
    }
    return 0;
}
