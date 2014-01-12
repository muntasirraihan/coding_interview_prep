/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <stack>
class Solution {
    vector<int> solution;
    unordered_set<TreeNode *> visited;
public:

    vector<int> postorderTraversal(TreeNode *root) {
        if (root == NULL) return solution;
        
        stack<TreeNode *> s;
        s.push(root);
        
        while (!s.empty()) {
            TreeNode *current = s.top(); s.pop();
            if (current->left == NULL && current->right == NULL) {
                solution.push_back(current->val);
                continue;
            }
            
            if (visited.find(current) == visited.end()) {
                s.push(current);
                if (current->right) s.push(current->right);
                if (current->left) s.push(current->left);
                visited.insert(current);
            } else {
                solution.push_back(current->val);
            }
        }
        
        return solution;
    }
};