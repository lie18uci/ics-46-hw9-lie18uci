#include "dijkstras.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);
    previous.assign(n, -1);
    distance[source] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, source});
    while (!pq.empty()) {
        auto [dist_u, u] = pq.top(); 
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (auto& edge : G[u]) {
            int v = edge.dst;
            int w = edge.weight;
            if (!visited[v] && dist_u + w < distance[v]) {
                distance[v] = dist_u + w;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>&, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int curr = destination; curr != -1; curr = previous[curr]) {
        path.push_back(curr);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    if (v.empty()) {
        cout << "\n";
    } else {
        for (size_t i = 0; i < v.size(); i++) {
            cout << v[i];
            if (i + 1 < v.size()) {
                cout << " ";
            }
        }
        cout << "\n";
    }
    cout << "Total cost is " << total << "\n";
}