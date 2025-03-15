#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    previous.resize(n, -1);
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});
    distance[source] = 0;
    while (!pq.empty()) {
        pair<int, int> current = pq.top();
        pq.pop();
        int u = current.second;
        if (visited[u]) {
            continue;
        }
        visited[u] = true;
        for (Edge neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;
            if (!visited[v] && (distance[u] + weight < distance[v])) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    int cur = destination;
    while (cur != -1) {
        path.push_back(cur);

        if (cur == 0) {
            return path;
        }
        cur = previous[cur];
    }
    std::reverse(path.begin(), path.end());
    return path;
}
void print_path(const vector<int>& v, int total) {
    int size = v.size();
    for (int i = 0; i < size; ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}