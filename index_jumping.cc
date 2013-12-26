// you can also use includes, for example:
// #include <algorithm>
int solution(const vector<int> &A) {
    // write your code in C++98
    
    if (A.size() == 0) return 0;
    
    vector<bool> seen(A.size(), false);
    seen[0] = true;    
    
    int K = 0;
    int M;
    
    while (true) {
        M = K + A[K];
        if (M >= A.size() || M < 0) {
            // detect out of bounds
            break;
        }
        seen[M] = true;
        if (A[K] == 0) {
            // detect endless loop
            break;    
        }
        K = M;
    }
    
    int result = 0;
    for (unsigned int i = 0; i < A.size(); ++i) {
        if (!seen[i]) {
            result += 1;    
        }
    }
    
    return result;
}
