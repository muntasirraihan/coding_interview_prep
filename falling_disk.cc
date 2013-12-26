// you can also use includes, for example:
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<int> &A, vector<int> &B) {
    // write your code in C++98
    int result = 0;
    int bottom = A.size();
    for (int i = 0; i < B.size(); ++i) {
        if (bottom == 0) break;
        int current = B[i];
        // cout << "current = " << current << endl;
        if (current > A[0]) break;
        int j = 0; bool set = false;
        for (j = 0; j < bottom; ++j) {
            if (current > A[j]) {
                result += 1;
                bottom = j-1;
                set = true;
                // cout << "bottom = " << bottom << endl;
                break;
            }
        }
        // cout << " j = " << j << endl;
        if (j == bottom && !set) {
            result += 1;
            bottom -= 1;
            // cout << "bottom = " << bottom << endl;
        }
    }
    return result;
}

int main() {
    int t[7] = {5, 6, 4, 3, 6, 2, 3};
    vector<int> A(t, t+7);
    int s[5] = {2, 3, 5, 2, 4};
    vector<int> B(s, s+5);

    cout << solution(A, B) << endl;
}