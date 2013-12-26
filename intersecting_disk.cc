// you can also use includes, for example:
#include <algorithm>

struct interval {
    long low;
    long high;
    interval(long a, long b) : low(a), high(b) {}
};

bool compareUsingLow(interval i1, interval i2) {
    return (i1.low < i2.low);   
}

int solution(const vector<int> &A) {
    // write your code in C++98
    if (A.size() == 0) return 0;
    
    vector<interval> v;
    for (unsigned int i = 0; i < A.size(); ++i) {
        v.push_back(interval(i - A[i], i + A[i]));
    }
    
    sort(v.begin(), v.end(), compareUsingLow);
    
    int result = 0;
    for (unsigned int i = 0; i < A.size(); ++i) {
        interval current = v[i];
        long current_high = current.high;
        int count = 0;
        for (unsigned int j = i + 1; j < A.size(); ++j) {
            if (v[j].low <= current_high) {
                count += 1;    
            } else {
                break;    
            }
        }
        result += count;
    }
   
   if (result > 10000000) return -1;
    
   return result; 
}


