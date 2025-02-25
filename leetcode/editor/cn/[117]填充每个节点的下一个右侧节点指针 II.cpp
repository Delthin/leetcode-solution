//给定一个二叉树： 
//
// 
//struct Node {
//  int val;
//  Node *left;
//  Node *right;
//  Node *next;
//} 
//
// 填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL 。 
//
// 初始状态下，所有 next 指针都被设置为 NULL 。 
//
// 
//
// 示例 1： 
// 
// 
//输入：root = [1,2,3,4,5,null,7]
//输出：[1,#,2,3,#,4,5,7,#]
//解释：给定二叉树如图 A 所示，你的函数应该填充它的每个 next 指针，以指向其下一个右侧节点，如图 B 所示。序列化输出按层序遍历顺序（由 next 指
//针连接），'#' 表示每层的末尾。 
//
// 示例 2： 
//
// 
//输入：root = []
//输出：[]
// 
//
// 
//
// 提示： 
//
// 
// 树中的节点数在范围 [0, 6000] 内 
// -100 <= Node.val <= 100 
// 
//
// 进阶： 
//
// 
// 你只能使用常量级额外空间。 
// 使用递归解题也符合要求，本题中递归程序的隐式栈空间不计入额外空间复杂度。 
// 
//
// 
// 
//
// Related Topics 树 深度优先搜索 广度优先搜索 链表 二叉树 👍 904 👎 0

#include <bits/stdc++.h>

using namespace std;
  
namespace solution117{
//leetcode submit region begin(Prohibit modification and deletion)
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    Node* connect(Node* root) {
            queue<Node*> que;
            if (root != NULL) que.push(root);
            while (!que.empty()) {
                int size = que.size();
                // vector<int> vec;
                Node* nodePre;
                Node* node;
                for (int i = 0; i < size; i++) {
                    if (i == 0) {
                        nodePre = que.front(); // 取出一层的头结点
                        que.pop();
                        node = nodePre;
                    } else {
                        node = que.front();
                        que.pop();
                        nodePre->next = node; // 本层前一个节点next指向本节点
                        nodePre = nodePre->next;
                    }
                    if (node->left) que.push(node->left);
                    if (node->right) que.push(node->right);
                }
                nodePre->next = NULL; // 本层最后一个节点指向NULL
            }
            return root;
        }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution117;
int main() {
    Solution solution;

    return 0;
}