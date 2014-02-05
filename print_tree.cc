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

string print_tree(TreeNode *root) {
	if (!root) return " ";

	string s = to_string(root->val);

	if (root->left) {
		s += " ( ";
		s += print_tree(root->left);
	}
	if (root->right) {
		s += " , ";
		s += print_tree(root->right);
		s += " ) ";
	}

	return s;
}

int main() {
	TreeNode *root = new TreeNode(9);
	root->left = new TreeNode(5);
	root->right = new TreeNode(12);

	root->left->left = new TreeNode(2);
	root->left->right = new TreeNode(7);

	root->right->left = new TreeNode(11);
	root->right->right = new TreeNode(13);

	cout << print_tree(root) << endl;

}