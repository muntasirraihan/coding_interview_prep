/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
#include <climits>
#include <queue>

class Solution {
    TreeNode *MARKER = new TreeNode(INT_MAX);
    vector<vector<int> > solution;
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        if (root == NULL) return solution;
        
        queue<TreeNode *> q;
        q.push(root);
        q.push(MARKER);
        
        vector<int> current_level;
        while (!q.empty()) {
            TreeNode *current = q.front(); q.pop();
            
            if (current == MARKER) {
                solution.push_back(current_level);
                current_level.clear();
                if (q.empty()) {
                    break;
                } else {
                    q.push(MARKER);
                }
            } else {
                current_level.push_back(current->val);
                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
        }
        
        return solution;
    }
};