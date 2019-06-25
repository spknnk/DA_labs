#include <iostream>
#include <vector>
#include <limits>
#include <queue>

const unsigned long long inf = std::numeric_limits<unsigned long long>::max();

struct Edge {
    size_t dest = 0;
    size_t  weight = 0;
};

bool operator< (const Edge& left, const Edge& right) {
    return left.weight > right.weight;
}

using Graph = std::vector<std::vector<Edge>>;

std::vector<size_t> Dijkstra(const Graph& graph, size_t start) {

    auto size = graph.size();
    std::vector<size_t> distances(size, inf);
    distances[start] = 0;

    std::priority_queue<Edge> priority;
    Edge start_init {start, 0};
    priority.push(start_init);

    std::vector<bool> relaxed(size, false);

    while (!priority.empty()) {
        Edge top = priority.top();
        priority.pop();
        if (relaxed[top.dest]) {
            continue;
        }
        relaxed[top.dest] = true;
        for (const Edge& edge: graph[top.dest]) {
            size_t current_distance = distances[top.dest] + edge.weight;
            if (current_distance < distances[edge.dest]) {
                distances[edge.dest] = current_distance;
                Edge tmp{edge.dest, current_distance};
                priority.push(tmp);
            }
        }
    }

    return distances;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n,m, start, finish;
    std::cin >> n >> m >> start >> finish;
    --start, --finish;

    Graph graph(n);

    for (size_t it = 0; it < m; ++it) {
        size_t u, v, weight;
        std::cin >> u >> v >> weight;
        --u,--v;

        graph[u].push_back(Edge{v, weight});
        graph[v].push_back(Edge{u, weight});
    }

    auto distances = Dijkstra(graph, start);

    if (distances[finish] != inf) {
        std::cout << distances[finish] << std::endl;
    } else {
        std::cout << "No solution" << std::endl;
    }

    return 0;
}