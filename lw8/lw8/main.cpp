#include <iostream>
#include <queue>
#include <vector>

std::vector<size_t> TopologicalSort(const std::vector<std::vector<bool>>& matrix) {
    std::vector<bool> visited(matrix.size(), false);
    std::vector<size_t> result;

    for (size_t iteration = 0; iteration < matrix.size(); ++iteration) {
        size_t j = 0;
        for (; j < visited.size() && visited[j]; ++j); // check for relevant vertex
        if (j == visited.size())
            break;
        bool marker = false;
        for (size_t i = 0; i < matrix.size(); ++i) {
            if (visited[i])
                continue;
            j = 0;
            for (; j < matrix.size() && !(matrix[j][i] && !visited[j]); ++j);
            if (j == matrix.size()) {
                result.push_back(i);
                visited[i] = true;
                marker = true;
            }
        }
        if (!marker)
            return std::vector<size_t>();
    }
    return result;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    std::vector<std::vector<bool>> matrix(n);
    for (size_t i = 0; i < n; ++i)
        matrix[i].assign(n, false);

    while (std::cin >> n >> m)
        matrix[n - 1][m - 1] = true;

    std::vector<size_t> res = TopologicalSort(matrix);

    if (res.empty())
        std::cout << -1;
    else
        for(size_t & i: res){
            std::cout << i + 1 << " ";
        }
    std::cout << std::endl;
    return 0;
}
