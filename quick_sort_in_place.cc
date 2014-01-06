class Solution {
public:
    void quickSort(int A[], int n) {
        if (n <= 1) return;
    
        int left[n];
        int right[n];
        int left_index = 0;
        int right_index = 0;
        
        int pivot = A[0];
        for (int i = 1; i < n; ++i) {
            if (A[i] <= pivot) {
                left[left_index++] = A[i];
            } else {
                right[right_index++] = A[i];
            }
        }
        
        quickSort(left, left_index);
        quickSort(right, right_index);
        
        for (int i = 0; i < left_index; ++i) {
            A[i] = left[i];
        }
        
        A[left_index] = pivot;
        
        for (int i = 0; i < right_index; ++i) {
            A[left_index + 1 + i] = right[i];
        }
        
    }
    void sortColors(int A[], int n) {
        quickSort(A, n);
    }
};