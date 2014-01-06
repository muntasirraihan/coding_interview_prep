#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    vector<vector<int> > solution;
public:
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        if (!root) return solution;
        
        // TreeNode *MARKER = new TreeNode(INT_MAX);
        
        // circular array as queue
        int N = 10;
        TreeNode *queue[N];
        int head = 0;
        queue[head] = root;
        queue[head + 1] = NULL;
        int tail = 2;
        
        vector<int> new_layer;
        while (head != tail) {
            cout << head << " " << tail << endl;
            TreeNode *current = queue[head];
            head++; head %= 10;
            
            if (current == NULL) {
                solution.insert(solution.begin(), new_layer);
                new_layer.clear();
                continue;
            } else {
                new_layer.push_back(current->val);
                if (current->left) {
                    queue[tail] = current->left;
                    tail++; tail %= 10;
                }
                if (current->right) {
                    queue[tail] = current->right;
                    tail++; tail %= 10;
                }
                if (queue[(tail - 1 + N) % N] != NULL) {
                    queue[tail] = NULL;
                    tail++; tail %= 10;
                }
            }
        }
        
        return solution;
        
    }
};

int main() {
    Solution s;
    TreeNode *root = new TreeNode(1);
    //root->left = new TreeNode(2);
    s.levelOrderBottom(root);
}