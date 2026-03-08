# Design Logic

## Core Mental Model
Cities are graph nodes; roads are weighted edges. Shortest route is the minimum total edge weight path.

## Data Structure Choices
- `vector<vector<Edge>>`: compact adjacency list for sparse road networks.
- `unordered_map<string,int>`: maps city names to node ids for fast lookup.
- min-heap priority queue: always expands next closest node in Dijkstra.

## Algorithmic Reasoning
Dijkstra works because all edge weights are non-negative. Once a shortest distance is popped from heap, it is final.

## Path Reconstruction
Parent pointers preserve previous node for each relaxation. Reversing from destination to source builds final route.

## Complexity
`O((V+E) log V)` due to heap operations across edges.
