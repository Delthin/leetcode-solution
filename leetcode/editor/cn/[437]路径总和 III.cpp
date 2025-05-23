/**
给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。 

 路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。 

 

 示例 1： 

 

 
输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于 8 的路径有 3 条，如图所示。
 

 示例 2： 

 
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3
 

 

 提示: 

 
 二叉树的节点个数的范围是 [0,1000] 
 
 -10⁹ <= Node.val <= 10⁹ 
 -1000 <= targetSum <= 1000 
 

 Related Topics 树 深度优先搜索 二叉树 👍 1988 👎 0

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
namespace solution437{
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
    public:
        unordered_map<long long, int> prefix;

        int dfs(TreeNode *root, long long curr, int targetSum) {
            if (!root) {
                return 0;
            }

            int ret = 0;
            curr += root->val;
            if (prefix.count(curr - targetSum)) {
                ret = prefix[curr - targetSum];
            }

            prefix[curr]++;
            ret += dfs(root->left, curr, targetSum);
            ret += dfs(root->right, curr, targetSum);
            prefix[curr]--;

            return ret;
        }

        int pathSum(TreeNode* root, int targetSum) {
            prefix[0] = 1;
            return dfs(root, 0, targetSum);
        }
    };
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution437;
int main() {
    Solution solution;
    cout << solution.pathSum(new TreeNode(1, new TreeNode(1), new TreeNode(1)), 1);
    return 0;
}