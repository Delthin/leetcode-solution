/**
给你一个非递减的 有序 整数数组，已知这个数组中恰好有一个整数，它的出现次数超过数组元素总数的 25%。 

 请你找到并返回这个整数 

 

 示例： 

 
输入：arr = [1,2,2,6,6,6,6,7,10]
输出：6
 

 

 提示： 

 
 1 <= arr.length <= 10^4 
 0 <= arr[i] <= 10^5 
 

 Related Topics 数组 👍 99 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution1287{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int findSpecialInteger(vector<int>& arr) {
        int times = 1, last = arr[0];
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            if (arr[i] == last) {
                if (++times > n / 4) {
                    return last;
                }
            } else {
                times = 1;
                last = arr[i];
            }
        }
        return last;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution1287;
int main() {
    Solution solution;

    return 0;
}