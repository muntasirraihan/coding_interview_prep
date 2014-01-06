#include<iostream>
#include<unordered_set>
#include<vector>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        if (matrix.empty()) return;
        
        int m = matrix.size();
        int n = matrix[0].size();
        unordered_set<int> columns_deleted;

        // find all cols to be deleted
        // reset all rows necessary
        for (int i = 0; i < m; ++i) {
            bool row_reset = false;
            for (int j = 0; j < n; ++j) {
   
                if (matrix[i][j] == 0) {

                    // record the column to delete
                    columns_deleted.insert(j);
                    
                    // reset this row
                    row_reset = true;
   
                } 
            }

            // delete all zeros in this row
            if (row_reset) {
            	for (int j = 0; j < n; ++j) {
            	    matrix[i][j] = 0;
            	}
            }
            
            // if all columns deleted, then we are done
            if (columns_deleted.size() == n) break;
        }

        // reset all columns
        for (unordered_set<int>::iterator it = columns_deleted.begin(); it != columns_deleted.end(); ++it) {
        	int col = *it;
            // delete matrix elements in this column
            for (int k = 0; k < m; ++k) {
            	matrix[k][col] = 0;
            }
        }
    }
};

int main(int argc, char const *argv[])
{

	Solution s;
	vector<vector<int> > matrix;

	int r1[] = {0,0,0,5};
	vector<int> v1(r1, r1 + 4);
	matrix.push_back(v1);

	int r2[] = {4,3,1,4};
	vector<int> v2(r2, r2 + 4);
	matrix.push_back(v2);

	int r3[] = {0,1,1,4};
	vector<int> v3(r3, r3 + 4);
	matrix.push_back(v3);

	int r4[] = {1,2,1,3};
	vector<int> v4(r4, r4 + 4);
	matrix.push_back(v4);

	int r5[] = {0,0,1,1};
	vector<int> v5(r5, r5 + 4);
	matrix.push_back(v5);

	s.setZeroes(matrix);

	for (vector<int> r : matrix) {
		for (int c : r) {
			cout << c << " ";
		}
		cout << endl;
	}
	return 0;
}