
# Graph Implementation for Epidemiology and Network Analysis

### Overview

This project focuses on the fundamental mathematical concept of graphs, which are essential in Computer Science for representing networks of connected entities. This implementation is designed to demonstrate graph theory applications in epidemiology, specifically in analyzing viral sequences and studying virus transmission clusters. The provided code is a Graph class API that allows for various operations on undirected graphs, such as computing shortest paths, connected components, and more.

### Background

In epidemiology, tools like HIV-TRACE (Pond et al., 2018) use graph-based methods to analyze viral sequence data. The tool constructs a graph where nodes represent viral sequences and edges are formed based on pairwise distances between sequences. This graph helps in identifying transmission clusters and provides insights into virus spread, aiding in prevention efforts.

## Files

- `Graph.h`: Header file defining the Graph class interface.
- `Graph.cpp`: Implementation of the Graph class methods.
- `GraphTest.cpp`: Test file to validate the functionality of the Graph class.
- `Makefile`: Build file for compiling the code.
- `small.csv` and `hiv.csv`: Example CSV files containing graph data.
  
## Features

- **Graph Construction**: Load a graph from a CSV file containing edges and weights.
- **Basic Properties**: Retrieve information about nodes, edges, and neighbors.
- **Shortest Path Algorithms**: Find the shortest path using unweighted or weighted algorithms.
- **Connected Components**: Determine connected components based on a weight threshold.
- **Threshold Calculation**: Calculate the smallest threshold needed for connectivity between nodes.

## Setup

### Prerequisites

Ensure you have `g++` installed with support for C++11.

### Building the Project

To compile the project, use the provided Makefile. Run the following command in your terminal:

```
make
```

To compile with profiling enabled using `gprof`, use:

```
make gprof
```

### Running Tests

After building the project, you can run the tests using the `GraphTest` executable. Specify the edge list CSV file and the test you want to run:

```
./GraphTest <edgelist_csv> <test>
```

Replace `<edgelist_csv>` with the path to your edge list file (e.g., `small.csv`) and `<test>` with one of the following options:

- `graph_properties`: Tests basic graph properties.
- `shortest_unweighted`: Tests shortest path computation for unweighted graphs.
- `shortest_weighted`: Tests shortest path computation for weighted graphs.
- `connected_components`: Tests the detection of connected components with a threshold.
- `smallest_threshold`: Tests the calculation of the smallest connecting threshold.

## Example Usage

To test basic graph properties with the `small.csv` file:

```
./GraphTest small.csv graph_properties
```

To compute the shortest weighted path:

```
./GraphTest small.csv shortest_weighted
```

## Acknowledgments

Thank you CSE 100 Advanced Data Structures for the challenging yet fascinating assignment. 
