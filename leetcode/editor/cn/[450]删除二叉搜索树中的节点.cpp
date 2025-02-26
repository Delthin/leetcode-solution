//给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的
//根节点的引用。 
//
// 一般来说，删除节点可分为两个步骤： 
//
// 
// 首先找到需要删除的节点； 
// 如果找到了，删除它。 
// 
//
// 
//
// 示例 1: 
//
// 
//
// 
//输入：root = [5,3,6,2,4,null,7], key = 3
//输出：[5,4,6,2,null,null,7]
//解释：给定需要删除的节点值是 3，所以我们首先找到 3 这个节点，然后删除它。
//一个正确的答案是 [5,4,6,2,null,null,7], 如下图所示。
//另一个正确答案是 [5,2,6,null,4,null,7]。
//
//
// 
//
// 示例 2: 
//
// 
//输入: root = [5,3,6,2,4,null,7], key = 0
//输出: [5,3,6,2,4,null,7]
//解释: 二叉树不包含值为 0 的节点
// 
//
// 示例 3: 
//
// 
//输入: root = [], key = 0
//输出: [] 
//
// 
//
// 提示: 
//
// 
// 节点数的范围 [0, 10⁴]. 
// -10⁵ <= Node.val <= 10⁵ 
// 节点值唯一 
// root 是合法的二叉搜索树 
// -10⁵ <= key <= 10⁵ 
// 
//
// 
//
// 进阶： 要求算法时间复杂度为 O(h)，h 为树的高度。 
//
// Related Topics 树 二叉搜索树 二叉树 👍 1410 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution450{
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
        TreeNode* deleteNode(TreeNode* root, int key) {
            if (root == nullptr) return root; // 第一种情况：没找到删除的节点，遍历到空节点直接返回了
            if (root->val == key) {
                // 第二种情况：左右孩子都为空（叶子节点），直接删除节点， 返回NULL为根节点
                if (root->left == nullptr && root->right == nullptr) {
                    ///! 内存释放
                    delete root;
                    return nullptr;
                }
                // 第三种情况：其左孩子为空，右孩子不为空，删除节点，右孩子补位 ，返回右孩子为根节点
                else if (root->left == nullptr) {
                    auto retNode = root->right;
                    ///! 内存释放
                    delete root;
                    return retNode;
                }
                // 第四种情况：其右孩子为空，左孩子不为空，删除节点，左孩子补位，返回左孩子为根节点
                else if (root->right == nullptr) {
                    auto retNode = root->left;
                    ///! 内存释放
                    delete root;
                    return retNode;
                }
                // 第五种情况：左右孩子节点都不为空，则将删除节点的左子树放到删除节点的右子树的最左面节点的左孩子的位置
                // 并返回删除节点右孩子为新的根节点。
                else {
                    TreeNode* cur = root->right; // 找右子树最左面的节点
                    while(cur->left != nullptr) {
                        cur = cur->left;
                    }
                    cur->left = root->left; // 把要删除的节点（root）左子树放在cur的左孩子的位置
                    TreeNode* tmp = root;   // 把root节点保存一下，下面来删除
                    root = root->right;     // 返回旧root的右孩子作为新root
                    delete tmp;             // 释放节点内存（这里不写也可以，但C++最好手动释放一下吧）
                    return root;
                }
            }
            if (root->val > key) root->left = deleteNode(root->left, key);
            if (root->val < key) root->right = deleteNode(root->right, key);
            return root;
        }
    };
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution450;
int main() {
    Solution solution;

    return 0;
}