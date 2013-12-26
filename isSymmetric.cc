/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool helper(TreeNode *lp, TreeNode *rp) {
        if (lp == NULL && rp == NULL) return true;
        
        if ((lp == NULL && rp != NULL) || (lp != NULL && rp == NULL)) return false;
        
        if (lp->val != rp->val) return false;
        
        return ((helper(lp->left, rp->right) && helper(lp->right, rp->left)));
        
    }
    bool isSymmetric(TreeNode *root) {
        if (root == NULL) return true;
        
        return helper(root->left, root->right);
        
    }
};