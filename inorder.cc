#include <cstdlib>
#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

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
    vector<int> inorderTraversal(TreeNode *root) {
        vector<int> inorder;
        if (root == NULL) return inorder;
        
        unordered_set<TreeNode *> seen;
        unordered_set<TreeNode *>::iterator iter;
        stack<TreeNode *> s;
        s.push(root);
        
        while (!s.empty()) {
            TreeNode *current = s.top();
          
            iter = seen.find(current);
            if (iter == seen.end() && current->left != NULL) {
                s.push(current->left);
                seen.insert(current);
            } else {
                inorder.push_back(current->val);
                s.pop();
                if (current->right != NULL) {
                    s.push(current->right);
                }
            }
        }
        
        return inorder;
    }
};



int main() {
    Solution s;
    TreeNode* t1 = new TreeNode(1);
    vector<int> v = s.inorderTraversal(t1);
    for (int x : v) {
       cout << x << " " << endl;
    }
}