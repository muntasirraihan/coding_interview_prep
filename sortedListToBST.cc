#include<iostream>
#include<queue>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    TreeNode *sortedListToBSTHelper(ListNode **headRef, int n) {
        if (n <= 0) return NULL;
        
        TreeNode *left = sortedListToBSTHelper(headRef, n/2);
        
        TreeNode *root = new TreeNode((*headRef)->val);
        // important to shift headRef for right subtree construction
        *headRef = (*headRef)->next;
        
        TreeNode *right = sortedListToBSTHelper(headRef, n - n/2 - 1);
        
        root->left = left;
        root->right = right;
        
        return root;
                
    }
    
    int countNumberNodes(ListNode *head) {
        int i = 0;
        while (head) {
            i++;
            head = head->next;
        }
        return i;
    }

public:
    TreeNode *sortedListToBST(ListNode *head) {
        if (!head) return NULL;
        
        int n = countNumberNodes(head);
        return sortedListToBSTHelper(&head, n);
    }
    void inorder(TreeNode *root) {
        if (!root) return;

        if (root->left) inorder(root->left);
        cout << root->val << " ";
        if (root->right) inorder(root->right);
        return;
    }

    void postorder(TreeNode *root) {
        if (!root) return;

        if (root->left) inorder(root->left);
        if (root->right) inorder(root->right);
        cout << root->val << " ";
        
        return;
    }

    void BFS(TreeNode *root) {
        if (!root) return;

        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *current = q.front(); q.pop();
            cout << current->val << " ";
            if (current->left) q.push(current->left); 
            if (current->right) q.push(current->right);
        }
    }
};

int main() {
    Solution s;
    ListNode *head, *p;
    head = new ListNode(1);
    p = head;
    head->next = new ListNode(2);
    head = head->next;

    head->next = new ListNode(3);
    head = head->next;

    head->next = new ListNode(4);
    head = head->next;

    head->next = new ListNode(5);
    head = head->next;

    head->next = new ListNode(6);
    head = head->next;

    head->next = new ListNode(7);
    head = head->next;

    TreeNode *BST = s.sortedListToBST(p);

    s.inorder(BST);cout << endl;
    s.postorder(BST);cout << endl;
    s.BFS(BST);cout << endl;

    // test postorder
    TreeNode *t = new TreeNode(4);

    t->left = new TreeNode(2);
    t->left->left = new TreeNode(1);
    t->left->right = new TreeNode(3);

    t->right = new TreeNode(6);
    t->right->left = new TreeNode(5);
    t->right->right = new TreeNode(7);
    s.postorder(t);cout << endl;
    s.BFS(t);
}