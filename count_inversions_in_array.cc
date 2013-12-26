// you can also use includes, for example:
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void print_vector(vector<int> &A) {
    cout << "print vector ";
    for (int i = 0; i < A.size(); ++i) {
        cout << A[i] << " ";
    }
    cout << endl;

}
                        
int merge(vector<int> &A, int start, int mid, int end) {
    int result = 0;
    int i = start;
    int j = mid + 1;
    vector<int> v;
    
    while ((i <= mid) && (j <= end)) {
        if (A[i] <= A[j]) {
            v.push_back(A[i]);
            i += 1;
        } else {
            v.push_back(A[j]);
            // important!
            result += (mid - i + 1);
            j += 1;
        }
    }

    while (j <= end) {
        v.push_back(A[j]);
        j += 1;      
    }
    while (i <= mid) {
        v.push_back(A[i]);
        i += 1;
    }
    
    copy(v.begin(), v.end(), A.begin()+start);

    return result;
}

int helper(vector<int> &A, int start, int end) {

    if (end == start) return 0;

    int mid = (start+end) / 2;
    
    int first_result = helper(A, start, mid);
    int second_result = helper(A, mid+1, end);
    
    int merge_result = merge(A, start, mid, end);
    
    return (first_result + second_result + merge_result);
        
}

int solution(const vector<int> &A) {
    // write your code in C++98
    if (A.size() == 0) return 0;
    vector<int> B(A);
    int result = helper(B, 0, A.size()-1);
    return result;
}

int main() {
    int A[] = {-1, 6, 3, 4, 7, 4};
    vector<int> B(A, A+6);

    cout << solution(B) << endl;

}
