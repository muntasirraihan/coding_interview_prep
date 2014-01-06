#include <stdint.h>
#include <vector>
#include <iostream>

using namespace std;

static inline uint32_t log2(const uint32_t x) {
// integer log-2
  uint32_t y;
  asm ( "\tbsr %1, %0\n"
      : "=r"(y)
      : "r" (x)
  );
  return y;
}

class Solution {
    vector<vector<int> > solution;
    vector<int> nums;
public:

    void permuteHelper(uint32_t candidates, vector<int> current) {
        if (candidates == 0) {
            solution.push_back(current);
            return;
        }

        uint32_t prev_chocies = 0;       
        while (candidates > 0) {
            // first zero out last 1
            // xor to get the only digit that changed e.g. 00001000 = index 3
            int next_candidates = candidates & (candidates - 1);
            uint32_t next_choice = (next_candidates ^ candidates);
            int next_candidate_index = log2(next_choice);

            vector<int> newCurrent(current);
            newCurrent.push_back(nums[next_candidate_index]);
        
            permuteHelper(next_candidates + prev_chocies, newCurrent);
            
            candidates = next_candidates;
            prev_chocies += next_choice;
        }
        
    }
    vector<vector<int> > permute(vector<int> &num) {
        nums = num;
        int N = num.size();
    
        uint32_t candidates = (1 << N) - 1;
        vector<int> current;
        permuteHelper(candidates, current);
        
        return solution;
    }
};

int main() {
    Solution s;
    int nums[3] = {1, 2, 3};
    vector<int> v(nums, nums+3);
    vector<vector<int> > solutions = s.permute(v);
    for (vector<int> vi : solutions) {
        for (int x : vi) {
            cout << x << " ";
        }
        cout << endl;
    }
}