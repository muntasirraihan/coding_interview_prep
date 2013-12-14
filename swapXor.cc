#include<cstdlib>
#include<iostream>

using namespace std;

int main() {

    int a = 12;
    int b = 41;

    cout << "a= " << a << endl;
    cout << "b= " << b << endl;

    (a ^= (b ^= (a ^= b)));

    cout << "a= " << a << endl;
    cout << "b= " << b << endl;

}
