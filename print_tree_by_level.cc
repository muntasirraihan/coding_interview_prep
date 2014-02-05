/* Print a tree like (Parent ( leftchild (leftchild, rightchild), rightchild(leftchild,rightchild) ) ) */

#include <string>
#include <queue>
#include <iostream>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {};
};


void print_tree_by_level(TreeNode *root) {
	if (!root) return;

	queue<TreeNode *> q;
	q.push(root);
	int current_level_count = 1;
	int next_level_count = 0;

	while (!q.empty()) {
		TreeNode *current = q.front(); q.pop();
		cout << current->val;
		current_level_count--;

		if (current->left) {
			q.push(current->left);
			next_level_count++;
		}

		if (current->right) {
			q.push(current->right);
			next_level_count++;
		}

		if (current_level_count == 0) {
			cout << endl;
			current_level_count = next_level_count;
			next_level_count = 0;
		} else {
			cout << " ";
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

	print_tree_by_level(root);

}