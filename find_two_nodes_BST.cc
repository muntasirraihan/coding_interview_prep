#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {};
};

/* perform inorder and reverse_order traverse at the same time */
void find_pair(TreeNode *root, int x, int &a, int &b) {
	a = -1;
	b = -1;
	if (!root) return;

	// keep two stacks for tree traversals
	stack<TreeNode *> inorder_stack, reverse_order_stack;
	TreeNode *inorder_pointer = root;
	TreeNode *reverse_order_pointer = root;

	while (1) {
		while (inorder_pointer) {
			inorder_stack.push(inorder_pointer);
			inorder_pointer = inorder_pointer->left;
		}

		while (reverse_order_pointer) {
			reverse_order_stack.push(reverse_order_pointer);
			reverse_order_pointer = reverse_order_pointer->right;
		}

		// no answer
		if (inorder_stack.empty() || reverse_order_stack.empty()) return;
		
		int current_sum = inorder_stack.top()->val + reverse_order_stack.top()->val;
		if (current_sum == x) {
			// found answer
			a = inorder_stack.top()->val;
			b = reverse_order_stack.top()->val;
			return;
		} else if (current_sum < x) {
			// answer too smaller
			// need to move inorder_pointer pointer to larger value
			inorder_pointer = inorder_stack.top();
			inorder_stack.pop();
			inorder_pointer = inorder_pointer->right;
		} else {
			// answer too big
			// need to move reverse_order_pointer pointer to smaller value
			reverse_order_pointer = reverse_order_stack.top();
			reverse_order_stack.pop();
			reverse_order_pointer = reverse_order_pointer->left;			
		}
	}
}

int main() {
	TreeNode *root = new TreeNode(9);
	root->left = new TreeNode(5);
	root->right = new TreeNode(12);

	root->left->left = new TreeNode(2);
	root->left->right = new TreeNode(7);

	root->right->left = new TreeNode(11);
	root->right->right = new TreeNode(13);

	int a, b;
	find_pair(root, 16, a, b);
	cout << a << "+" << b << endl;

}