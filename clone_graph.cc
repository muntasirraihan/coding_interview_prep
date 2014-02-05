/**
 * Definition for undirected graph.
 * struct UndirectedGraphNode {
 *     int label;
 *     vector<UndirectedGraphNode *> neighbors;
 *     UndirectedGraphNode(int x) : label(x) {};
 * };
 */
class Solution {
    unordered_set<UndirectedGraphNode *> visited;
    unordered_map<UndirectedGraphNode *, UndirectedGraphNode *> nodes_mapping;
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
    	if (!node) return NULL;

    	if (visited.find(node) == visited.end()) {
    		// not visited before
    		visited.insert(node);
    		UndirectedGraphNode *cloneNode = new UndirectedGraphNode(node->label);
    		nodes_mapping[node] = cloneNode;

    		// perform DFS on node
    		for (int i = 0; i < node->neighbors.size(); ++i) {
    			UndirectedGraphNode *nbrNode = node->neighbors[i];
		    	cloneNode->neighbors.push_back(cloneGraph(nbrNode));
    		}
    		return cloneNode;
    	}
    	return nodes_mapping[node];
    }
};