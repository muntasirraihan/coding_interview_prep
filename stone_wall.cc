// you can also use includes, for example:
// #include <algorithm>
#include <stack>

using namespace std;

int solution_on_small_data(const vector<int> &H)  {
    int result = 0;
    
    stack<int> s;
    for (unsigned int i = 0; i < H.size(); ++i) {
        int current = H[i];
        if (s.empty()) {
            result += 1;
            s.push(current);
        } else {
            if (current > s.top()) {
                result += 1;
                s.push(current);
            } else if (current < s.top()) {
                s.pop();
                while (!s.empty()) {
                    if (current > s.top()) {
                        result += 1;
                        s.push(current);      
                    } else if (current < s.top()) {
                        s.pop();
                    } else {
                        break;   
                    }
                }
                
                if (s.empty()) {
                    s.push(current);
                    result += 1;
                }
            }
        }
    }
    
    return result;
}

int solution_on_large_data(const vector<int> &H) {
    return solution_on_small_data(H);
    
}

int solution(const vector<int> &H) {
    // write your code in C++98
    if (H.size() <= 1000) {
        return solution_on_small_data(H);
    } else {
        return solution_on_large_data(H);   
    }   
}
