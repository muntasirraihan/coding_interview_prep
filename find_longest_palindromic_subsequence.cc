#include <cstdio>
#include <string>
#include <vector>

using namespace std;

#define NO_OP 4

void backtrace(int i, int j, vector<vector<int> > &choices, vector<int> &lower, vector<int> &upper) {
	if (i == j) {
		lower.push_back(i);
		return;
	}

	switch (choices[i][j]) {
	case 0:
		backtrace(i, j - 1, choices, lower, upper); break;
	case 1:
		lower.push_back(i);
		upper.insert(upper.begin(), j);
		backtrace(i + 1, j - 1, choices, lower, upper); break;
	case 2:
		backtrace(i + 1, j, choices, lower, upper); break;
	}

	return;
}

string find_longest_palindromic_subsequence(string s) {
	int size = s.size();
	if (size == 0)
		return 0;
	
	// initialze OPT with zeros
	vector<vector<int> > OPT(size, vector<int>(size, 0));
	// initialze all leading diagonals
	for (int i = 0; i < size; ++i) {
		OPT[i][i] = 1;
	}

	// record choices
	// 0 => L(i, j) = L(i , j - 1)
	// 1 => L(i, j) = L(i + 1, j - 1) + 2
	// 2 => L(i, j) = L(i + 1, j)
	vector<vector<int> > choices(size, vector<int>(size, NO_OP));

	// compute DP
	for (int offset = 1; offset < size; ++offset) {
		for (int row = 0; row < size - offset; ++row) {
			if (s[row] == s[row + offset]) {
				OPT[row][row + offset] = OPT[row + 1][row + offset - 1] + 2;
				choices[row][row + offset] = 1;
			} else {
				if (OPT[row][row + offset - 1] >= OPT[row + 1][row + offset]) {
					OPT[row][row + offset] = OPT[row][row + offset - 1];
					choices[row][row + offset] = 0;
				} else {
					OPT[row][row + offset] = OPT[row + 1][row + offset];
					choices[row][row + offset] = 2;
				}
			}
		}
	}

	// // print
	// printf("\n---------------\n");
	// for (int i = 0; i < size; ++i) {
	// 	for (int j = 0; j < size; ++j) {
	// 		printf(" %d ", OPT[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n---------------\n");

	// // print
	// printf("\n---------------\n");
	// for (int i = 0; i < size; ++i) {
	// 	for (int j = 0; j < size; ++j) {
	// 		printf(" %d ", choices[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n---------------\n");

	// back trace to find the longest palindromic subsequence
	vector<int> lower;
	vector<int> upper;
	backtrace(0, size - 1, choices, lower, upper);
	string subseq = "";
	for (int i : lower) {
		subseq += s[i];
	}
	for (int i : upper) {
		subseq += s[i];
	}
	return subseq;
}

int main() {
	// string s = "abcbabcbabcba";
	string s = "ABCBAHELLOHOWRACECARAREYOUIAMAIDOINGGOOD";
	// string s = "babab";
	// string s = "GEEKSFORGEEKS";
	int subseq_len;
	printf("original string = %s\n", s.c_str());

	string subseq = find_longest_palindromic_subsequence(s);
	printf("find_longest_palindromic_subsequence = %s\n", subseq.c_str());
	printf("length = %lu\n", subseq.size());
}
