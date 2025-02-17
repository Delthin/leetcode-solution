/**
给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。 

 有效 二叉搜索树定义如下： 

 
 节点的左子树只包含 小于 当前节点的数。 
 节点的右子树只包含 大于 当前节点的数。 
 所有左子树和右子树自身必须也是二叉搜索树。 
 

 

 示例 1： 
 
 
输入：root = [2,1,3]
输出：true
 

 示例 2： 
 
 
输入：root = [5,1,4,null,null,3,6]
输出：false
解释：根节点的值是 5 ，但是右子节点的值是 4 。
 

 

 提示： 

 
 树中节点数目范围在[1, 10⁴] 内 
 -2³¹ <= Node.val <= 2³¹ - 1 
 

 Related Topics 树 深度优先搜索 二叉搜索树 二叉树 👍 2496 👎 0

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
namespace solution98{
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
    int* last = nullptr;
public:
    bool isValidBST(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        if (!isValidBST(root->left)) {
            return false;
        };
        if (last == nullptr) {
            last = new int(root->val);
        } else {
            if (root->val <= *last) {
                return false;
            }
            *last = root->val;
        }
        return isValidBST(root->right);
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution98;
int main() {
    Solution solution;

    return 0;
}