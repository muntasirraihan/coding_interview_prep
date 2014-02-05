/*
 Write a function called eval,
 which takes a string and returns a boolean.
 This string is allowed 6 different characters: 0, 1, &, |, (, and ).
 Eval should evaluate the string as a boolean expression,
 where 0 is false, 1 is true, & is an and, and | is an or.
 An example string might look like "(0 | (1 | 0)) & (1 & ((1 | 0) & 0))" 
*/
 
#include <cstdlib>
#include <iostream>

using namespace std;

#define F 0
#define T 1
#define AND 2
#define OR 3

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/* return the position of the matching closing parens */
int findMatchingParens(char s[], int start) {
	if (s[start] != '(') {
		return start;
	}
	int count = 1;
	while (count > 0) {
		start++;
		if (s[start] == '(')
			count++;
		else if (s[start] == ')')
			count--;
	}
	return start;
}

TreeNode *parseExpr(char s[], int start, int end) {
	/* left tree */
	int matchLeft = findMatchingParens(s, start);
	TreeNode *left;
	if (matchLeft == start) {
		// left is a number
		left = new TreeNode(atoi(&s[start]));
	} else {
		// left is an expr
		left = parseExpr(s, start + 1, matchLeft - 1);
	}

	/* finish parsing */
	if (matchLeft + 1 > end)
		return left;

	/* root node */
	TreeNode *root;
	if (s[matchLeft + 1] == '|')
		root = new TreeNode(OR);
	else
		root = new TreeNode(AND);

	/* right tree */
	int matchRight = findMatchingParens(s, matchLeft + 2);
	TreeNode *right;
	if (matchRight == matchLeft + 2) {
		// right is a number
		right = new TreeNode(atoi(&s[matchLeft + 2]));
	} else {
		// right is an expr
		right = parseExpr(s, matchLeft + 3, matchRight - 1);
	}

	root->left = left;
	root->right = right;

	return root;
}


bool eval(TreeNode *root) {
	if (root->val == AND)
		return (eval(root->left) && eval(root->right));
	else if (root->val == OR)
		return (eval(root->left) || eval(root->right));
	return root->val;
}

bool parseAndEval(char s[]) {
	int len = strlen(s);
	if (len == 0)
		return false;

	TreeNode *root = parseExpr(s, 0, len - 1);
	return eval(root);
}

int main() {
	char testStr[] = "((0|1)&1)&(1&(0|1))";
	cout << parseAndEval(testStr) << endl;

}