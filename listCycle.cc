
#include<iostream>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int v) : val(v), next(NULL) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head) return NULL;
        
        ListNode *fast = head;
        ListNode *slow = head;
        do {
            if (fast->next && fast->next->next) {
                fast = fast->next->next;
            } else {
                return NULL;
            }
            if (slow->next) slow = slow->next;
        } while (fast != slow);
        
        // determine start of cycle
        fast = head;
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
};

int main() {
	Solution s;
	// ListNode * head = new ListNode(3);
	// head->next = new ListNode(2);
	// head->next->next = new ListNode(0);
	// head->next->next->next = new ListNode(-4);
	// head->next->next->next->next = head->next;

	ListNode *head = new ListNode(1);
	head->next = new ListNode(2);
	head->next->next = head;
	s.detectCycle(head);
}