#include <iostream>

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
    void insertToBST(int x, TreeNode *root) {
        if (x < root->val) {
            if (root->left) {
                insertToBST(x, root->left);
            } else {
                root->left = new TreeNode(x);
            }
        } else {
            if (root->right) {
                insertToBST(x, root->right);
            } else {
                root->right = new TreeNode(x);
            }
        }    
        return;     
    }
public:
    TreeNode *sortedListToBST(ListNode *head) {
        TreeNode *root = NULL;
        while (head != NULL) {
            if (root) {
                insertToBST(head->val, root);
            } else {
                root = new TreeNode(head->val);
            }
            head = head->next;
        }
        return root;
    }
};



int main(int argc, char *argv[]) {
    Solution s;
    ListNode *l = new ListNode(1);
    l->next = new ListNode(3);
    //l->next = new ListNode(0);
    TreeNode *tree = s.sortedListToBST(l);
    cout << tree->val << endl;
}