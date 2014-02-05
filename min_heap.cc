#include <iostream>

using namespace std;

/* binary min-heap */
class Heap {
	int *vals;
	int n;
	int true_size;

	void percolate_down(int i) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int smallest = i;
		if (left < n && vals[left] < vals[smallest]) smallest = left;
		if (right < n && vals[right] < vals[smallest]) smallest = right;
		
		if (smallest != i) {
			swap(vals[i], vals[smallest]);
			percolate_down(smallest);
		}

	}

	void percolate_up(int i) {
		int parent = (i - 1) / 2;
		while (parent >= 0 && vals[i] < vals[parent]) {
			swap(vals[parent], vals[i]);
			i = parent;
			parent = (i - 1) / 2;
		}
	}

	void double_size() {
		int *new_vals = new int[true_size << 1];
		for (int i = 0; i < true_size; ++i) {
			new_vals[i] = vals[i];
		}
		true_size = (true_size << 1);

		delete[] vals;
		vals = new_vals;
	}

public:
	Heap(int *A, int size) {
		true_size = 1;
		while (true_size < size) true_size = (true_size << 1);
		vals = new int[true_size];

		n = size;
		for (int i = 0; i < n; ++i) {
			vals[i] = A[i];
		}

		for (int i = n - 1; i >= 0; --i) {
			percolate_down(i);
		}

	}

	void insert(int x) {
		if (n + 1 > true_size) double_size();
		vals[n] = x;
		percolate_up(n);
		n++;
	}

	int remove_min() {
		swap(vals[0], vals[n - 1]);
		n--;
		percolate_down(0);
		return vals[n];
	}

	bool empty() {
		return (n == 0);
	}
};

int main() {
	int A[10] = {2, 3, 1, 6, 4, 5, 8, 9, 7, 0};
	Heap heap(A, 10);
	// heap.insert(-5);
	// heap.insert(-5);
	// heap.insert(-5);
	// heap.insert(-5);
	// heap.insert(-5);	
	// heap.insert(-5);
	// heap.insert(-5);
	// heap.insert(-5);
	// heap.insert(-5);
	while (!heap.empty()) {
		cout << heap.remove_min() << " ";
	}
	cout << endl;
	// for (int i : A) {
	// 	cout << i << " ";
	// }
	// cout << endl;
}