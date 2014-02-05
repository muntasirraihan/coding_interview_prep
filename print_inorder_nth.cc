/* Print a tree like (Parent ( leftchild (leftchild, rightchild), rightchild(leftchild,rightchild) ) ) */

#include <string>
#include <stack>
#include <iostream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {};
};


void print_inorder_nth(TreeNode *root, int n) {
	if (!root) return;
	if (n < 0) return;

	stack<TreeNode *> inorder_stack;
	TreeNode *ptr = root;

	while (1) {
		while (ptr) {
			inorder_stack.push(ptr);
			ptr = ptr->left;
		}

		if (inorder_stack.empty()) {
			cout << "n is larger than tree size " << endl;
			return;
		}

		TreeNode *current = inorder_stack.top();
		inorder_stack.pop();

		// if found, print and return
		if (n == 0) {
			cout << current->val << endl;
			return;
		}

		// otherwise decrement n
		n--;
		ptr = current->right;
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

	print_inorder_nth(root, 4);

}