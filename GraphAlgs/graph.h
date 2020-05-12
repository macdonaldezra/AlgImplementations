#ifndef GRAPH_H
#define GRAPH_H

#include "queue.h"
#include <iostream>
#include <fstream>

using namespace std;

template<typename D>
class Graph {
public:
	struct Node {
		int index;
		D *data;
	};
	class VertexDoesNotExist
		{	};
	class PathDoesNotExist
		{	};
		
	Graph();
	~Graph();
	void InsertEntry(D &data);
	void InsertEdge(D data2, D data1, int relationship);
	void InputData(string fileName);
	void OutputData(string fileName);

	void MaxPositiveDegree();
	void MaxDegree();
	void BreadthFirstSearch(D data) throw(Graph::VertexDoesNotExist);
	void ShortestPath(D data1, D data2) throw(Graph::VertexDoesNotExist, Graph::PathDoesNotExist);
private:
	int matrixSize;
	int **matrix;
	Node *entries;

	int getIndex(D data);
	D getData(int index);
	void displayPath(int *path, int start, int dest);
	// Utility function to swap two nodes in the array
	void swap(Node &val1, Node &val2) {
		Node temp = val1;
		val1 = val2;
		val2 = temp;
	}

	// A function that builds a n x n adj matrix where n = cap.
	// Each cell within the matrix is assigned a value of 0.
	void buildGraph(int cap) {
		matrixSize = cap;
		matrix = new int*[matrixSize];
		entries = new Node[matrixSize];
		for (int i = 0; i < matrixSize; i++) {
			matrix[i] = new int[matrixSize];
			for (int j = 0; j < matrixSize; j++)
				matrix[i][j] = 0;
		}
	}
};
#include "graph.inl.h"
#endif

