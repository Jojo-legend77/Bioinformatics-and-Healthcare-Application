#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
#include <stack>
#include <string>

using namespace std;

// Define a structure for a weighted edge
struct Edge {
    string destination; // Destination node (e.g., patient ID, gene name)
    double weight;      // Weight of the edge (e.g., similarity score, interaction strength)
};

// Weighted Graph class using adjacency list representation
class WeightedGraph {
private:
    unordered_map<string, list<Edge>> adjacencyList; // Adjacency list for the graph

public:
    // Add a node to the graph
    void addNode(const string& node) {
        if (adjacencyList.find(node) == adjacencyList.end()) {
            adjacencyList[node] = {}; // Initialize an empty list for the node
            cout << "Node '" << node << "' added successfully.\n";
        } else {
            cout << "Node '" << node << "' already exists.\n";
        }
    }

    // Add a weighted edge between two nodes
    void addEdge(const string& source, const string& destination, double weight) {
        // Ensure both nodes exist in the graph
        addNode(source);
        addNode(destination);

        // Add the edge from source to destination
        adjacencyList[source].push_back(Edge{destination, weight});
        cout << "Edge added from '" << source << "' to '" << destination << "' with weight " << weight << ".\n";
    }

    // Delete a node from the graph
    void deleteNode(const string& node) {
        if (adjacencyList.find(node) != adjacencyList.end()) {
            // Remove all edges pointing to the node
            for (auto& pair : adjacencyList) {
                pair.second.remove_if([&node](const Edge& edge) { return edge.destination == node; });
            }
            // Remove the node itself
            adjacencyList.erase(node);
            cout << "Node '" << node << "' deleted successfully.\n";
        } else {
            cout << "Node '" << node << "' does not exist.\n";
        }
    }

    // Update the weight of an edge
    void updateWeight(const string& source, const string& destination, double newWeight) {
        if (adjacencyList.find(source) != adjacencyList.end()) {
            for (Edge& edge : adjacencyList[source]) {
                if (edge.destination == destination) {
                    edge.weight = newWeight;
                    cout << "Weight updated for edge from '" << source << "' to '" << destination << "' to " << newWeight << ".\n";
                    return;
                }
            }
        }
        cout << "Edge from '" << source << "' to '" << destination << "' does not exist.\n";
    }

    // Breadth-First Search (BFS) traversal
    void BFS(const string& startNode) const {
        if (adjacencyList.find(startNode) == adjacencyList.end()) {
            cout << "Start node '" << startNode << "' does not exist.\n";
            return;
        }

        unordered_map<string, bool> visited;
        queue<string> q;

        q.push(startNode);
        visited[startNode] = true;

        cout << "BFS Traversal starting from '" << startNode << "': ";
        while (!q.empty()) {
            string currentNode = q.front();
            q.pop();
            cout << currentNode << " ";

            for (const Edge& edge : adjacencyList.at(currentNode)) {
                if (!visited[edge.destination]) {
                    visited[edge.destination] = true;
                    q.push(edge.destination);
                }
            }
        }
        cout << endl;
    }

    // Depth-First Search (DFS) traversal
    void DFS(const string& startNode) const {
        if (adjacencyList.find(startNode) == adjacencyList.end()) {
            cout << "Start node '" << startNode << "' does not exist.\n";
            return;
        }

        unordered_map<string, bool> visited;
        stack<string> s;

        s.push(startNode);

        cout << "DFS Traversal starting from '" << startNode << "': ";
        while (!s.empty()) {
            string currentNode = s.top();
            s.pop();

            if (!visited[currentNode]) {
                visited[currentNode] = true;
                cout << currentNode << " ";

                for (const Edge& edge : adjacencyList.at(currentNode)) {
                    if (!visited[edge.destination]) {
                        s.push(edge.destination);
                    }
                }
            }
        }
        cout << endl;
    }

    // Print the graph
    void printGraph() const {
        cout << "Weighted Graph Representation:" << endl;
        for (const auto& pair : adjacencyList) {
            cout << pair.first << " -> ";
            for (const Edge& edge : pair.second) {
                cout << "(" << edge.destination << ", " << edge.weight << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    WeightedGraph graph;
    int choice;
    string source, destination;
    double weight;

    do {
        cout << "\ngraph representation and application :\n";
        cout << "1. Add Node\n";
        cout << "2. Add Edge\n";
        cout << "3. Delete Node\n";
        cout << "4. Update Edge Weight\n";
        cout << "5. BFS Traversal\n";
        cout << "6. DFS Traversal\n";
        cout << "7. Print Graph\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Add Node
                cout << "Enter node name: ";
                cin >> source;
                graph.addNode(source);
                break;

            case 2: // Add Edge
                cout << "Enter source node: ";
                cin >> source;
                cout << "Enter destination node: ";
                cin >> destination;
                cout << "Enter edge weight: ";
                cin >> weight;
                graph.addEdge(source, destination, weight);
                break;

            case 3: // Delete Node
                cout << "Enter node to delete: ";
                cin >> source;
                graph.deleteNode(source);
                break;

            case 4: // Update Edge Weight
                cout << "Enter source node: ";
                cin >> source;
                cout << "Enter destination node: ";
                cin >> destination;
                cout << "Enter new weight: ";
                cin >> weight;
                graph.updateWeight(source, destination, weight);
                break;

            case 5: // BFS Traversal
                cout << "Enter start node for BFS: ";
                cin >> source;
                graph.BFS(source);
                break;

            case 6: // DFS Traversal
                cout << "Enter start node for DFS: ";
                cin >> source;
                graph.DFS(source);
                break;

            case 7: // Print Graph
                graph.printGraph();
                break;

            case 8: // Exit
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}