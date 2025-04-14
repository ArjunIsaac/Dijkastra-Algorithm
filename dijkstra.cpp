#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int destination;
    int weight;
};

struct QueueNode {
    int vertex;
    int distance;
    
    bool operator<(const QueueNode& other) const {
        return distance > other.distance;
    }
};

void dijkstra(const vector<vector<Edge>>& graph, int source) {
    int num_nodes = graph.size();
    vector<int> distances(num_nodes, INT_MAX);
    vector<bool> visited(num_nodes, false);
    
    priority_queue<QueueNode> pq;
    distances[source] = 0;
    pq.push({source, 0});
    
    while (!pq.empty()) {
        int current = pq.top().vertex;
        pq.pop();
        
        if (visited[current]) continue;
        visited[current] = true;
        
        for (const Edge& edge : graph[current]) {
            int neighbor = edge.destination;
            int new_distance = distances[current] + edge.weight;
            
            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                pq.push({neighbor, new_distance});
            }
        }
    }
    
    cout << "Shortest distances from node " << source << ":\n";
    for (int i = 0; i < num_nodes; ++i) {
        if (distances[i] == INT_MAX) {
            cout << "Node " << i << ": unreachable\n";
        } else {
            cout << "Node " << i << ": " << distances[i] << "\n";
        }
    }
}

vector<vector<Edge>> createGraph(int num_nodes) {
    vector<vector<Edge>> graph(num_nodes);

    for (int i = 0; i < num_nodes; i++) {
        for (int j = i+1; j < num_nodes; j++) {
            int weight;
            if (i != j) {
                cout << "Enter the weight of edge from node " << i << " to node " << j 
                     << " (enter 0 if no edge exists): ";
                cin >> weight;
                    graph[i].push_back({j, weight});
                    graph[j].push_back({i,weight}); //since its undirected the weight applies both directions of the edge
                
                } 
        }
    }
    return graph;
}

int main() {
    int num_nodes;
    cout << "Enter the number of nodes: ";
    cin >> num_nodes; // get numbers of nodes

    vector<vector<Edge>> graph = createGraph(num_nodes); // send over number of nodes to make our network graph

    int start;
    cout << "Enter starting node:";
    cin >> start;
    dijkstra(graph, start);

    return 0;
}
