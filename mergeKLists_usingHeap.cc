/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
 
#include <queue>

typedef pair<int, ListNode *> HeapNode;

struct HeapNodeComparator {
    bool operator()(const HeapNode &p1, const HeapNode &p2) {
        return (p1.first > p2.first);
    }
};

typedef priority_queue<HeapNode, vector<HeapNode>, HeapNodeComparator> heap_type;

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        if (lists.empty()) return NULL;
        
        // initialize the heap with k first elements
        vector<HeapNode> firstKElements;
        for (int i = 0; i < lists.size(); ++i) {
            if (lists[i]) {
                firstKElements.push_back(make_pair(lists[i]->val, lists[i]));
            }
        }
        heap_type pq(firstKElements.begin(), firstKElements.end());
  
        // start pop off from the heap to result list
        ListNode *result_head = NULL;
        ListNode *result_tail = NULL;
        while (!pq.empty()) {
            HeapNode current = pq.top(); pq.pop();
            ListNode *currentListNode = current.second;
            
            // insert min element to result
            if (result_head == NULL && result_tail == NULL) {
                result_head = currentListNode;
                result_tail = currentListNode;
            } else {
                result_tail->next = currentListNode;
                result_tail = result_tail->next;
            }
            
            if (currentListNode->next) {
                // insert next element from the list
                pq.push(make_pair(currentListNode->next->val, currentListNode->next));
            }
        }
        
        return result_head;
    }
};