#include<unordered_map>
#include<utility>
#include<iostream>

using namespace std;

class EqualFn {
public:
    bool operator() (const pair<int, int> &t1, const pair<int, int> &t2) const {
        return (t1.first == t2.first) && (t1.second == t2.second);
    }
};

class HashFn {
public:
    size_t operator()(const pair<int, int> &t1) const {
        hash<int> h;
        return h(t1.first*t1.second);
    };
};

class Solution {
    int solution = 0;
    unordered_map<pair<int, int>, int, HashFn, EqualFn> results;
public:
    int uniquePaths(int m, int n) {

        cout << m << " " << n << endl;

        if (results.find(make_pair(m, n)) != results.end()) {
            return results[make_pair(m, n)];
        }

        if (m == 1 || n == 1) {
            results[make_pair(m, n)] = 1;
            return 1;
        }

        if (m > 1) {
            int result = uniquePaths(m - 1, n);
            results[make_pair(m - 1, n)] = result;
        }
        if (n > 1) {    
            int result = uniquePaths(m, n - 1);
            results[make_pair(m, n - 1)] = result;            
        }
        
        results[make_pair(m, n)] = results[make_pair(m - 1, n)] + results[make_pair(m, n - 1)];
        return results[make_pair(m, n)];
    }
};


int main() {
    Solution s;
    cout << s.uniquePaths(3, 3) << endl ;
}