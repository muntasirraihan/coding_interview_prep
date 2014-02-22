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

void bfs(graphNode *root) {
	if (!root) return;

	unordered_set<graphNode*> discovered;
	unordered_set<graphNode*> explored;

	// unordered_map<graphNode*, graphNode*> parents;

	queue<graphNode *> q;
	q.push(root);
	discovered.insert(root);

	while (!q.empty()) {
		graphNode *current = q.front(); q.pop();
		explored.insert(current);

		for (graphNode *n : current->neighbors){
			
			if (discovered.find(n) == discovered.end()) {
				printf("found %d\n", n->label);
				discovered.insert(n);
				parents[n] = current;
				q.push(n);

			}

			if (explored.find(n) == explored.end()) {
				printf("%d -> %d\n", current->label, n->label);
			}

		}	
	}
}

void trace_path(graphNode *s, graphNode *t) {
	if (s == t) {
		printf("start at %d ", s->label);
		return;
	}
	trace_path(s, parents[t]);
	printf("-> %d", t->label);
}

bool isBipartite(graphNode *root) {
	if (!root) return true;

	unordered_set<graphNode*> discovered;
	unordered_set<graphNode*> explored;

	// unordered_map<graphNode*, graphNode*> parents;
	int r = 0;
	int b = 1;
	unordered_map<graphNode*, int> coloring;

	queue<graphNode *> q;
	q.push(root);
	discovered.insert(root);
	
	//
	coloring[root] = r;
	printf("color %d with %d\n", root->label, r);

	while (!q.empty()) {
		graphNode *current = q.front(); q.pop();
		explored.insert(current);

		//
		int currentColor = coloring[current];
		int oppositeColor = (currentColor + 1) % 2;

		for (graphNode *n : current->neighbors){
			
			if (discovered.find(n) == discovered.end()) {
				printf("color %d with %d\n", n->label, oppositeColor);
				discovered.insert(n);
				parents[n] = current;
				q.push(n);
				//
				coloring[n] = oppositeColor;
			}

			if (explored.find(n) == explored.end()) {
				printf("%d -> %d\n", current->label, n->label);
				if (coloring[n] != oppositeColor) {
					printf("try to color %d with color %d\n", n->label, oppositeColor);
					printf("find inconsistent coloring at %d\n", n->label);
					return false;
				}
			}

		}	
	}
	return true;
}


void dfs(graphNode *current, unordered_set<graphNode*> &discovered, 
		unordered_set<graphNode*> &explored, unordered_map<graphNode*, graphNode*> &parents) {
	if (!current) return;

	discovered.insert(current);
	printf("found %d\n", current->label);

	for (graphNode *n : current->neighbors){
		if (discovered.find(n) == discovered.end()) {
			parents[n] = current;
			printf("forward edge : %d -> %d\n", current->label, n->label);
			dfs(n, discovered, explored, parents);
		}
		// n would have been explored if it was just discovered
		if (explored.find(n) == explored.end()) {
			printf("backward edge : %d -> %d\n", current->label, n->label);
			if (parents[current] != n) {
				printf("cycle detected when we see edge %d->%d\n", current->label, n->label);
			}
		}
	}

	explored.insert(current);
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

	v2->neighbors.push_back(v1);
	v2->neighbors.push_back(v3);
	// v2->neighbors.push_back(v4);

	// v3->neighbors.push_back(v1);
	v3->neighbors.push_back(v2);
	v3->neighbors.push_back(v4);

	v4->neighbors.push_back(v1);
	// v4->neighbors.push_back(v2);
	v4->neighbors.push_back(v3);

	printf("\n-----perform bfs-----\n");
	bfs(v1);

	printf("\n-----trace path from v1 to v3-----\n");
	trace_path(v1, v3);

	printf("\n-----check if graph bipartite-----\n");
	isBipartite(v1) ? printf("is graph bipartite? yes\n") : printf("is graph bipartite? no\n");


	printf("\n-----perform dfs-----\n");
	unordered_set<graphNode*> discovered;
	unordered_set<graphNode*> explored;
	unordered_map<graphNode*, graphNode*> parents;
	dfs(v1, discovered, explored, parents);
}