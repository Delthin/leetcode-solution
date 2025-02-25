//给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历， postorder 是同一棵树的后序遍历，请你构造并
//返回这颗 二叉树 。 
//
// 
//
// 示例 1: 
// 
// 
//输入：inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
//输出：[3,9,20,null,null,15,7]
// 
//
// 示例 2: 
//
// 
//输入：inorder = [-1], postorder = [-1]
//输出：[-1]
// 
//
// 
//
// 提示: 
//
// 
// 1 <= inorder.length <= 3000 
// postorder.length == inorder.length 
// -3000 <= inorder[i], postorder[i] <= 3000 
// inorder 和 postorder 都由 不同 的值组成 
// postorder 中每一个值都在 inorder 中 
// inorder 保证是树的中序遍历 
// postorder 保证是树的后序遍历 
// 
//
// Related Topics 树 数组 哈希表 分治 二叉树 👍 1309 👎 0

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
namespace solution106{
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
    int index = 0;
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        index = inorder.size() - 1;
        return split(postorder, inorder, 0, postorder.size());
    }
    TreeNode* split(vector<int>& postorder, vector<int>& inorder, int l, int r) {
        if (l == r) {
            return nullptr;
        }
        auto* node = new TreeNode(postorder[index]);
        if (l == r - 1) {
            index--;
            return node;
        }
        int inorder_index = l;
        for (; inorder_index < r; inorder_index++) {
            if (inorder[inorder_index] == postorder[index]) {
                break;
            }
        }
        if (inorder_index == r) {
            return nullptr;
        }
        index--;
        node->right = split(postorder, inorder, inorder_index + 1, r);
        node->left = split(postorder, inorder, l, inorder_index);
        return node;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution106;
int main() {
    Solution solution;
    vector<int> inorder   = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};
    cout << solution.buildTree(inorder, postorder);
    return 0;
}