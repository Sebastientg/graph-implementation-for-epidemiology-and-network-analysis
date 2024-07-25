#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <unordered_map>
#include <string>

using namespace std;

// Class to implement Disjoint Set operations, also known as Union-Find.
// This data structure is used to manage a collection of disjoint (non-overlapping) sets.
// It supports two primary operations efficiently:
// 1. `find`: Determine the representative or "root" of the set containing a particular element.
// 2. `union`: Merge two sets into a single set.

class DisjointSet {
public:
    // Creates a new set containing only the specified node.
    // Initializes the node to be its own parent (root of its set) and sets its size to 1.
    // 
    // @param node The node to create a set for. This should be a unique identifier for the set.
    void makeSet(const string& node);

    // Finds the representative or "root" of the set containing the specified node.
    // Uses path compression to flatten the structure of the tree whenever `find` is called,
    // making future queries faster.
    //
    // @param node The node whose set representative is to be found.
    // @return The representative of the set containing the node.
    string find(const string& node);

    // Merges the sets containing the two specified nodes into a single set.
    // Uses union by size to ensure the smaller set is added under the root of the larger set,
    // keeping the tree as flat as possible.
    //
    // @param node1 The first node to be merged.
    // @param node2 The second node to be merged.
    void Union(const string& node1, const string& node2);

private:
    // A map that stores the parent of each node. 
    // Each node points to its parent node, or itself if it is a root.
    unordered_map<string, string> parent;

    // A map that stores the size of the set for which each node is a root.
    // This helps in implementing union by size.
    unordered_map<string, int> size;
};

#endif
