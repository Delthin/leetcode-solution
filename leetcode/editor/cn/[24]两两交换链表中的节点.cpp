/**
给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。 

 

 示例 1： 
 
 
输入：head = [1,2,3,4]
输出：[2,1,4,3]
 

 示例 2： 

 
输入：head = []
输出：[]
 

 示例 3： 

 
输入：head = [1]
输出：[1]
 

 

 提示： 

 
 链表中节点的数目在范围 [0, 100] 内 
 0 <= Node.val <= 100 
 

 Related Topics 递归 链表 👍 2343 👎 0

*/
#include <bits/stdc++.h>
struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};
using namespace std;
  
namespace solution24{
//leetcode submit region begin(Prohibit modification and deletion)
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* temp = dummyHead;
        while (temp->next != nullptr && temp->next->next != nullptr) {
            ListNode* node1 = temp->next;
            ListNode* node2 = temp->next->next;
            temp->next = node2;
            node1->next = node2->next;
            node2->next = node1;
            temp = node1;
        }
        ListNode* ans = dummyHead->next;
        delete dummyHead;
        return ans;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution24;
int main() {
    Solution solution;

    return 0;
}