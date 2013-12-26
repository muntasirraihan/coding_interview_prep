#include <iostream>

using namespace std;

int solution(int N) {
    // write your code in C++98
    int result = 0;
    int count = 0;
    bool flag = false;
    while (N > 0) {
        int digit = N & 1;
        if (digit == 1) {
            flag = true;    
            result = max(result, count);
            count = 0;
        }
        
        if (flag && (digit == 0)) {
            count += 1;        
        }
        
        N = N >> 1;
    }
    
    return result;
}

int main() {
    int N = 15;
    cout << solution(N) << endl;
}