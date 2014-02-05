#include <iostream>

using namespace std;

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void bubbleSort(int *A, int n) {
	for (int i = n - 1; i > 0; --i) {
		for (int j = 1; j <= i; ++j) {
			if (A[j - 1] > A[j]) swap(A[j], A[j - 1]);
		}
	}
}

void selectionSort(int *A, int n) {
	for (int i = 0; i < n; ++i) {
		int index = i;
		for (int j = i + 1; j < n; ++j) {
			if (A[j] < A[index]) index = j;
		}
		swap(A[i], A[index]);
	}
}

void insertionSort(int *A, int n) {
	for (int i = 1; i < n; ++i) {
		for (int j = i; j > 0; --j) {
			if (A[j - 1] > A[j]) {
				swap(A[j - 1], A[j]);
			} else {
				break;
			}
		}
	}
}

/* heapsort */

void percolate_down(int *A, int n, int i) {
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;
	if (left < n && A[left] > A[largest]) largest = left;
	if (right < n && A[right] > A[largest]) largest = right;

	if (largest != i) {
		swap(A[i], A[largest]);
		percolate_down(A, n, largest);
	}
}

void make_max_heap(int *A, int n) {
	for (int i = n - 1; i >= 0; --i) {
		percolate_down(A, n, i);
	}
}

void heapSort(int *A, int n) {
	make_max_heap(A, n);
	for (int i = n - 1; i >= 0; --i) {
		swap(A[0], A[i]);
		percolate_down(A, i, 0);
	}
}

int main() {
	int A[10] = {2, 3, 1, 6, 4, 5, 8, 9, 7, 0};
	heapSort(A, 10);
	for (int i : A) {
		cout << i << " ";
	}
	cout << endl;
}