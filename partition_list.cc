#include <cstdlib>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        if (head == NULL) return head;

        ListNode *lessHead = NULL;
        ListNode *moreHead = NULL;
        ListNode *lessPointer = NULL;
        ListNode *morePointer = NULL;
        
        // still has nodes in the list
        while (head != NULL) {
            // see smaller val
            if (head->val < x) {
                if (!lessHead) {
                    lessHead = new ListNode(head->val);
                    lessPointer = lessHead;
                } else {
                    lessPointer->next = new ListNode(head->val);
                    lessPointer = lessPointer->next;
                }
            } else {
            // see equal or larger val
                if (!moreHead) {
                    moreHead = new ListNode(head->val);
                    morePointer = moreHead;
                } else {
                    morePointer->next = new ListNode(head->val);
                    morePointer = morePointer->next;
                }
            }
            
            head = head->next;
        }
        
        if (lessHead == NULL) {

            return moreHead;
        } else if (moreHead == NULL) {
            return lessHead;
        }
        
        lessPointer->next = moreHead;
        return lessHead;
    }
};


int main() {
    Solution s;
    ListNode *head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    ListNode *result = s.partition(head, 3);
    while (result != NULL) {
        cout << result->val << endl;
        result = result->next;
    }
}