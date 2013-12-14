#include <iostream>
#include <cstdlib>

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
    int maxPathSum(TreeNode *root) {
        int terminated = 0;
        int partOfPath = 0;
        helper(root, terminated, partOfPath);
        // cout << "here " << terminated << endl;
        // cout << "here " << partOfPath << endl;
        return max(terminated, partOfPath);
    }
    
    void helper(TreeNode *root, int &terminated, int &partOfPath) {
        // leaf
        if ((root->left == NULL) && (root->right == NULL)) {
            terminated = root->val;
            partOfPath = root->val;
            //cout << "in " << terminated << endl;
            //cout << "in " << partOfPath << endl;
            return;
        }
        
        // intermediate node
        int left_terminated = 0;
        int left_partOfPath = 0;
        int right_terminated = 0;
        int right_partOfPath = 0;
        if (root->left != NULL) {
            helper(root->left, left_terminated, left_partOfPath);
        }
        if (root->right != NULL) {
            helper(root->right, right_terminated, right_partOfPath);
        }
        
        // return
        // throw away negative left or right path
        left_partOfPath = (left_partOfPath > 0) ? left_partOfPath : 0;
        right_partOfPath = (right_partOfPath > 0) ? right_partOfPath : 0;
        if ((root->left != NULL) && (root->right != NULL))   {
            int self_terminated = left_partOfPath + root->val + right_partOfPath;
            terminated = max(self_terminated, max(left_terminated, right_terminated));
            partOfPath = root->val + max(left_partOfPath, right_partOfPath);
            return;
        } else if (root->left != NULL) {
            int self_terminated = left_partOfPath + root->val;
            terminated = max(self_terminated, left_terminated);
            partOfPath = root->val + left_partOfPath;
            return;
        } else {
            int self_terminated = root->val + right_partOfPath;
            terminated = max(self_terminated, right_terminated);
            partOfPath = root->val + right_partOfPath;
            return;
        }
    }
};

int main() {
    Solution s;
    TreeNode* t = new TreeNode(-2);
    t->left = new TreeNode(-1);
    cout << s.maxPathSum(t) << endl;
}