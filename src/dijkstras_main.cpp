#include "dijkstras.h"

int main() {
    Graph G;
    file_to_graph("large.txt", G);
    vector<int> previous;
    vector<int> distance = dijkstra_shortest_path(G, 0, previous);
    int n = G.numVertices - 1;
    for (int i = 0; i < n; ++i) {
        vector<int> path = extract_shortest_path(distance, previous, i);
        print_path(path, distance[i]);
    }
    return 0;
}