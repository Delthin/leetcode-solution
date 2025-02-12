/**
给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。 

 

 示例 1： 
 
 
输入：head = [1,2,2,1]
输出：true
 

 示例 2： 
 
 
输入：head = [1,2]
输出：false
 

 

 提示： 

 
 链表中节点数目在范围[1, 10⁵] 内 
 0 <= Node.val <= 9 
 

 

 进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？ 

 Related Topics 栈 递归 链表 双指针 👍 1999 👎 0

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

namespace solution234{
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
    bool isPalindrome(ListNode* head) {
        int n = 1;
        ListNode* ptr = head;
        while(ptr->next) {
            ptr = ptr->next;
            n++;
        }
        ptr = head;
        for (int i = 0; i < (n - 1) / 2; i++) {
            ptr = ptr->next;
        }
        ListNode *next = ptr->next;
        ptr->next = nullptr;
        ptr = next;
        ListNode* new_head = head;
        for (int i = 0; i < n / 2; i++) {
            next = ptr->next;
            ptr->next = new_head;
            new_head = ptr;
            ptr = next;
        }
        for (int i = 0; i < n / 2; i++) {
            if (head->val != new_head->val) {
                return false;
            }
            head = head->next;
            new_head = new_head->next;
        }
        return true;
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution234;
int main() {
    Solution solution;
    ListNode node21(1);
    ListNode node22(2, &node21);
    ListNode node12(2, &node22);
    ListNode node11(1, &node12);
    cout << solution.isPalindrome(&node11);
    return 0;
}