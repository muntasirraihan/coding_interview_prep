#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;
// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        // root
        if ((p == NULL) && (q == NULL)) {
            return true;
        }
        
        if ((p == NULL) != (q == NULL)) {
            return false;
        }
        
        cout << p->val << endl;
        cout << q->val << endl;

        // root val
        if (p->val != q->val) {
            return false;
        }
        
        // has left
        if ((p->left == NULL) != (q->left == NULL)) {
            return false;
        }
        
        // has right
        if ((p->right == NULL) != (q->right == NULL)) {
            return false;
        }
        
        // compile results from subtree
        bool r1 = true, r2 = true;
        
        if (p->left != NULL) {
            r1 = isSameTree(p->left, q->left);
        }
        
        if (p->right != NULL) {
            r2 = isSameTree(p->right, q->right);
        }
        
        return (r1 == r2);
    }
};


int main() {
    Solution s;
    TreeNode* t1 = new TreeNode(0);
    TreeNode* t2 = new TreeNode(1);
    cout << s.isSameTree(t1, t2) << endl;
}