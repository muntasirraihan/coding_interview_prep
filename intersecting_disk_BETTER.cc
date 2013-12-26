#include <algorithm>

int solution(const vector<int> &A) {
    // write your code in C++98
    unsigned int A_size = A.size();
    if (A_size == 0) return 0;
    
    vector<long> v_low;
    vector<long> v_high;
    
    for (unsigned int i = 0; i < A_size; ++i) {
        v_low.push_back(i - (long)A[i]);
        v_high.push_back(i + (long)A[i]);
    }
    
    sort(v_low.begin(), v_low.end());
    sort(v_high.begin(), v_high.end());
    
    int result = 0;
    
    int i_low = 0;
    int i_high = 0;
    int overlap_count = 0;
    
    // always finish v_low first
    while (i_low < A_size) {
        if (v_low[i_low] <= v_high[i_high]) {
            // see a low first
            result += overlap_count;
            overlap_count += 1;           
            i_low += 1;
        } else {
            // see a high first
            overlap_count -= 1;
            i_high += 1;
        }
    }
    
   if (result > 10000000) return -1;
    
   return result; 
}