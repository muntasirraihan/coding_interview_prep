#include<cstring>
#include<vector>

#include<iostream>
using namespace std;

vector<int> solution(int N, vector<int> &A) {
    // write your code in C++98
    int counters[N];
    for (unsigned int j = 0; j < N; ++j) counters[j] = 0;
    int max = 0;
    int last_maxCount_op = 0;
    for (unsigned int i = 0; i < A.size(); ++i) {
        int op = A[i];
        if (op < N + 1) {
            counters[op-1] += 1;    
            if (counters[op-1] > max) {
                max = counters[op-1];
            }
        } else {
            if (last_maxCount_op != i-1) {
                for (unsigned int j = 0; j < N; ++j) counters[j] = max;
            }
            last_maxCount_op = i;
        }
    }
    
    return vector<int>(counters, counters+N);
}   

int main() {
    int in[] = {3, 4, 4, 6, 1, 4, 4};
    vector<int> input(in, in+7);
    vector<int> result = solution(5, input);
    for (int x : result) {
        cout << x << " ";
    }
}