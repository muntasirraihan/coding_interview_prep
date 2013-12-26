#include <iostream>
#include <queue>
#include <climits>

#define NULL_VAL (INT_MAX)
#define CHECK_NODE (new TreeNode(NULL_VAL))

using namespace std;


void print_vector(const vector<int> &v) {
    //cout << "print vector ";
    for (int x : v) cout << x << " ";
    cout << endl;
}


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};



bool check_layer_is_palindrome(const vector<int> &layer) {
    int size = layer.size();

    //print_vector(layer);
    
    if (size == 0) return true;
    
    for (int i = 0; i < size / 2; ++i) {
        if (layer[i] != layer[size - i - 1]) return false;
    }
    
    return true;
}



class Solution {
public:
    
    bool isSymmetric(TreeNode *root) {
        if (root == NULL) return true;

        queue<TreeNode *> q;
        q.push(root);
        q.push(CHECK_NODE);
        
        vector<int> layer;
        
        while (!q.empty()) {
            TreeNode *current = q.front(); q.pop();
            
            if (current->val == NULL_VAL) {
                if (!check_layer_is_palindrome(layer)) return false;
                layer.clear();
                //cout << "here " << layer.size() << endl;
                if (!q.empty()) q.push(CHECK_NODE);
                continue;
            }
            
            if (current->left != NULL) {
                layer.push_back(current->left->val);
                q.push(current->left);
            } else {
                layer.push_back(NULL_VAL);
            }

            if (current->right != NULL) {
                layer.push_back(current->right->val);
                q.push(current->right);
            } else {
                layer.push_back(NULL_VAL);
            }
        }
    
        return true;
    }
};

int main() {
    Solution s;
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->right->right = new TreeNode(3);

    cout << s.isSymmetric(root) << endl;
}