#include "bump.h"


using namespace std;


Bump::Bump(char *fName) {
    N = 0;
    ifstream inFile;

    inFile.open(fName);
    if (!inFile) {
        cerr << "File is not openable. " << endl;
        return;
    }

    inFile >> N;

    if (N > 100000) {
        cerr << "N is too large" << endl;
        return;
    }

    srand(time(NULL));

    // Allocate an array of ints for each node in our reduction
    UpperCover = new vector<int>[N];
    Nodes = new Entry[N];
    // Declare array to hold each of our rows

    int row = 0;
    inFile >> row;

    int val;
    while (row < N && inFile) {
        inFile >> val;
        // create new entry and add to Nodes data structure
        Entry newEntry;
        newEntry.priority = getPriority();
        newEntry.lowerCovers = 0;
        newEntry.id = row;
        Nodes[row] = newEntry;
        // Nodes.push_back(newEntry);

        while (val < N && inFile) {
            UpperCover[row].push_back(val);
            inFile >> val;
        }
        inFile >> row;
    }

    inFile.close();

    for (int k = 0; k < N; k++) { lowerCovers(k); }
    buildQueue();
}


Bump::~Bump() {
    if (N > 0) {
        delete [] UpperCover;
    }
}


void Bump::lowerCovers(int index) {
    int covers = 0;

    // for all vertices less than N increment covers
    // whenever we find a path to the vertex given by index.
    for (int i = index-1; i >= 0; i--) {

        vector<int>::iterator j = UpperCover[i].begin();
        while (j != UpperCover[i].end()) {
            if (index == *j) {
                covers++;
            }
            j++;
        }
    }
    Nodes[index].lowerCovers = covers;
}

// Returns a random value between 100 and N where N > 100
int Bump::getPriority() {
    if (N > 100) {
        return (rand() % N + 1);
    }
    return (rand() % 100 + 1);
}

string Bump::concatenate(const string& str, int num) {
    ostringstream oss;
    oss << str << " " << num;
    return oss.str();
}

// For each vertex in the upper cover for the vertex denoted 
// by index decrement their lowerCovers by one.
void Bump::decrementUpperCovers(int index) {

    vector<int>::iterator j = UpperCover[index].begin();
    while (j != UpperCover[index].end()) {
        Nodes[*j].lowerCovers--;
        j++;
    }
}

void Bump::buildQueue() {
    int enqueued = 0; // number of elements processed by priority queue

    // Strings to hold our leastCovers and max priority elements
    string leastCovers = "";
    string priority = "";

    Entry temp;
    while (enqueued < N) {
        // Insert any elements into the priority queue that have 0 lower covers
        // remaining.
        for (int i = 0; i < N; i++) {
            if (Nodes[i].lowerCovers == 0) {
                BumpQueue.push(Nodes[i]);
                enqueued++;
                Nodes[i].lowerCovers = -1;
            }
        }

        // Remove all elements inserted in BumpQueue, ordered by their
        // max priority.
        while (!BumpQueue.empty()) {
            temp = BumpQueue.top();
            // Build leastCovers and priority string
            leastCovers = concatenate(leastCovers, temp.id);
            priority = concatenate(priority, temp.priority);
            // decrement all of the upper covers for popped element
            decrementUpperCovers(temp.id);
            if (!BumpQueue.empty()) {
                BumpQueue.pop();
            }
        }
    }

    cout << leastCovers << "\n"
         << "Priorities: " << priority << "\n";
}