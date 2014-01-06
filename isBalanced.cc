#include <iostream>
#include <cstdlib>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}    
};
 
class Solution {
public:
    int findHeight(TreeNode *root, bool &isBalanced) {
         cout << root->val << endl;

        if (root->left == NULL && root->right == NULL) {
            isBalanced = true;
            return 0;
        }
        
        int ld = 0;
        int rd = 0;
        if (root->left != NULL) {
            bool isLeftBalanced;
            ld = findHeight(root->left, isLeftBalanced) + 1;
            isBalanced &= isLeftBalanced;
        }
        if (root->right != NULL) {
            bool isRightBalanced;
            rd = findHeight(root->right, isRightBalanced) + 1;
            isBalanced &= isRightBalanced;
        }
        
        if (abs(ld - rd) > 1) {
            isBalanced = false;
        }


        
        return max(ld, rd);
    }

    bool isBalanced(TreeNode *root) {
        if (root == NULL) return true;
        
        bool f;
        cout << findHeight(root, f) << endl;
        return f;
    }
};

int main() {
    TreeNode *root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(3);
    root->left->left->left = new TreeNode(4);
    root->left->left->right = new TreeNode(4);
    Solution s;
    cout << s.isBalanced(root) << endl;
}