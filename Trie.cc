#include <iostream>

using namespace std;

struct TrieNode {
	int words;		// num of words
	int prefixes;	// num of prefixes
	TrieNode **edges;	// array of TrieNode pointers
};


void initializeTrieNode(TrieNode *tn) {
	tn->words = 0;
	tn->prefixes = 0;
	tn->edges = new TrieNode*[26];
	for (int i = 0; i < 26; ++i)
		tn->edges[i] = NULL;
}


void addWord(TrieNode *tn, char *word) {
	if (*word == '\0') {
		tn->words++;
		return;
	}
	int c = *word - 'a';
	
	if (!tn->edges[c]) {
		tn->edges[c] = new TrieNode();
		initializeTrieNode(tn->edges[c]);
	}

	tn->prefixes++;
	
	word++;
	addWord(tn->edges[c], word);

}

int countWord(TrieNode *tn, char *word) {
	if (*word == '\0') return tn->words;

	int c = *word - 'a';

	if (!tn->edges[c]) {
		return 0;
	}

	word++;
	return countWord(tn->edges[c], word);

}

int countPrefix(TrieNode *tn, char *prefix) {
	if (*prefix == '\0') return tn->prefixes;

	int c = prefix[0] - 'a';
	if (!tn->edges[c]) {
		return 0;
	}

	prefix++;
	return countPrefix(tn->edges[c], prefix);
	
}


int main() {
	TrieNode *root = new TrieNode();
	initializeTrieNode(root);

	char s[] = "a";
	addWord(root, s);
	addWord(root, s);
	char t[] = "aab";
	char q[] = "abb";
	addWord(root, t);
	addWord(root, t);
	addWord(root, q);

	char tmp[] = "ab";
	cout << countPrefix(root, tmp) << endl;
	cout << countWord(root, q) << endl;
}


