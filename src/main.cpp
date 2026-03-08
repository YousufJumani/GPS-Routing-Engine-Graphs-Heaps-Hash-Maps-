#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

struct Edge {
    int to;
    int weight;
};

struct State {
    int dist;
    int node;
    bool operator>(const State &other) const {
        return dist > other.dist;
    }
};

class Graph {
private:
    std::vector<std::vector<Edge>> adj_;
    std::unordered_map<std::string, int> cityToIndex_;
    std::vector<std::string> indexToCity_;

public:
    int addCity(const std::string &city) {
        auto it = cityToIndex_.find(city);
        if (it != cityToIndex_.end()) return it->second;

        int index = static_cast<int>(adj_.size());
        cityToIndex_[city] = index;
        indexToCity_.push_back(city);
        adj_.push_back({});
        return index;
    }

    void addRoad(const std::string &from, const std::string &to, int distance) {
        int u = addCity(from);
        int v = addCity(to);
        adj_[u].push_back({v, distance});
        adj_[v].push_back({u, distance});
    }

    bool shortestPath(const std::string &startCity,
                      const std::string &endCity,
                      int &outDistance,
                      std::vector<std::string> &outPath) const {
        auto itStart = cityToIndex_.find(startCity);
        auto itEnd = cityToIndex_.find(endCity);
        if (itStart == cityToIndex_.end() || itEnd == cityToIndex_.end()) return false;

        int n = static_cast<int>(adj_.size());
        int start = itStart->second;
        int goal = itEnd->second;

        std::vector<int> dist(n, INT_MAX);
        std::vector<int> parent(n, -1);
        std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            State current = pq.top();
            pq.pop();

            if (current.dist != dist[current.node]) continue;
            if (current.node == goal) break;

            for (const Edge &edge : adj_[current.node]) {
                int nextDist = current.dist + edge.weight;
                if (nextDist < dist[edge.to]) {
                    dist[edge.to] = nextDist;
                    parent[edge.to] = current.node;
                    pq.push({nextDist, edge.to});
                }
            }
        }

        if (dist[goal] == INT_MAX) return false;

        outDistance = dist[goal];
        std::vector<int> pathIndices;
        for (int node = goal; node != -1; node = parent[node]) {
            pathIndices.push_back(node);
        }
        std::reverse(pathIndices.begin(), pathIndices.end());

        outPath.clear();
        for (int idx : pathIndices) outPath.push_back(indexToCity_[idx]);
        return true;
    }
};

int main() {
    Graph graph;

    graph.addRoad("Delhi", "Agra", 233);
    graph.addRoad("Agra", "Jaipur", 238);
    graph.addRoad("Delhi", "Lucknow", 555);
    graph.addRoad("Lucknow", "Varanasi", 320);
    graph.addRoad("Jaipur", "Mumbai", 1148);
    graph.addRoad("Varanasi", "Kolkata", 680);
    graph.addRoad("Mumbai", "Bangalore", 981);
    graph.addRoad("Kolkata", "Bangalore", 1871);

    std::cout << "GPS Routing Engine (Dijkstra)\n";
    std::cout << "Available sample cities: Delhi, Agra, Jaipur, Lucknow, Varanasi, Mumbai, Kolkata, Bangalore\n";

    while (true) {
        std::cout << "\nEnter start city (or quit): ";
        std::string start;
        std::getline(std::cin, start);
        if (start == "quit") break;

        std::cout << "Enter destination city: ";
        std::string destination;
        std::getline(std::cin, destination);

        int distance = 0;
        std::vector<std::string> path;
        if (!graph.shortestPath(start, destination, distance, path)) {
            std::cout << "Route not found. Check city names.\n";
            continue;
        }

        std::cout << "Shortest distance: " << distance << " km\n";
        std::cout << "Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i] << (i + 1 < path.size() ? " -> " : "\n");
        }
    }

    return 0;
}
