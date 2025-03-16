#include <iostream>
#include "dijkstras.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " graph" << endl;
        return 1;
    }
    Graph G;
    file_to_graph(argv[1], G);
    int source = 0;
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    for (int i = 0; i < G.numVertices; i++) {
        if (distances[i] == INF) {
            std::cout << "No path found.\n";
    } else {
        std::vector<int> path = extract_shortest_path(distances, previous, i);
        for (size_t j = 0; j < path.size(); j++) {
            std::cout << path[j];
            if (j + 1 < path.size()) {
                std::cout << " ";
            }
        }
        std::cout << "\n";
        std::cout << "Total cost is " << distances[i] << "\n";
    }
    }
}