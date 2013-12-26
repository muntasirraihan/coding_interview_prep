#include <iostream>
#include <vector>

using namespace std;

void print_vector(vector<int> &A) {
    cout << "print vector ";
    for (int i = 0; i < A.size(); ++i) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int f(int a, int b) {
	return (a < b) ? a : b;
}

vector<int> construct_segtree(const vector<int> &A, int start, int end) {
	vector<int> segtree;
	int size = end - start + 1;
	if (size == 1) {
		segtree.push_back(0);
		segtree.push_back(A[start]);
		return segtree;
	}

	int mid = (start + end) / 2;
	vector<int> ltree = construct_segtree(A, start, mid);
	vector<int> rtree = construct_segtree(A, mid + 1, end);

	// merge
	segtree.push_back(0);
	segtree.push_back(f(ltree[1], rtree[1]));
	for (int i = 1; i < ltree.size(); ++i) {
		segtree.push_back(ltree[i]);
	}
	for (int i = 1; i < rtree.size(); ++i) {
		segtree.push_back(rtree[i]);
	}

	return segtree;
}

int minimum_range_query(vector<int> segtree, int qs, int qe) {
	if (start == end) return segtree[root_idx];
	return 1;
}

int main() {
	int A[] = {1, 3, 5, 7, 9, 11};
	vector<int> B(A, A+6);
	vector<int> segtree = construct_segtree(B, 0, B.size()-1);

	print_vector(segtree);	
}