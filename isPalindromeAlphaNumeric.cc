/*    
    48-57
    
    65-90 A
    
    97-122
*/

#include <string>

#include <iostream>

using namespace std;

class Solution {
    
    bool isAlphaNumeric(char c) {
        return ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122));
    }
    
    char reduceToLowerCase(char c) {
        if (c >= 65 && c <= 90) {
            return (97 + c - 65);
        }
        return c;
    }
    
public:
    bool isPalindrome(string s) {
        if (s.empty()) return true;
        int left = 0;
        int right = s.size() - 1;
        
        while (left != right && left <= right) {
        	cout << left << " " << right << endl;
            while ((left < right) && !isAlphaNumeric(s[left])) left++;
            while ((left < right) && !isAlphaNumeric(s[right])) right--;
            cout << left << " " << right << endl;
            if (left == right) break;
            if (reduceToLowerCase(s[left]) != reduceToLowerCase(s[right])) return false;
            left++;
            right--;
        }
        
        return true;
        
    }
};

int main() {
	Solution soln;
	string s = "a ba";
	cout << soln.isPalindrome(s) << endl;
}