#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    bool hasSameDigits(string s) {
        int n = s.size();
        for (int i = 0; i < n - 2; i++) {
            string temp = "";
            for (int j = 0; j < n - 1 - i; j++) {
                temp += ((s.at(j) + s.at(j + 1) - 2 * '0') % 10) + '0';
            }
            s = temp;
        }
        return s[0] == s[1];
    }
};