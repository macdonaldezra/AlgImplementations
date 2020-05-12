template<typename D>
Graph<D>::Graph() {
	matrixSize = 0;
}

template<typename D>
void Graph<D>::InputData(string fileName) {
	ifstream fin;
	int numData;
	string garbage;
	fin.open(fileName.c_str());
	// read in data from file
	if (fin.is_open()) {
		fin >> numData;
		getline(fin, garbage);
		buildGraph(numData);
		int relation;

		for (int i = 0; i < numData; i++) {
			string *name = new string;
			getline(fin, *name);
			entries[i].data = name;
			entries[i].index = i;
		}

		string name1, name2, rel;
		while (!fin.eof() && !fin.fail()) {
			fin >> name1;
			fin >> name2;
			fin >> rel;
			relation = atoi(rel.c_str());
			getline(fin, garbage);
			InsertEdge(name1, name2, relation);
		}
	}
	fin.close();
}

template<typename D>
Graph<D>::~Graph() {
	for (int i = 0; i < matrixSize; i++)
		delete [] matrix[i];
	delete [] matrix;
	matrixSize = 0;
}

template<typename D>
void Graph<D>::OutputData(string fileName) {
	ofstream fout;
	fout.open(fileName.c_str());
	if (fout.is_open()) {
		fout << matrixSize << endl;
		for (int x = 0; x < matrixSize; x++)
			fout << *(entries[x].data) << endl;

		for (int i = 0; i < matrixSize; i++) {
			for (int j = 0; j < matrixSize; j++) {
				if (matrix[i][j] != 0) {
					fout << *(entries[i].data) << " "
						 << *(entries[j].data) << " "
						 << matrix[i][j] << endl;
				}
			}
		}
	} else {
		cout << "Unable to open " << fileName << " to output data." << endl;
	}
	fout.close();
}

template<typename D>
void Graph<D>::InsertEntry(D &data) {
	entries[matrixSize].index = matrixSize;
	entries[matrixSize].data = &data;
	matrixSize++;
}

template<typename D>
void Graph<D>::InsertEdge(D data1, D data2, int relationship) {
	int ind1 = getIndex(data1);
	int ind2 = getIndex(data2);
	matrix[ind1][ind2] = relationship;
}

template<typename D>
int Graph<D>::getIndex(D data) {
	for (int i = 0; i < matrixSize; i++) {
		if (data == *(entries[i].data))
			return entries[i].index;
	}
	return -1;
}

template<typename D>
D Graph<D>::getData(int index) {
	if (index < 0 || matrixSize < index)
		return 0;
	return *(entries[index].data);
}

template<typename D>
void Graph<D>::MaxPositiveDegree() {
	Node *max = new Node[matrixSize];
	int i;
	for (i = 0; i < matrixSize; i++) {
		int status = 0;
		for (int j = 0; j < matrixSize; j++) {
			if (matrix[i][j] == 1)
				status++;
		}
		max[i].data = entries[i].data;
		max[i].index = status;
		// if this nodes degree is less than previous
		// nodes degree, then swap.
		if (max[i].index < max[i-1].index)
			swap(max[i], max[i-1]);
	}
	cout << *(max[i-1].data) << " has the most positive influence with " << 
			max[i-1].index << " connections." << endl;
	delete [] max;
}

template<typename D>
void Graph<D>::MaxDegree() {
	Node *max = new Node[matrixSize];
	int i;
	for (int i = 0; i < matrixSize; i++) {
		int status = 0;
		for (int j = 0; j < matrixSize; j++) {
			if (matrix[i][j] != 0)
				status++;
		}
		max[i].data = entries[i].data;
		max[i].index = status;
		// if this nodes degree is less than previous
		// nodes degree, then swap.
		if (max[i].index < max[i-1].index)
			swap(max[i], max[i-1]);
	}
	cout << *(max[matrixSize-1].data) << " has the most influence with " << 
			max[matrixSize-1].index << " connections." << endl;
	delete [] max;
}

template<typename D>
void Graph<D>::BreadthFirstSearch(D data) throw(Graph::VertexDoesNotExist) {
	int ind = getIndex(data);
	if (ind == -1)
		throw VertexDoesNotExist();
	
	bool *visited = new bool[matrixSize];
	for (int x = 0; x < matrixSize; x++)
		visited[x] = false;

	visited[ind] = true;
	int count = 0;

	Queue<int> queue;
	queue.enqueue(ind);
	while (!queue.empty()) {
		int top = queue.dequeue();

		for (int i = 0; i < matrixSize; i++) {
			if (matrix[top][i] != 0 && (!visited[i])) {
				queue.enqueue(i);
				visited[i] = true;
				count++;
			}
		}
	}
	cout << "The total number of connections for " << data << " is "
		 << count << "." << endl;
	delete [] visited;
}

template<typename D>
void Graph<D>::ShortestPath(D data2, D data1) throw(Graph::VertexDoesNotExist, Graph::PathDoesNotExist) {
	int ind1 = getIndex(data1);
	int ind2 = getIndex(data2);
	if (ind1 == -1 || ind2 == -1)
		throw VertexDoesNotExist();

	int *pred = new int[matrixSize];
	bool *visited = new bool[matrixSize];
	for (int i = 0; i < matrixSize; i++) {
		pred[i] = -1;
		visited[i] = false;
	}

	visited[ind1] = true;
	Queue<int> queue;
	queue.enqueue(ind1);
	while (!queue.empty()) {
		int top = queue.dequeue();
		for (int j = 0; j < matrixSize; j++) {
			if (matrix[top][j] == 1 && visited[j] == false) {
				pred[j] = top;
				visited[j] = true;
				queue.enqueue(j);
				if (j == ind2) {
					displayPath(pred, ind1, ind2);
					return;
				}
			}
		}
	}
	delete [] pred;
	delete [] visited;
	throw PathDoesNotExist();
}

template<typename D>
void Graph<D>::displayPath(int *path, int start, int dest) {
	cout << "The shortest path between the two nodes is: " << endl;
	D val;
	Queue<int> pathway;
	int crawl = dest;
	pathway.enqueue(crawl);
	int index;

	while(path[crawl] != -1) {
		pathway.enqueue(path[crawl]);
		index = pathway.dequeue();
		val = getData(index);
		cout << val << endl;
		crawl = path[crawl];
	}
	val = getData(start);
	cout << val << endl;
}
