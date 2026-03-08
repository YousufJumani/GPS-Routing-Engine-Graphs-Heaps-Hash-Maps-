# GPS Routing Engine (Graphs + Heaps + Hash Maps)
<img width="1920" height="1080" alt="Untitled design (10)" src="https://github.com/user-attachments/assets/3fcdcbbd-145f-4d4d-92a4-99323c1418dc" />


## Problem It Solves
Finds the shortest route between two cities in a road network.

## Skills Covered
- Graph representation with adjacency lists
- Dijkstra's algorithm with min-heap (`priority_queue`)
- `std::unordered_map` for city-name to node lookup
- Path reconstruction using parent array

## Build and Run
```powershell
g++ -std=c++17 -O2 .\src\main.cpp -o gps.exe
.\gps.exe
```

## Why This Design
- Graph edges model roads naturally.
- Min-heap ensures the next best distance is explored first.
- Hash map provides O(1) average lookup from city names to graph indices.
- Parent tracking rebuilds human-readable route output.

## Complexity
- Time: `O((V + E) log V)`
- Space: `O(V + E)`


