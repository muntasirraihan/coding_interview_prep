/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

class Solution {
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        
        ListNode *result, *tail, *p, *q;
        if (l1->val < l2->val) {
            result = l1;
            tail = l1;
            p = l1->next;
            q = l2;
        } else {
            result = l2;
            tail = l2;
            p = l1;
            q = l2->next;
        }

        while (p && q) {
            if (p->val < q->val) {
                tail->next = p;
                p = p->next;
            } else {
                tail->next = q;
                q = q->next;
            }
            tail = tail->next;
        }
        
        if (!p && q) tail->next = q;
        if (!q && p) tail->next = p;
        
        return result;
    }

public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty()) return NULL;
        if (lists.size() == 1) return lists[0];
        
        // pairwise merge lists
        int k = lists.size();
        vector<ListNode *> newLists;
        for (int i = 0; i < k / 2; ++i) {
                ListNode *l1 = lists[2 * i];
                ListNode *l2 = lists[2 * i + 1];
                ListNode *result = mergeTwoLists(l1, l2);
                newLists.push_back(result);
        }
        
        // treat odd k case
        if (k % 2 == 1) {
            ListNode *oddOneOut = lists[k - 1];
            newLists[k / 2 - 1] = mergeTwoLists(newLists[k / 2 - 1], oddOneOut);
        }
        
        return mergeKLists(newLists);
 
    }
};