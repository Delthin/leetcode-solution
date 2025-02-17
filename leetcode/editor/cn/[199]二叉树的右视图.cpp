/**
给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。 

 

 示例 1： 

 
 输入：root = [1,2,3,null,5,null,4] 
 

 输出：[1,3,4] 

 解释： 

 

 示例 2： 

 
 输入：root = [1,2,3,4,null,null,null,5] 
 

 输出：[1,3,4,5] 

 解释： 

 

 示例 3： 

 
 输入：root = [1,null,3] 
 

 输出：[1,3] 

 示例 4： 

 
 输入：root = [] 
 

 输出：[] 

 

 提示: 

 
 二叉树的节点个数的范围是 [0,100] 
 
 -100 <= Node.val <= 100 
 

 Related Topics 树 深度优先搜索 广度优先搜索 二叉树 👍 1161 👎 0

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
namespace solution199{
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        queue<TreeNode*> que;
        if (root == nullptr) {
            return ans;
        }
        que.push(root);
        while(!que.empty()) {
            int floorSize = que.size();
            for (int i = 0; i < floorSize; i++) {
                TreeNode* node = que.front();
                que.pop();
                if (node->left) {
                    que.push(node->left);
                }
                if (node->right) {
                    que.push(node->right);
                }
                if (i == floorSize - 1) {
                    ans.push_back(node->val);
                }
            }
        }
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution199;
int main() {
    Solution solution;

    return 0;
}