/**
给你一棵二叉树的根节点，返回该树的 直径 。 

 二叉树的 直径 是指树中任意两个节点之间最长路径的 长度 。这条路径可能经过也可能不经过根节点 root 。 

 两节点之间路径的 长度 由它们之间边数表示。 

 

 示例 1： 
 
 
输入：root = [1,2,3,4,5]
输出：3
解释：3 ，取路径 [4,2,1,3] 或 [5,2,1,3] 的长度。
 

 示例 2： 

 
输入：root = [1,2]
输出：1
 

 

 提示： 

 
 树中节点数目在范围 [1, 10⁴] 内 
 -100 <= Node.val <= 100 
 

 Related Topics 树 深度优先搜索 二叉树 👍 1654 👎 0

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
namespace solution543{
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
        int ans;
        int depth(TreeNode* rt){
            if (rt == NULL) {
                return 0; // 访问到空节点了，返回0
            }
            int L = depth(rt->left); // 左儿子为根的子树的深度
            int R = depth(rt->right); // 右儿子为根的子树的深度
            ans = max(ans, L + R + 1); // 计算d_node即L+R+1 并更新ans
            return max(L, R) + 1; // 返回该节点为根的子树的深度
        }
    public:
        int diameterOfBinaryTree(TreeNode* root) {
            ans = 1;
            depth(root);
            return ans - 1;
        }
    };
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution543;
int main() {
    Solution solution;

    return 0;
}