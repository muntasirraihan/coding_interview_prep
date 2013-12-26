#include <cstdlib>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int removeDuplicates(int A[], int n) {
        if (n <= 1) return n;
        
        int numDuplicates = 0;
        unordered_set<int> seen;
        unordered_set<int>::iterator iter;
        seen.insert(A[0]);
        int p = 1;
        int q = 1;
        while (p < n) {
            iter = seen.find(A[p]);
            if (iter == seen.end()) {
                A[q] = A[p];
                q += 1;
            } else {
                numDuplicates += 1;
            }
            p += 1;
        }
        
        return n - numDuplicates;
    }
};


int main() {
    Solution s;
    int A[3] = {1, 1, 2};
    cout << "yui " << s.removeDuplicates(A, 3) << endl;

    for (int x : A) {
        cout << x << " " << endl;
    }
}
