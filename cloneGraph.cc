#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>

using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
    unordered_set<UndirectedGraphNode *> visited;
    unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> nodes_mapping;
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (!node) return NULL;
        
        UndirectedGraphNode *clone_node = NULL;
        
        if (visited.find(node) == visited.end()) {

            // visit self
            visited.insert(node);
            clone_node = new UndirectedGraphNode(node->label);
            nodes_mapping[node] = clone_node;

            // DFS on neighbors
            for (int i = 0; i < node->neighbors.size(); ++i) {
                UndirectedGraphNode *nbrNode = node->neighbors[i];
                if (visited.find(nbrNode) == visited.end()) {
                    clone_node->neighbors.push_back(cloneGraph(nbrNode));
                } else {
                    clone_node->neighbors.push_back(nodes_mapping[nbrNode]);
                }
            }
        }

        return clone_node;
    }

    void printVector(vector<UndirectedGraphNode *> &v) {
        for (UndirectedGraphNode * n : v) {
            cout << n->label << " ";
        }
        cout << endl;
    }
};



int main() {
    Solution s;

    UndirectedGraphNode *n1 = new UndirectedGraphNode(1);
    UndirectedGraphNode *n2 = new UndirectedGraphNode(2);
    UndirectedGraphNode *n3 = new UndirectedGraphNode(3);
    UndirectedGraphNode *n4 = new UndirectedGraphNode(4);
    UndirectedGraphNode *n5 = new UndirectedGraphNode(5);


    n1->neighbors.push_back(n2);
    n1->neighbors.push_back(n3);
    n1->neighbors.push_back(n4);
    n1->neighbors.push_back(n5);

    n2->neighbors.push_back(n1);
    n2->neighbors.push_back(n3);

    n3->neighbors.push_back(n2);
    n3->neighbors.push_back(n1);
    n3->neighbors.push_back(n5);

    n4->neighbors.push_back(n1);

    n5->neighbors.push_back(n3);
    n5->neighbors.push_back(n1);


    UndirectedGraphNode *clone = s.cloneGraph(n1);
    s.printVector(clone->neighbors);
    
}