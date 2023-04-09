#include <bits/stdc++.h>

const int MAX_N = 20007;

std::vector<std::pair<int,int>> adj[MAX_N];
std::vector<int> bridgeIds;

int numVertices, timer;
int visited[MAX_N], entryTime[MAX_N], lowestEntryTime[MAX_N];

void readData() {
    int numEdges, from, to;
    std::cout << "Input number of vertices and edges: ";
    std::cin >> numVertices >> numEdges;
    
    for (int i = 1; i <= numEdges; i++) {
        std::cout << "Input " << i << ") edge(from, to): ";
        std::cin >> from >> to;
        adj[from].push_back({to, i});
        adj[to].push_back({from, i});
    }
}

void dfs(int v, int parent, int edgeId) {
    visited[v] = true; 
    entryTime[v] = lowestEntryTime[v] = ++timer;

    for (auto edge : adj[v]) {
        int neighbor = edge.first;
        int id = edge.second;

        if (id == edgeId) continue; // skip the edge we came from

        if (visited[neighbor] == false) {
            dfs(neighbor, v, id);
            lowestEntryTime[v] = std::min(lowestEntryTime[v], lowestEntryTime[neighbor]);
            if (lowestEntryTime[neighbor] > entryTime[v]) {
                bridgeIds.push_back(id);
            }
        } else {
            lowestEntryTime[v] = std::min(lowestEntryTime[v], entryTime[neighbor]);
        }
    }
}

void findBridges() {
    for (int i = 1; i <= numVertices; i++) visited[i] = 0;
    for (int i = 1; i <= numVertices; i++) {
        if (visited[i] == 0) {
            dfs(i, -1, -1);
        }
    }

    sort(bridgeIds.begin(), bridgeIds.end());
    int numBridges = bridgeIds.size();
    std::cout << "Number of bridges: " << numBridges << '\n';
    for (auto id : bridgeIds) {
        std::cout << "Id of bridge: " << id << '\n';
    }
    for (int i = 1; i <= 6; i++) {
        std::cout << entryTime[i] << ' ';
    }
    std::cout << '\n';
    for (int i = 1; i <= 6; i++) {
        std::cout  << lowestEntryTime[i] << ' ';
    }

}

int main() {
    readData();
    findBridges();
    return 0;
}
