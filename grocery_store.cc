#include <set>
#include <map>
#include <vector>
#include <limits.h>
#include <iostream>

using namespace std;

int solution(const vector<int> &A, const vector<int> &B, const vector<int> &C, const vector<int> &D) {

    // node, vector<node, weight>
    map<int, vector<pair<int, int> > > adj_list;    
    
    // construct adjacency list
    // undirected graph
    for (int i = 0; i < A.size(); ++i) {
        if (adj_list.find(A[i]) == adj_list.end()) {
            adj_list[A[i]] = vector<pair<int, int> >();    
        }
        adj_list[A[i]].push_back(make_pair(B[i], C[i]));

        if (adj_list.find(B[i]) == adj_list.end()) {
            adj_list[B[i]] = vector<pair<int, int> >();    
        }
        adj_list[B[i]].push_back(make_pair(A[i], C[i]));
    }

    int max_timeout = 0;
    for (int i = 0; i < D.size(); ++i) {
        if (D[i] > max_timeout) max_timeout = D[i];
    }
    
    // initialize dist vector to infinity except for source node = 0
    vector<int> dist(D.size(), INT_MAX);
    dist[0] = 0;
    
    vector<bool> seen(D.size(), false);


    // priority queue <weight, node>
    set<pair<int, int> > pq;
    pq.insert(make_pair(0, 0));
    while (!pq.empty()) { 
        int closest_node = pq.begin()->second;
        int closest_dist = pq.begin()->first;
        
        // mark visited
        if (seen[closest_node]) {
            continue;
        } else {
            seen[closest_node] = true;
        }

        if (closest_dist <= D[closest_node]) {
            // DONE!
            return closest_dist;
        }

        pq.erase(pq.begin());
        
        // potential optimization here
        // check if closest_dist > max_timeout
        if (closest_dist > max_timeout) return -1;

        // if has neighbors
        if (adj_list.find(closest_node) != adj_list.end()) {
            vector<pair<int, int> > neighbors = adj_list[closest_node];
            for (int i = 0; i < neighbors.size(); ++i) {
                int neighbor_node = neighbors[i].first;
                int edge_weight = neighbors[i].second;
                if (closest_dist + edge_weight < dist[neighbor_node]) {
                    // need to update priority queue
                    pq.erase(make_pair(dist[neighbor_node], neighbor_node));
                    pq.insert(make_pair(closest_dist + edge_weight, neighbor_node));
                    dist[neighbor_node] = closest_dist + edge_weight;
                }
            }
        }
    }
    // exhausted all the nodes
    return -1;
}