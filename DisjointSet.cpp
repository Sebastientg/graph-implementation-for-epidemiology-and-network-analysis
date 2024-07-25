#include "DisjointSet.h"

using namespace std;

// Initializes a new set with the given node as its own parent and size of 1.
void DisjointSet::makeSet(const string& node) {
    parent[node] = node;
    size[node] = 1;
}

// Finds and returns the representative (root) of the set containing the given node.
// Uses path compression to optimize future queries.
string DisjointSet::find(const string& node) {
    if (parent[node] != node) {
        parent[node] = find(parent[node]); // Path compression
    }
    return parent[node];
}

// Merges the sets containing the two specified nodes.
// Uses union by size to attach the smaller tree under the larger tree.
void DisjointSet::Union(const string& node1, const string& node2) {
    string root1 = find(node1);
    string root2 = find(node2);

    if (root1 != root2) {
        if (size[root1] > size[root2]) {
            parent[root2] = root1;
        } else if (size[root1] < size[root2]) {
            parent[root1] = root2;
        } else {
            parent[root2] = root1;
            size[root1]++;
        }
    }
}
