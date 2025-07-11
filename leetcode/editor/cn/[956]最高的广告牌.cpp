/**
你正在安装一个广告牌，并希望它高度最大。这块广告牌将有两个钢制支架，两边各一个。每个钢支架的高度必须相等。 

 你有一堆可以焊接在一起的钢筋 rods。举个例子，如果钢筋的长度为 1、2 和 3，则可以将它们焊接在一起形成长度为 6 的支架。 

 返回 广告牌的最大可能安装高度 。如果没法安装广告牌，请返回 0 。 

 

 示例 1： 

 
输入：[1,2,3,6]
输出：6
解释：我们有两个不相交的子集 {1,2,3} 和 {6}，它们具有相同的和 sum = 6。
 

 示例 2： 

 
输入：[1,2,3,4,5,6]
输出：10
解释：我们有两个不相交的子集 {2,3,5} 和 {4,6}，它们具有相同的和 sum = 10。 

 示例 3： 

 
输入：[1,2]
输出：0
解释：没法安装广告牌，所以返回 0。 

 

 提示： 

 
 0 <= rods.length <= 20 
 1 <= rods[i] <= 1000 
 sum(rods[i]) <= 5000 
 

 Related Topics 数组 动态规划 👍 205 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
  
namespace solution956{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
public:
    int tallestBillboard(vector<int>& rods) {
        // 没看懂思密达
        int sum =0;
        for(int& i:rods){
            sum+=i;
        }

        vector<int> mindrop(sum+1,INT_MAX);
        vector<bool> canget(sum+1,false);
        mindrop[0] = 0;
        canget[0] = true;
        for(int& i :rods){
            for(int j=sum;j>=0;j--){
                if(j-i>=0&&canget[j-i]){
                    //可以将该支架抛弃。差值变化+=支架长度
                    canget[j]=true;
                    mindrop[j]=min(mindrop[j],mindrop[j-i]+i);
                }
                if(j-2*i>=0&&canget[j-2*i]){
                    //可以将该支架从左边移到右边。差值变化+=2*支架长度
                    canget[j]=true;
                    mindrop[j]=min(mindrop[j],mindrop[j-2*i]);
                }
            }
        }
        return (sum-mindrop[sum])/2;

    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution956;
int main() {
    Solution solution;

    return 0;
}