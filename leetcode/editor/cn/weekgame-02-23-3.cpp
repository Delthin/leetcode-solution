//
// Created by lisiyi on 25-2-23.
//
#include <bits/stdc++.h>

using namespace std;

class Solution {
private:
    int count_p_in_factorial(int n, int p) {
        int count = 0;
        while (n) {
            n /= p;
            count += n;
        }
        return count;
    }

    int compute_combination_mod10(int m, int k) {
        if (k < 0 || k > m) return 0;

        int count_2 = count_p_in_factorial(m, 2) - count_p_in_factorial(k, 2) - count_p_in_factorial(m - k, 2);
        int count_5 = count_p_in_factorial(m, 5) - count_p_in_factorial(k, 5) - count_p_in_factorial(m - k, 5);

        if (count_2 < 0 || count_5 < 0) return 0;

        int min_count = std::min(count_2, count_5);
        if (min_count >= 1) return 0;

        int num_product = 1;
        for (int i = 0; i < k; ++i) {
            int num = m - i;
            while (num % 2 == 0) num /= 2;
            while (num % 5 == 0) num /= 5;
            num_product = (num_product * (num % 10)) % 10;
        }

        int den_product = 1;
        for (int i = 1; i <= k; ++i) {
            int den = i;
            while (den % 2 == 0) den /= 2;
            while (den % 5 == 0) den /= 5;
            den_product = (den_product * (den % 10)) % 10;
        }

        int inv_den = 1;
        switch (den_product % 10) {
            case 1: inv_den = 1; break;
            case 3: inv_den = 7; break;
            case 7: inv_den = 3; break;
            case 9: inv_den = 9; break;
            default: inv_den = 1;
        }

        int result = (num_product * inv_den) % 10;

        int pow2 = 1;
        for (int i = 0; i < count_2; ++i) {
            pow2 = (pow2 * 2) % 10;
        }

        int pow5 = 1;
        for (int i = 0; i < count_5; ++i) {
            pow5 = (pow5 * 5) % 10;
        }

        result = (result * pow2) % 10;
        result = (result * pow5) % 10;

        return result;
    }

public:
    bool hasSameDigits(string s) {
        int n = s.size();
        if (n == 2) {
            return s[0] == s[1];
        }
        int m = n - 2;

        int first = 0, second = 0;
        for (int i = 0; i <= m; ++i) {
            int coef = compute_combination_mod10(m, i);
            first = (first + coef * (s[i] - '0')) % 10;
        }
        for (int i = 1; i <= m + 1; ++i) {
            int coef = compute_combination_mod10(m, i - 1);
            second = (second + coef * (s[i] - '0')) % 10;
        }

        return first == second;
    }
};

int main() {
    Solution solution;
    solution.hasSameDigits("31386065");
    return 0;

}