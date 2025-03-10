/**
小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为
 root 。 

 除了
 root 之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果 两个直接相连的房子
在同一天晚上被打劫 ，房屋将自动报警。 

 给定二叉树的 root 。返回 在不触动警报的情况下 ，小偷能够盗取的最高金额 。 

 

 示例 1: 

 

 
输入: root = [3,2,3,null,3,null,1]
输出: 7 
解释: 小偷一晚能够盗取的最高金额 3 + 3 + 1 = 7 

 示例 2: 

 

 
输入: root = [3,4,5,1,3,null,1]
输出: 9
解释: 小偷一晚能够盗取的最高金额 4 + 5 = 9
 

 

 提示： 

 
 

 
 树的节点数在 [1, 10⁴] 范围内 
 0 <= Node.val <= 10⁴ 
 

 Related Topics 树 深度优先搜索 动态规划 二叉树 👍 2057 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
namespace solution337{
//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
private:
    pair<int, int> robTree(TreeNode* cur) {
        if (cur == nullptr) return {0, 0};
        auto left = robTree(cur->left);
        auto right = robTree(cur->right);
        int valUse = cur->val + left.second + right.second;
        int valNoUse = max(left.first, left.second) + max(right.first, right.second);
        return {valUse, valNoUse};
    }
public:
    int rob(TreeNode* root) {
        auto [valNoUse, valUse] = robTree(root);
        return max(valNoUse, valUse);
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution337;
int main() {
    Solution solution;

    return 0;
}