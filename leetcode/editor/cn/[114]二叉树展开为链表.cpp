/**
给你二叉树的根结点 root ，请你将它展开为一个单链表： 

 
 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。 
 展开后的单链表应该与二叉树 先序遍历 顺序相同。 
 

 

 示例 1： 
 
 
输入：root = [1,2,5,3,4,null,6]
输出：[1,null,2,null,3,null,4,null,5,null,6]
 

 示例 2： 

 
输入：root = []
输出：[]
 

 示例 3： 

 
输入：root = [0]
输出：[0]
 

 

 提示： 

 
 树中结点数在范围 [0, 2000] 内 
 -100 <= Node.val <= 100 
 

 

 进阶：你可以使用原地算法（O(1) 额外空间）展开这棵树吗？ 

 Related Topics 栈 树 深度优先搜索 链表 二叉树 👍 1782 👎 0

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
namespace solution114{
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
    TreeNode* rotateTail(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* leftTail = rotateTail(root->left);
        TreeNode* rightTail = rotateTail(root->right);
        if (leftTail == nullptr && rightTail == nullptr) {
            return root;
        }
        if (leftTail == nullptr) {
            return rightTail;
        }
        if (rightTail == nullptr) {
            root->right = root->left;
            root->left = nullptr;
            return leftTail;
        }
        leftTail->right = root->right;
        root->right = root->left;
        root->left = nullptr;
        return rightTail;
    }
public:
    void flatten(TreeNode* root) {
        rotateTail(root);
        return;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution114;
int main() {
    Solution solution;

    return 0;
}