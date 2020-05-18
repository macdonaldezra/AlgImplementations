# General Overview:
Program is implements multiple Graph algorithms like BFS and Shortest Path. The data structure
is used to represent social connections between a list of provided users.

### Data Structures:
Queue - implemented using a growing array that doubles in size each time it reaches
capacity. Basic empty(), full(), enqueue(), and dequeue() functions have been implemented
all running in O(1) time. The growing function on the other hand has runtime O(N).

Graph - Implemented using an adjacency matrix that can have -1, 0 or 1 values within
each of its indices. An additional array is allocated with the graph to hold the
data nodes associated with each column in the graph. The graph data structure includes
algorithms that determine the maximum degree of a node within differing contexts, as well
as the maximum amount of connections a given node can have.

BreadthFirstSearch() & ShortestPath() - Runs in O(V+E) time where V denotes the vertices or 
number of users and E denotes the number of connections between users or edges.
MaxDegree() & MaxPositiveDegree() - Runs in O(V^2) given that once each Vertex is iterated over, 
it iterates of every other vertex in the VxV matrix in order to determine the total number of
edges of a given type that it shares with that vertex.
