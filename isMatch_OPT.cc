#include<cstring>
#include<vector>

using namespace std;

class Solution {
public:
    bool isMatch(const char *s, const char *p) {
        int sl = strlen(s);
        int pl = strlen(p);

        // mark all pattern elements followed by a star
        vector<bool> starred(pl, false);
        for (int j = 0; j < pl - 1; ++j) {
            if (p[j + 1] == '*') starred[j] = true;
        }

        vector<vector<bool> > match(sl + 1, vector<bool>(pl + 1, false));
        match[0][0] = true;

        for (int j = 1; j <= pl; ++j) {
            if (match[0][j - 1] && starred[j]) {
                match[0][j] = true;
                ++j;
            } else {
                break;
            }
        }


        for (int j = 0; j < pl; ++j) {
            for (int i = 0; i < sl; ++i) {

            }
        }

    }
};