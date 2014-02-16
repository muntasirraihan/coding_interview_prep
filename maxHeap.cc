#include<iostream>

using namespace std;

class maxHeap {
public:
	int size;
	int max_size;
	int *vals;

	maxHeap() {
		max_size = 2;
		vals = new int[max_size];
		size = 0;
	}

	maxHeap(int *A, int n) {
		// make heap
		size = n;
		max_size = find_next_2_power(size);
		vals = new int[size];
		for (int i = 0; i < size; ++i)
			vals[i] = A[i];

		// heapify down from bottom up to build heap property
		for (int i = size / 2 - 1; i >= 0; --i) {
			heapify_down(i);
		}
	}

	void insert(int x) {
		// double array and copy values
		if (size + 1 > max_size) {
			int *new_vals = new int[max_size << 1];
			for (int i = 0; i < max_size; ++i)
				new_vals[i] = vals[i];
			max_size = max_size << 1;
			delete[] vals;
			vals = new_vals; 
		}

		// insert to leaf node
		vals[size] = x;
		// then heapify up
		heapify_up(size);
		size++;
	}

	int pop() {
		// swap root of tree with last leaf node
		swap(vals, 0, size - 1);

		// return result
		int result = vals[size - 1];
		size--;
		
		// heapify down root
		heapify_down(0);

		// shrink array by half
		if (size < max_size / 2) {
			int *new_vals = new int[max_size >> 1];
			for (int i = 0; i < size; ++i)
				new_vals[i] = vals[i];
			max_size = max_size >> 1;
			delete[] vals;
			vals = new_vals;
		}
		return result;
	}

	int get_size() {
		return size;
	}

	~maxHeap(){
		delete[] vals;
	}

	void heapify_up(int i) {
		if (i > 0 && vals[parent(i)] < vals[i]) {
			swap(vals, parent(i), i);
			heapify_up(parent(i));
		}
		return;
	}

	void heapify_down(int i) {
		if (i >= size) return;

		int larger_child = (vals[left_child(i)] > vals[right_child(i)]) ? left_child(i) : right_child(i);

		if (vals[i] < vals[larger_child]) {
			swap(vals, i, larger_child);
			heapify_down(larger_child);
		}
		return;

	}

/* Helper methods */
	int find_next_2_power(int x) {
		int b = 1;
		while (b < x) b <<= 1;
		return b;
	}

	void swap(int A[], int i, int j) {
		int t = vals[i];
		vals[i] = vals[j];
		vals[j] = t;
	}

	int parent(int i) {
		if (i > 0)
			return (i - 1) / 2;
		else
			return 0;
	}

	int left_child(int i) {
		int t = 2 * i + 1;
		if (t >= size)
			return i;
		return t;
	}

	int right_child(int i) {
		int t = 2 * i + 2;
		if (t >= size)
			return i;
		return t;
	}

};



int main() {
	int A[] = {2, 7, 17, 3, 19, 100, 36, 25, 1};

	maxHeap h = maxHeap();
	for (int i = 0; i < 9; ++i) {
		h.insert(A[i]);
	}

	for (int i = 0; i < 9; ++i) {
		cout << h.vals[i] << " ";
	}
	cout << endl;

	while (h.get_size() > 0) {
		cout << h.pop() << " ";
	}
	cout << endl;

	maxHeap maxH = maxHeap(A, 9);
	for (int i = 0; i < 9; ++i) {
		cout << maxH.vals[i] << " ";
	}
	cout << endl;

	while (maxH.get_size() > 0) {
		cout << maxH.pop() << " ";
	}
	cout << endl;
}

	// for (int i = 0; i < size; ++i) {
	// 	cout << vals[i] << " ";
	// }
	// cout << endl;