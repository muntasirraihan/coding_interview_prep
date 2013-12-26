#include<iostream>

using namespace std;

class Solution {
public:
    int maxSubArray(int A[], int n) {
        if (n == 0) return 0;
        int sum = A[0];
        int maxSum = A[0];
        for (int i = 1; i < n; ++i) {
            if (sum > 0) {
                if (A[i] > 0) {
                    sum += A[i];
                } else {
                    sum = (sum + A[i] >= 0) ? sum + A[i] : A[i];
                }
            } else {
                if (A[i] > 0) {
                    sum = A[i];
                } else {
                    sum = (sum > A[i]) ? sum : A[i];
                }
            }
            
            if (sum > maxSum) {
                maxSum = sum;
            }
        }
        return maxSum;
    }
};

int main() {
    Solution s;
    int A[2] = {-2, 1};
    cout << s.maxSubArray(A, 2) << endl;
}