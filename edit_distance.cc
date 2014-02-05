#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        if (m == 0 || n == 0) return max(m, n);
        
        // initialize OPT matrix
        vector<vector<int> > OPT(m + 1, vector<int>(n + 1, -1));
        for (int j = 0; j <= n; ++j) OPT[0][j] = j;
        for (int i = 0; i <= m; ++i) OPT[i][0] = i;
        
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    OPT[i][j] = OPT[i - 1][j - 1];
                } else {
                    OPT[i][j] = min(min(OPT[i - 1][j] + 1, OPT[i][j - 1] + 1), OPT[i - 1][j - 1] + 1);
                }
            }
        }
        
        return OPT[m][n];
    }
};

int main() {
    Solution s;
    cout << s.minDistance("kitten", "sitting") << endl;
}