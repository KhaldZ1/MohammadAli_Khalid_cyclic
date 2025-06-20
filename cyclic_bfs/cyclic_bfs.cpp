#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class CyclicDetectorBFS {
private:
    std::vector<std::vector<int>> adjMatrix;
    int numVertices;

public:
    CyclicDetectorBFS(const std::vector<std::vector<int>>& matrix)
        : adjMatrix(matrix), numVertices(matrix.size()) {}

    bool detectCycle(std::vector<int>& cycle) {


        std::vector<int> inDegree(numVertices, 0);
        std::vector<std::vector<int>> adjList(numVertices);


        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (adjMatrix[i][j] == 1) {
                    adjList[i].push_back(j);
                    inDegree[j]++;
                }
            }
        }

        std::queue<int> q;
        std::vector<int> topoOrder;

        for (int i = 0; i < numVertices; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int vertex = q.front();
            q.pop();
            topoOrder.push_back(vertex);

            for (int neighbor : adjList[vertex]) {
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        if (topoOrder.size() != numVertices) {
            std::vector<bool> inCycle(numVertices, false);
            for (int i = 0; i < numVertices; i++) {
                if (inDegree[i] > 0) {
                    inCycle[i] = true;
                }
            }

            findCyclePath(inCycle, cycle);
            return true;
        }

        return false;
    }

private:
    void findCyclePath(const std::vector<bool>& inCycle, std::vector<int>& cycle) {
        std::vector<bool> visited(numVertices, false);
        std::vector<int> parent(numVertices, -1);

        int startVertex = -1;
        for (int i = 0; i < numVertices; i++) {
            if (inCycle[i]) {
                startVertex = i;
                break;
            }
        }

        if (startVertex == -1) return;

        if (dfsFindCycle(startVertex, visited, parent, inCycle, cycle)) {
            return;
        }
    }

    bool dfsFindCycle(int vertex, std::vector<bool>& visited, std::vector<int>& parent,
                      const std::vector<bool>& inCycle, std::vector<int>& cycle) {
        visited[vertex] = true;

        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[vertex][i] == 1 && inCycle[i]) {
                if (!visited[i]) {
                    parent[i] = vertex;
                    if (dfsFindCycle(i, visited, parent, inCycle, cycle)) {
                        return true;
                    }
                } else {
                    cycle.clear();
                    int curr = vertex;
                    cycle.push_back(i);
                    while (curr != i && curr != -1) {
                        cycle.push_back(curr);
                        curr = parent[curr];
                    }
                    if (curr == i) {
                        std::reverse(cycle.begin(), cycle.end());
                        cycle.push_back(i);
                    }
                    return true;
                }
            }
        }
        return false;
    }

public:
    void printMatrix() {
        std::cout << "Adjacency Matrix:" << std::endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                std::cout << adjMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    std::cout << "=== Cycle Detection using BFS (Kahn's Algorithm) ===" << std::endl;

    std::vector<std::vector<int>> graph1 = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };

    std::cout << "\nTest Case 1:" << std::endl;
    CyclicDetectorBFS detector1(graph1);
    detector1.printMatrix();

    std::vector<int> cycle1;
    if (detector1.detectCycle(cycle1)) {
        std::cout << "Graph is CYCLIC!" << std::endl;
        std::cout << "Cycle found: ";
        for (int i = 0; i < cycle1.size(); i++) {
            std::cout << cycle1[i];
            if (i < cycle1.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Graph is ACYCLIC!" << std::endl;
    }

    std::vector<std::vector<int>> graph2 = {
        {0, 1, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };

    std::cout << "\nTest Case 2:" << std::endl;
    CyclicDetectorBFS detector2(graph2);
    detector2.printMatrix();

    std::vector<int> cycle2;
    if (detector2.detectCycle(cycle2)) {
        std::cout << "Graph is CYCLIC!" << std::endl;
        std::cout << "Cycle found: ";
        for (int i = 0; i < cycle2.size(); i++) {
            std::cout << cycle2[i];
            if (i < cycle2.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Graph is ACYCLIC!" << std::endl;
    }

    std::vector<std::vector<int>> graph3 = {
        {1, 0, 0},
        {0, 0, 1},
        {0, 0, 0}
    };

    std::cout << "\nTest Case 3 (Self-loop):" << std::endl;
    CyclicDetectorBFS detector3(graph3);
    detector3.printMatrix();

    std::vector<int> cycle3;
    if (detector3.detectCycle(cycle3)) {
        std::cout << "Graph is CYCLIC!" << std::endl;
        std::cout << "Cycle found: ";
        for (int i = 0; i < cycle3.size(); i++) {
            std::cout << cycle3[i];
            if (i < cycle3.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Graph is ACYCLIC!" << std::endl;
    }

    std::cout << "\n=== Custom Graph Input ===" << std::endl;
    int n;
    std::cout << "Enter the number of vertices: ";
    std::cin >> n;

    std::vector<std::vector<int>> customGraph(n, std::vector<int>(n));
    std::cout << "Enter the adjacency matrix (0 or 1):" << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> customGraph[i][j];
        }
    }

    CyclicDetectorBFS customDetector(customGraph);
    customDetector.printMatrix();

    std::vector<int> customCycle;
    if (customDetector.detectCycle(customCycle)) {
        std::cout << "Your graph is CYCLIC!" << std::endl;
        std::cout << "Cycle found: ";
        for (int i = 0; i < customCycle.size(); i++) {
            std::cout << customCycle[i];
            if (i < customCycle.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Your graph is ACYCLIC!" << std::endl;
    }

    return 0;
}
