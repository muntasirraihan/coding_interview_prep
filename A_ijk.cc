/*
* Given an array of numbers find all such triplets that satisfy the given condition.
* Condition: a[i] < a[j] < a[k] where I < j < k.
*/

#include <vector>
#include <iostream>

using namespace std;

vector<vector<int> > all_triplets;

void backtrack(const vector<int> &seq, int pos, vector<int> current_indices, int max_element) {
	
	int current_size = current_indices.size();

	if (current_size == 3) {
		// done, add to global solution
		all_triplets.push_back(current_indices);
	} else if (current_size > 0) {
		// find the next larger element
		while (seq[pos] <= max_element && pos < seq.size()) pos++;

		// no more larger element
		if (pos == seq.size())
			return;		
	}

	// do not include this element
	vector<int> alternate_indices(current_indices);
	backtrack(seq, pos + 1, alternate_indices, max_element));

	// include this element
	current_indices.push_back(pos);
	backtrack(seq, pos + 1, current_indices, max(max_element, seq[pos]));

	return;
}	

