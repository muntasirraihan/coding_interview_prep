#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
private:
    unordered_map<string, vector<string> > pred_map;
    unordered_set<string> lastHop;

    void find_lastHop(string end, unordered_set<string> &dict) {
        for (unordered_set<string>::iterator dictIter = dict.begin();
            dictIter != dict.end(); ++dictIter) {
            if (withinOneCharDiff(end, *dictIter)) {
                lastHop.insert(*dictIter);
            }
        }
    }

public:
    vector<vector<string> > all_solutions;

    inline bool withinOneCharDiff(string s, string t) {
        int numDiffs = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] != t[i]) {
                numDiffs += 1;
                if (numDiffs > 1) return false;
            }
        }
        if (numDiffs == 1) return true;
        return false;
    }

    vector<vector<string> > findLadders(string start, string end, 
                                        unordered_set<string> &dict) {
        queue<string> bfs_queue;
        bool found = false;
        bfs_queue.push(start);
        // map from dict word to predecessors
        unordered_map<string, int> visited;
        visited[start] = 0;
        find_lastHop(end, dict);
        
        // perform BFS to find shortest seq of transformations
        while (!bfs_queue.empty()) {
            string current = bfs_queue.front();
            bfs_queue.pop();

            // if found last hop
            unordered_set<string>::iterator lastHopIter = lastHop.find(current);
            if (lastHopIter != lastHop.end()) {
                found = true;
                // mark the preds for end word
                unordered_map<string, vector<string> >::iterator iter = pred_map.find(end);
                if (iter == pred_map.end()) {
                    // first time reach end
                    vector<string> preds;
                    preds.push_back(current);
                    pred_map.insert(pair<string, vector<string> >(end, preds));
                } else {
                    // latter time reach end
                    iter->second.push_back(current);
                }
            }

            // find next hop (BFS next layer)
            if (!found) {
                // mutate current to next
                string next(current);
                for (int pos = 0; pos < current.size(); ++pos) {
                    char currentChar = next[pos];
                    for (int l = 0; l < 26; ++l) {
                        next[pos] = 'a'+l;
                        
                        unordered_set<string>::iterator dictIter = dict.find(next);
                        if (dictIter != dict.end()) {
                            // if next exist in dict, expand into it
                            unordered_map<string, int>::iterator iter = visited.find(next);
                            if (iter == visited.end()) {
                                // if first time visiting
                                // mark visited
                                visited[next] = visited[current] + 1;
                                bfs_queue.push(next);
                                vector<string> preds;
                                preds.push_back(current);
                                pred_map.insert(pair<string, vector<string> >(next, preds));
                            } else if (visited[current] + 1 == visited[next]) {
                                // if visited but only from one layer above, allow setting predecessor
                                pred_map[next].push_back(current);
                            }
                        }

                        next[pos] = currentChar;
                    }
                }
            }

        }

        // find all sequences
        unordered_map<string, vector<string> >::iterator iter = pred_map.find(end);
        if (iter == pred_map.end()) {
            // no solution
            return all_solutions;
        }

        // DFS to find all solutions
        vector<string> path;
        path.push_back(end);

        find_all_solutions(start, end, path);

        return all_solutions;
    }

    void find_all_solutions(string start, string current, vector<string>& path) {
        
        if (current.compare(start) == 0) {
            all_solutions.push_back(path);
            return;
        }

        unordered_map<string, vector<string> >::iterator iter = pred_map.find(current);
        for (string pred : iter->second) {
            vector<string> new_path(path);
            new_path.insert(new_path.begin(), pred);
            find_all_solutions(start, pred, new_path);
        }
    }
};


int main() {
    Solution s;
    string start = "qa";
    string end = "sq"; 
    string words[] = {"si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye"};

    unordered_set<string> dict;
    for (string word : words) {
        dict.insert(word);
    }

    vector<vector<string> > solns;
    solns = s.findLadders(start, end, dict);
    cout << solns.size() << endl;
    for (vector<vector<string> >::iterator iter = solns.begin(); iter != solns.end(); ++iter) {
        for (vector<string>::iterator iiter = iter->begin(); iiter != iter->end(); ++iiter) {
            cout << *iiter << "->";
        }
        cout << endl;
    }
}