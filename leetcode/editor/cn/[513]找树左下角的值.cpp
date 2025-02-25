//给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值。 
//
// 假设二叉树中至少有一个节点。 
//
// 
//
// 示例 1: 
//
// 
//
// 
//输入: root = [2,1,3]
//输出: 1
// 
//
// 示例 2: 
//
// 
//
// 
//输入: [1,2,3,4,null,5,6,null,null,7]
//输出: 7
// 
//
// 
//
// 提示: 
//
// 
// 二叉树的节点个数的范围是 [1,10⁴] 
// 
// -2³¹ <= Node.val <= 2³¹ - 1 
// 
//
// Related Topics 树 深度优先搜索 广度优先搜索 二叉树 👍 619 👎 0

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
namespace solution513{
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
    int maxDepth = -1;
    int ret = 0;
    void traversal(TreeNode* root, int depth) {
        if (root == nullptr) return;
        if (root->left) {
            depth++;
            traversal(root->left, depth);
            depth--;
        }
        if (root->right) {
            depth++;
            traversal(root->right, depth);
            depth--;
        }
        if (depth > maxDepth) {
            maxDepth = depth;
            ret = root->val;
        }
    }
public:
    int findBottomLeftValue(TreeNode* root) {
        traversal(root, 0);
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution513;
int main() {
    Solution solution;

    return 0;
}