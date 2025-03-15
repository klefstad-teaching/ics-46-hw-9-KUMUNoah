#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    previous.resize(n, -1);
    vector<int> distance;
    distance.resize(n, INF);
    vector<bool> visited;
    visited.resize(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, Compare> pq;
    pq.push({source, 0});
    distance[source] = 0;
    while (!pq.empty()) {
        pair<int, int> current = pq.top();
        pq.pop();
        int u = current.first;
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
                pq.push({v, distance[v]});
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
    return path;
}
void print_path(const vector<int>& v, int total) {
    int size = v.size();
    for (int i = size-1; i >=0; --i) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}