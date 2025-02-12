/**
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。 

 

 示例 1： 
 
 
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
 

 示例 2： 

 
输入：head = [1], n = 1
输出：[]
 

 示例 3： 

 
输入：head = [1,2], n = 1
输出：[1]
 

 

 提示： 

 
 链表中结点的数目为 sz 
 1 <= sz <= 30 
 0 <= Node.val <= 100 
 1 <= n <= sz 
 

 

 进阶：你能尝试使用一趟扫描实现吗？ 

 Related Topics 链表 双指针 👍 3018 👎 0

*/
#include <bits/stdc++.h>

using namespace std;
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
namespace solution19{
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* fast = head;
        while(n > 0) {
            fast = fast->next;
            n--;
        }
        ListNode* slow = head;
        ListNode* prev = nullptr;
        while(fast != nullptr) {
            fast = fast->next;
            prev = slow;
            slow = slow->next;
        }
        if (prev == nullptr) {
            head = head->next;
            return head;
        }
        prev->next = slow->next;
        slow->next = nullptr;
        return head;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution19;
int main() {
    Solution solution;

    return 0;
}