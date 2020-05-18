# General Overview:
This program is a terminal driven run that analyzes connections between users
specified within a text file. Each user has a name and shares either positive or 
negative connections with other users. The program uses a graph to store and analyze
these relationships with support from a queue for breadth first searching.

### Implementation:
This program relies on a queue and graph libraries which are implemented in 
main.cpp. The graph implements a BFS algorithm to find the total 
number of other users reached within one users network as well as a variance of this
algorithm to find the shortest path between two users. The remaining algorithms concern
finding the shortest path between two users or vertices, which are both done using 
algorithms with runtime O(N^2).

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

### Testing:
This program has been tested by loading the data file pex3.data and manipulating said
data using commands within the specification requirements. A sample run of the program
is given in the file sampleoutput.txt.

