#include <cstdlib>
#include <iostream>

using namespace std;

int f(int a, int b) {
    int p = (a > 0) ? a : -a; 
    int q = (b > 0) ? b : -b; 

    if (p < q) {
        int t = p;
        p = q;
        q = t;
    }

    if (q == 0) return 0;

    for (int r = p % q; r != 0; r = p % q) {
        p = q; q = r;
    }

    return q;
}

int main() {
    cout << f(10, 5) << endl;
    cout << f(6, 9) << endl;
    cout << f(2, 3) << endl;
    cout << f(0, 1) << endl;
}
