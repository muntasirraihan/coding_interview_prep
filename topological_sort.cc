// BFS on a graph

#include<iostream>
#include<vector>
#include<unordered_set>
#include<queue>
#include<unordered_map>

using namespace std;

struct graphNode {
	int label;
	vector<graphNode *> neighbors;
	graphNode(int x) : label(x) {};
};


unordered_map<graphNode*, graphNode*> parents;

void topological_sort(graphNode *root, unordered_map<graphNode *, int> indegrees, int graph_size) {
	if (!root) return;

	vector<graphNode*> sorted;

	queue<graphNode *> zero_indegree_nodes;
	zero_indegree_nodes.push(root);

	while (!zero_indegree_nodes.empty()) {
		graphNode *current = zero_indegree_nodes.front();
		zero_indegree_nodes.pop();

		sorted.push_back(current);
		printf("next item = %d\n", current->label);

		for (graphNode *n : current->neighbors){
			indegrees[n]--;
			// printf("nbr of %d is %d with indegree = %d\n", current->label, n->label, indegrees[n]);
			if (indegrees[n] == 0) {
				zero_indegree_nodes.push(n);
			}			
		}
	}

	if (sorted.size() < graph_size) {
		printf("topological sort failed, since graph is not DAG\n");
	}
}


int main() {
	graphNode *v1 = new graphNode(1);
	graphNode *v2 = new graphNode(2);
	graphNode *v3 = new graphNode(3);
	graphNode *v4 = new graphNode(4);
	graphNode *v5 = new graphNode(5);
	graphNode *v6 = new graphNode(6);
	graphNode *v7 = new graphNode(7);
	graphNode *v8 = new graphNode(8);

	v1->neighbors.push_back(v2);
	v1->neighbors.push_back(v3);
	v1->neighbors.push_back(v4);

	// v2->neighbors.push_back(v1);
	v2->neighbors.push_back(v3);
	// v2->neighbors.push_back(v4);

	// v3->neighbors.push_back(v1);
	// v3->neighbors.push_back(v2);
	v3->neighbors.push_back(v4);

	// v4->neighbors.push_back(v1);
	// v4->neighbors.push_back(v2);
	// v4->neighbors.push_back(v3);

	unordered_map<graphNode *, int> indegrees;
	indegrees[v1] = 0;
	indegrees[v2] = 1;
	indegrees[v3] = 2;
	indegrees[v4] = 2;
	
	printf("\n-----perform topological sort-----\n");
	topological_sort(v1, indegrees, 4);
}