//给你一个二叉树的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。 
//
// 叶子节点 是指没有子节点的节点。 
//
// 示例 1： 
// 
// 
//输入：root = [1,2,3,null,5]
//输出：["1->2->5","1->3"]
// 
//
// 示例 2： 
//
// 
//输入：root = [1]
//输出：["1"]
// 
//
// 
//
// 提示： 
//
// 
// 树中节点的数目在范围 [1, 100] 内 
// -100 <= Node.val <= 100 
// 
//
// Related Topics 树 深度优先搜索 字符串 回溯 二叉树 👍 1207 👎 0

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
namespace solution257{
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
    vector<int> path;
    vector<string> ret;
    void addPath() {
        string str;
        str+= to_string(path[0]);
        for (int i = 1; i < path.size(); i++) {
            str += "->";
            str += to_string(path[i]);
        }
        ret.push_back(str);
    }
    void dfs(TreeNode* root) {
        if (root == nullptr) return;
        path.push_back(root->val);
        if (!root->left && !root->right) {
            addPath();
            path.pop_back();
            return;
        }
        if (root->left) {
            dfs(root->left);
        }
        if (root->right) {
            dfs(root->right);
        }
        path.pop_back();
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        dfs(root);
        return ret;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution257;
int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);

    Solution solution;
    vector<string> paths = solution.binaryTreePaths(root);

    // Print the generated paths.
    for (const auto& path : paths) {
        cout << path << endl;
    }
    return 0;
}