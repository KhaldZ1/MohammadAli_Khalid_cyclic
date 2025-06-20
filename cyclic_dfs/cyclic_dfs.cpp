#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class CyclicDetectorDFS {
private:
    std::vector<std::vector<int>> adjMatrix;
    int numVertices;

    bool dfsUtil(int vertex, std::vector<bool>& visited, std::vector<bool>& recStack,
                 std::vector<int>& parent, std::vector<int>& cycle) {
        visited[vertex] = true;
        recStack[vertex] = true;

        for (int i = 0; i < numVertices; i++) {
            if (adjMatrix[vertex][i] == 1) {
                if (!visited[i]) {
                    parent[i] = vertex;
                    if (dfsUtil(i, visited, recStack, parent, cycle)) {
                        return true;
                    }
                }
                else if (recStack[i]) {
                    cycle.clear();
                    int curr = vertex;
                    while (curr != i) {
                        cycle.push_back(curr);
                        curr = parent[curr];
                    }
                    cycle.push_back(i);
                    cycle.push_back(vertex);
                    std::reverse(cycle.begin(), cycle.end());
                    return true;
                }
            }
        }

        recStack[vertex] = false;
        return false;
    }

public:
    CyclicDetectorDFS(const std::vector<std::vector<int>>& matrix)
        : adjMatrix(matrix), numVertices(matrix.size()) {}

    bool detectCycle(std::vector<int>& cycle) {
        std::vector<bool> visited(numVertices, false);
        std::vector<bool> recStack(numVertices, false);
        std::vector<int> parent(numVertices, -1);

        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                if (dfsUtil(i, visited, recStack, parent, cycle)) {
                    return true;
                }
            }
        }
        return false;
    }

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
    std::cout << "=== Cycle Detection using DFS ===" << std::endl;

    std::vector<std::vector<int>> graph1 = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}
    };

    std::cout << "\nTest Case 1:" << std::endl;
    CyclicDetectorDFS detector1(graph1);
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
    CyclicDetectorDFS detector2(graph2);
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
    CyclicDetectorDFS detector3(graph3);
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

    CyclicDetectorDFS customDetector(customGraph);
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
