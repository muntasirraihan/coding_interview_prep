#include <vector>

using namespace std;

void find_all_partitions_of_int_helper(int n, int current_sum, vector<int> &current_partition, vector<vector<int> > &solution) {
	// ensure all legal candidates are nondecreasing
	if (current_sum == n) {
		solution.push_back(current_partition);
		return;
	}
	for (int candidate = 1; candidate <= n - current_sum; ++candidate) {
		vector<int> next_partition(current_partition);
		int current_sum_copy = current_sum;
		if (next_partition.empty()) {
			next_partition.push_back(candidate);
			current_sum_copy = candidate;
		} else if (candidate >= current_partition.back()) {
			next_partition.push_back(candidate);
			current_sum_copy += candidate;
		} else {
			continue;
		}
		
		find_all_partitions_of_int_helper(n, current_sum_copy, next_partition, solution);
	}
}

vector<vector<int> > find_all_partitions_of_int(int n) {
	vector<vector<int> > solution;
	if (n == 0)
		return solution;
	vector<int> current_partition;
	find_all_partitions_of_int_helper(n, 0, current_partition, solution);

	return solution;
}

int main() {
	vector<vector<int> > solution = find_all_partitions_of_int(4);
	for (vector<int> v : solution) {
		for (int x : v) {
			printf("%d ", x);
		}
		printf("\n");
	}
}