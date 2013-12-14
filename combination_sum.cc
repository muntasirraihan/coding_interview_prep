#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution {
public:
    void helper(vector<int> &candidates, vector<vector<int> > &allSolutions, vector<int> &currentSet, 
                    int currentIndex, int currentSum, int target, bool repeated) {
        // run out of candidates
        if (currentIndex >= candidates.size()) {
            return;
        }

        // skip current number
        if (!repeated) {
            vector<int> newSet1(currentSet);
            helper(candidates, allSolutions, newSet1, currentIndex+1, currentSum, target, false);
        }

        // add a new number to currentSet
        currentSet.push_back(candidates[currentIndex]);
        int newSum = currentSum + candidates[currentIndex];
        if (newSum == target) {
            // found a new solution
            allSolutions.push_back(currentSet);
            return;
        } else if (newSum > target) {
            // run over target
            return;
        } else {
            // add repeated number
            vector<int> newSet2(currentSet);
            helper(candidates, allSolutions, newSet2, currentIndex, newSum, target, true);
            // add next number
            vector<int> newSet3(currentSet);
            helper(candidates, allSolutions, newSet3, currentIndex+1, newSum, target, false);
        }
        return;

    }
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        vector<vector<int> > allSolutions;
        vector<int> currentSet;
        sort(candidates.begin(), candidates.end());
        helper(candidates, allSolutions, currentSet, 0, 0, target, false);
        
        return allSolutions;
    }
};

int main() {
    Solution s;
    vector<int> candidates;
    candidates.push_back(1);
    candidates.push_back(2);
    vector<vector<int> > allSolutions = s.combinationSum(candidates, 2);

    // print solutions
    for (int i = 0; i < allSolutions.size(); i++) {
        vector<int> aSolution = allSolutions[i];
        cout << "another solution" << endl;
        for (int j = 0; j < aSolution.size(); j++) {
            cout << aSolution[j] << "+";
        }
        cout << endl;
    }
}