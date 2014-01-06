#include <climits>
#include <iostream>
#include <cstdlib>

using namespace std;
class Solution {
public:
    double findKthElementSortedArray(int A[], int m, int B[], int n, int k) {
        if (m == 0) return B[k-1];
        if (n == 0) return A[k-1];
        

        int i = (int)((double)m / (m+n) * (k-1));
        int j = (k-1) - i;
        
        double A_i_1 = ((i == 0) ? INT_MIN : A[i-1]); 
        double B_j_1 = ((j == 0) ? INT_MIN : B[j-1]);
        double A_i = ((i == m) ? INT_MAX : A[i]);
        double B_j = ((j == n) ? INT_MAX : B[j]);


        if (B_j_1 <= A_i && A_i <= B_j) {
            return A_i;
        } else if (A_i_1 <= B_j && B_j <= A_i) {
            return B_j;
        }
        
        if (A_i < B_j) {
            return findKthElementSortedArray(A+i+1, m-i-1, B, j, k-i-1);
        } else {
            return findKthElementSortedArray(A, i, B+j+1, n-j-1, k-j-1);
        }

        
    }
    
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        if ((m + n) % 2 == 1) return findKthElementSortedArray(A, m, B, n, (m + n) / 2 + 1);
        
        double a = findKthElementSortedArray(A, m, B, n, (m + n) / 2);
        double b = findKthElementSortedArray(A, m, B, n, (m + n) / 2 + 1);
        return (a + b) / 2;
    }
};

int main() {
    int A[] = {2, 3, 4, 5, 6, 7};
    int m = 6;
    int B[] = {1};
    int n = 1;

    Solution s;
    cout << s.findKthElementSortedArray(A, m, B, n, 3) << endl;

}