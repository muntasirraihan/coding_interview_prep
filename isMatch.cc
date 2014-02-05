#include<string>
#include<sstream>
#include<vector>
#include<iostream>

using namespace std;

class Solution {
	bool isMatchHelper(string s, int si, string p, int pi, const vector<bool> &isStarred) {
		// reach regex end but not string end
		if (pi == p.size() && si < s.size()) return false;

		// reach string end
		if (si == s.size()) {
			// reach regex end
			if (pi == p.size()) return true;
			
			// the rest of regex is all starred
			while (pi < p.size() && isStarred[pi]) {
				pi++;
			}
			return (pi == p.size() || isStarred[pi]);
		} else {
			// not same element and pattern element != .
			if (s[si] != p[pi] && p[pi] != '.') {
				// can match zero pattern element if it's starred
				if (isStarred[pi]) {
					return isMatchHelper(s, si, p, pi + 1, isStarred);
				} else{
					return false;
				}
			}

			if (s[si] == p[pi] || p[pi] == '.') {
				// if can match zero or more
				if (isStarred[pi]) {
					// optimization
					if (pi + 1 < p.size() && p[pi] == p[pi + 1] && isStarred[pi + 1]) {
						return isMatchHelper(s, si + 1, p, pi + 1, isStarred);
					} else {
						// match zero or more
						return (isMatchHelper(s, si, p, pi + 1, isStarred) || isMatchHelper(s, si + 1, p, pi, isStarred));
					}
				} else {
					return isMatchHelper(s, si + 1, p, pi + 1, isStarred);
				}
			}
		}

		return false;
	}
public:
    bool isMatch(const char *s, const char *p) {
    	vector<bool> isStarred;
    	stringstream ss;
    	for (int i = 0; i < strlen(p); ++i) {
    		if (p[i] != '*') {
    			ss << p[i];
	    		if (i + 1 < strlen(p) && p[i + 1] == '*') {
	    			isStarred.push_back(true);
	    		} else {
	    			isStarred.push_back(false);
	    		}
	    	}
    	}
    	string s_str(s);
    	string p_str = ss.str();

	   	return isMatchHelper(s_str, 0, p_str, 0, isStarred);
    }
};

int main() {
	Solution sol;
	char s[] = "a";
	char p[] = ".*.*";
	cout << sol.isMatch(s, p) << endl;
}