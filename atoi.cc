#include <iostream>
#include <climits>
    
using namespace std;

class Solution {
public:
    int atoi(const char *str) {
        if (!str) return 0;
        
        int i = 0;
        // ignore whitespace
        while (i < strlen(str) && str[i] == ' ') i++;
    
        int sign = 1;
        // take + or -
        if (i < strlen(str) && str[i] == '+') {
            i++;
        } else if (i < strlen(str) && str[i] == '-') {
            i++;
            sign = -1;
        }
        
        int result = 0;
        while (i < strlen(str) && str[i] >= 48 && str[i] < 57) {
            if (sign == 1) {
                if (result > INT_MAX / 10 || (result == INT_MAX / 10 && (str[i] - 48) > 7)) {
                    return (INT_MAX);
                }
            } else {
                if (-result < INT_MIN / 10 || (-result == INT_MIN / 10 && (str[i] - 48) > 8)) {
                    return (INT_MIN);
                }
            }
            result = result * 10 + (str[i] - 48);
            i++;
        }
        return result * sign;
    }
};

int main() {
    Solution s;
    char str[] = "2147483648";
    cout << s.atoi(str) << endl;
}