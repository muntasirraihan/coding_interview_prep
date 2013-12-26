#include <cstdlib>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

    class Solution {
    public:
        ListNode *deleteDuplicates(ListNode *head) {
            if (head == NULL) return head;
            
            unordered_set<int> seen;
            seen.insert(head->val);
            
            ListNode *p = head;
            ListNode *q = head; 
            p = p->next;
            unordered_set<int>::iterator iter;
            while (p != NULL) {
                iter = seen.find(p->val);
                if (iter != seen.end()) {
                    q->next = p->next;
                } else {
                    seen.insert(p->val);
                    q = q->next;
                }
                p = p->next;
            }
            
            return head;
        }
    };



int main() {
    Solution s;
    ListNode* t1 = new ListNode(1);
    ListNode* t2 = new ListNode(1);
    ListNode* t3 = new ListNode(2);
    t1->next = t2;
    t2->next = t3;
    s.deleteDuplicates(t1);
    ListNode *p = t1;
    while (p != NULL) {
        cout << p->val << "-";
        p = p->next;
    }   
}
    