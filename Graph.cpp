#include "Graph.h"
#include "DisjointSet.h"
#include <fstream>
#include <sstream>
#include <algorithm>

// Constructor: Reads edges from a CSV file and initializes the graph.
Graph::Graph(const char* const & edgelist_csv_fn) {
    ifstream my_file(edgelist_csv_fn); // Open the file
    string line; // Helper variable to store the current line
    total_edges = 0;
                        
    while (getline(my_file, line)) {  // Read one line from the file
        istringstream ss(line);      // Create an istringstream for the current line
        string first, second, third; // Helper variables
        getline(ss, first, ',');     // Store first column in "first"
        getline(ss, second, ',');    // Store second column in "second"
        getline(ss, third, '\n');    // Store third column in "third"

        insert(first, second, stod(third)); // Insert undirected edge
    }
    my_file.close();                 // Close the file when done

    // Populate node_labels from adjacency_list
    for (const auto& entry : adjacency_list) {
        node_labels.push_back(entry.first);
    }
    total_nodes = node_labels.size();
}

// Inserts an undirected edge into the adjacency list.
void Graph::insert(string const & start_label, string const & end_label, double const & edge_weight) {
    adjacency_list[start_label].insert({end_label, edge_weight});
    adjacency_list[end_label].insert({start_label, edge_weight});
    total_edges++;
}

// Returns the number of nodes in the graph.
unsigned int Graph::num_nodes() {
    return total_nodes;
}

// Returns a vector of node labels in the graph.
vector<string> Graph::nodes() {
    return node_labels;
}

// Returns the number of edges in the graph.
unsigned int Graph::num_edges() {
    return total_edges;
}

// Returns the number of neighbors for a given node.
unsigned int Graph::num_neighbors(string const & node_label) {
    if (adjacency_list.find(node_label) != adjacency_list.end()) {
        return adjacency_list[node_label].size();
    } else {
        return 0;
    }
}

// Returns the weight of the edge between two nodes. Returns -1 if the edge does not exist.
double Graph::edge_weight(string const & u_label, string const & v_label) {
    if (adjacency_list.find(u_label) != adjacency_list.end()) {
        for (const auto& neighbor : adjacency_list[u_label]) {
            if (neighbor.first == v_label) {
                return neighbor.second;
            }
        }
    }

    return -1; // Edge does not exist
}

// Returns a vector of neighbors for a given node.
vector<string> Graph::neighbors(string const & node_label) {
    vector<string> result;
    if (adjacency_list.find(node_label) != adjacency_list.end()) {
        for (const auto& neighbor : adjacency_list[node_label]) {
            result.push_back(neighbor.first);
        }
    }
    return result;
}

// Finds the shortest path between two nodes using BFS (for unweighted graphs).
vector<string> Graph::shortest_path_unweighted(string const & start_label, string const & end_label) {
    vector<string> result;

    // Only one node in the path
    if (start_label == end_label) {
        result.push_back(start_label);
        return result;
    }

    // Initialize BFS variables
    queue<string> q;
    unordered_map<string, string> parent; // To reconstruct the path
    unordered_set<string> visited; // To track visited nodes

    q.push(start_label);
    visited.insert(start_label);

    bool found = false;

    while (!q.empty() && !found) {
        string current = q.front();
        q.pop();

        if (adjacency_list.find(current) != adjacency_list.end()) {
            for (const auto& neighbor : adjacency_list[current]) {
                if (visited.find(neighbor.first) == visited.end()) {
                    visited.insert(neighbor.first);
                    parent[neighbor.first] = current;
                    q.push(neighbor.first);

                    if (neighbor.first == end_label) {
                        found = true;
                        break;
                    }
                }
            }
        }
    }

    if (found) {
        // Reconstruct the path
        for (string i = end_label; i != start_label; i = parent[i]) {
            result.push_back(i);
        }
        result.push_back(start_label);
        reverse(result.begin(), result.end());
    }

    return result;
}

// Finds the shortest path between two nodes using Dijkstra's algorithm (for weighted graphs).
vector<tuple<string,string,double>> Graph::shortest_path_weighted(string const & start_label, string const & end_label) {
    if (start_label == end_label) {
        return { make_tuple(start_label, start_label, -1) };
    }

    // Priority queue for Dijkstra's algorithm
    priority_queue<tuple<double, string, string>, vector<tuple<double, string, string>>, Compare> pq;

    // Distance and previous node maps
    unordered_map<string, double> dist;
    unordered_map<string, string> prev;
    unordered_set<string> done;

    // Initialize distances and previous nodes
    for (const auto& node : node_labels) {
        dist[node] = numeric_limits<double>::infinity();
        prev[node] = "";
    }

    // Set start node distance to 0 and add it to the priority queue
    dist[start_label] = 0;
    pq.push({0.0, start_label, start_label});

    while (!pq.empty()) {
        tuple<double, string, string> top = pq.top();
        pq.pop();
        
        double current_dist = get<0>(top);
        string current = get<1>(top);
        string from = get<2>(top);

        if (done.find(current) != done.end()) continue; // Skip if already processed

        done.insert(current);

        for (const auto& neighbor : adjacency_list[current]) {
            string neighbor_label = neighbor.first;
            double weight = neighbor.second;

            if (done.find(neighbor_label) == done.end()) {
                double new_dist = current_dist + weight;
                if (new_dist < dist[neighbor_label]) {
                    dist[neighbor_label] = new_dist;
                    prev[neighbor_label] = current;
                    pq.push(make_tuple(new_dist, neighbor_label, current));
                }
            }
        }
    }

    if (dist[end_label] == numeric_limits<double>::infinity()) {
        return {};  // No path found
    }

    // Reconstruct the path
    vector<tuple<string, string, double>> result;
    for (string i = end_label; i != start_label; i = prev[i]) {
        string from = prev[i];
        double weight = dist[i] - dist[from];
        result.push_back(make_tuple(from, i, weight));
    }

    reverse(result.begin(), result.end());

    return result;
}

// Finds all connected components with edge weights below a given threshold.
vector<vector<string>> Graph::connected_components(double const & threshold) {
    vector<vector<string>> components;
    unordered_set<string> visited;

    for (const auto& node_entry : adjacency_list) {
        const string& start_node = node_entry.first;

        if (visited.find(start_node) == visited.end()) {
            vector<string> component;
            queue<string> q;
            q.push(start_node);
            visited.insert(start_node);

            while (!q.empty()) {
                string current_node = q.front();
                q.pop();
                component.push_back(current_node);

                for (const auto& neighbor : adjacency_list[current_node]) {
                    const string& neighbor_node = neighbor.first;
                    double weight = neighbor.second;

                    if (weight <= threshold && visited.find(neighbor_node) == visited.end()) {
                        q.push(neighbor_node);
                        visited.insert(neighbor_node);
                    }
                }
            }

            components.push_back(component);
        }
    }

    return components;
}

// Finds the smallest threshold that connects two nodes in the graph.
double Graph::smallest_connecting_threshold(string const & start_label, string const & end_label) {
    if (start_label == end_label) {
        return 0;
    }

    vector<tuple<double, string, string>> edges;

    // Extract all edges and their weights from the adjacency list
    for (const auto& node_entry : adjacency_list) {
        const string& u = node_entry.first;
        for (const auto& neighbor : node_entry.second) {
            const string& v = neighbor.first;
            double weight = neighbor.second;
            edges.push_back(make_tuple(weight, u, v));
        }
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end());

    // Initialize Disjoint Set
    DisjointSet ds;
    for (const auto& node : node_labels) {
        ds.makeSet(node);
    }

    // Process edges in ascending order
    for (const auto& edge : edges) {
        double weight = get<0>(edge);
        const string& u = get<1>(edge);
        const string& v = get<2>(edge);

        ds.Union(u, v);

        // Check if nodes are now connected
        if (ds.find(start_label) == ds.find(end_label)) {
            return weight;
        }
    }

    return -1; // No connection found
}





