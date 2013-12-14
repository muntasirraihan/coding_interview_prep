#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    vector<vector<bool> > matched;
public:
    bool helper(vector<vector<char> > &board, string word, int wordIndex, int i, int j) {

        // cout << wordIndex << endl;
        // cout << i << " " << j << endl;
        // stepped out of board
        if (i >= board.size() || j >= board[0].size() || i < 0 || j < 0) {
            return false;
        }

        // cout << "dasdsa" << endl;
        // if matched this cell before
        if (matched[i][j]) {
            return false;
        }
        
        // cout << "wqerqw" << endl;
        // match a new character
        if (word[wordIndex] == board[i][j]) {
            wordIndex += 1;

            // match the entire word
            if (wordIndex >= word.size()) {
                return true;
            }
        } else {
            // did not match the current cell
            if (wordIndex > 0) {
                // in the middle of matching a word
                // breaks the matching
                return false;
            }
        }

        matched[i][j] = true;
        // cout << "3123" << endl;
        // cout << wordIndex << endl;

        // find next match
        bool result = false;
        result |= helper(board, word, wordIndex, i-1, j);

        if (result) {
            return true;
        }
        result |= helper(board, word, wordIndex, i+1, j);
        if (result) {
            return true;
        }
        result |= helper(board, word, wordIndex, i, j-1);
        if (result) {
            return true;
        }
        result |= helper(board, word, wordIndex, i, j+1);
        
        // remove marking
        matched[i][j] = false;

        return result;
        
    }

    bool exist(vector<vector<char> > &board, string word) {

        // initialize matched grid to false
        for (int i = 0; i < board.size(); i++) {
            vector<bool> row;
            for (int j = 0; j < board[0].size(); j++) {
                row.push_back(false);
            }
            matched.push_back(row);
        }

        // start dfs at every cell
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == word[0]) 
                    if (helper(board, word, 0, i, j)) {
                        return true;
                    }
            }
        }

        // no match at all
        return false;
    }
};

int main() {
    Solution s;
    vector<vector<char> > board;
    vector<char> firstRow;
    firstRow.push_back('a');
    firstRow.push_back('b');
    board.push_back(firstRow);

    vector<char> secondRow;
    secondRow.push_back('c');
    secondRow.push_back('d');
    board.push_back(secondRow);

    string word = "dbac";
    
    //s.exist(board, word);
    cout << "ans = " << s.exist(board, word) << endl;

    }