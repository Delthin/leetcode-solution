/**
给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回
其根节点。 

 

 示例 1: 
 
 
输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]
 

 示例 2: 

 
输入: preorder = [-1], inorder = [-1]
输出: [-1]
 

 

 提示: 

 
 1 <= preorder.length <= 3000 
 inorder.length == preorder.length 
 -3000 <= preorder[i], inorder[i] <= 3000 
 preorder 和 inorder 均 无重复 元素 
 inorder 均出现在 preorder 
 preorder 保证 为二叉树的前序遍历序列 
 inorder 保证 为二叉树的中序遍历序列 
 

 Related Topics 树 数组 哈希表 分治 二叉树 👍 2462 👎 0

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
namespace solution105{
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return split(preorder, inorder, 0, preorder.size());
    }
    TreeNode* split(vector<int>& preorder, vector<int>& inorder, int l, int r) {
        if (l == r) {
            return nullptr;
        }
        auto* node = new TreeNode(preorder[index]);
        if (l == r - 1) {
            index++;
            return node;
        }
        int inorder_index = l;
        for (; inorder_index < r; inorder_index++) {
            if (inorder[inorder_index] == preorder[index]) {
                break;
            }
        }
        if (inorder_index == r) {
            return nullptr;
        }
        index++;
        node->left = split(preorder, inorder, l, inorder_index);
        node->right = split(preorder, inorder, inorder_index + 1, r);
        return node;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution105;
int main() {
    Solution solution;
    vector<int> preorder = {1, 2};
    vector<int> inorder = {2, 1};
    solution.buildTree(preorder, inorder);
    return 0;
}