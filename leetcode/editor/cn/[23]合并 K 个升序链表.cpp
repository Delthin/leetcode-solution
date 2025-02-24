/**
给你一个链表数组，每个链表都已经按升序排列。 

 请你将所有链表合并到一个升序链表中，返回合并后的链表。 

 

 示例 1： 

 输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6
 

 示例 2： 

 输入：lists = []
输出：[]
 

 示例 3： 

 输入：lists = [[]]
输出：[]
 

 

 提示： 

 
 k == lists.length 
 0 <= k <= 10^4 
 0 <= lists[i].length <= 500 
 -10^4 <= lists[i][j] <= 10^4 
 lists[i] 按 升序 排列 
 lists[i].length 的总和不超过 10^4 
 

 Related Topics 链表 分治 堆（优先队列） 归并排序 👍 2961 👎 0

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
namespace solution23{
//leetcode submit region begin(Prohibit modification and deletion)
class Solution {
private:
    ListNode* merge(ListNode* l_node, ListNode* r_node) {
        if (!l_node || !r_node) return l_node ? l_node : r_node;
        ListNode* dummy_node = new ListNode(0);
        ListNode* prev = dummy_node;
        while (l_node && r_node) {
            if (l_node->val < r_node->val) {
                prev->next = l_node;
                prev = l_node;
                l_node = l_node->next;
            } else {
                prev->next = r_node;
                prev = r_node;
                r_node = r_node->next;
            }
        }
        prev->next = l_node ? l_node : r_node;
        ListNode* ans = dummy_node->next;
        delete dummy_node;
        return ans;
    }
    ListNode* mergeSort(int l, int r, vector<ListNode*> &lists) {
        if (l == r) {
            return lists[l];
        }
        if (l > r) return nullptr;
        int mid = l + (r - l) / 2;
        return merge(mergeSort(l, mid,lists), mergeSort(mid + 1, r, lists));
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) return nullptr;
        return mergeSort(0, lists.size() - 1, lists);
    }
};
//leetcode submit region end(Prohibit modification and deletion)

}

using namespace solution23;
int main() {
    Solution solution;

    return 0;
}