#include <iostream>
#include <cstdlib>
#include "queue.h"
#include "task.h"

using namespace std;

const string Submit = "submit";
const string Help = "help";
const string Execute = "execute";
const string Random = "random";
const string Quit = "quit";

string readCommand();

void helpMenu();

void loadData(string fileName, Queue<double, Task> &Arr);

void outputData(string fileName, Queue<double, Task> &Arr);

void submitTask(Queue<double, Task> &Arr);

void executeTask(Queue<double, Task> &Arr);

void executeRandomTask(Queue<double, Task> &Arr);

int main(int argc, char *argv[]) {
	int size = 10;
	if (argc == 2)
	    size = atoi(argv[1]);

	Queue<double, Task> queue(size);

	string command;
	string filename = "batch.txt";
	loadData(filename, queue);

	helpMenu();
	command = readCommand();

	while (command != Quit) {
	    if (command == Submit) {
		submitTask(queue);
	    } else if (command == Execute) {
		executeTask(queue);
	    } else if (command == Help) {
		helpMenu();
	    } else if (command == Random) {
		executeRandomTask(queue);
	    } else {
		cout << "Unknown command." << endl;
	    }
	    command = readCommand();
	}
	outputData(filename, queue);
	return 0;
}

string readCommand() {
	string command, garbage;
	cout << "------------------------" << endl
	     << "Enter your command: ";
	cin >> command;
	getline(cin, garbage);
	return command;
}

void helpMenu() {
	cout << "Enter " << Submit << " to add a job to the task queue" << endl
	     << "      " << Help << " to see this menu" << endl
	     << "      " << Execute << " to execute a job with the shortest execution time" << endl
	     << "      " << Random << " to execute a job with a random execution time" << endl
	     << "      " << Quit << " to quit the program" << endl;
}

void loadData(string fileName, Queue<double, Task> &Arr) {
	ifstream fin;
	int numData;
	string garbage;
	fin.open(fileName.c_str());
	if (fin.is_open()) {
	    fin >> numData;
	    getline(fin, garbage);
	    if (Arr.size < numData) {
		cout << "Only " << Arr.size << " items will be entered on the task queue." << endl;
		    numData = numData - (numData - Arr.size);
		}
	    for (int i = 0; i < numData; i++) {
		Task *data = new Task(fin);
		Arr.Enqueue(data->time, *data);
	    }
	} else {
	    cout << "Unable to open " << fileName << " to read data." << endl
	         << "Assuming there are no tasks in the queue yet." << endl;
	}
	fin.close();
}

void outputData(string fileName, Queue<double, Task> &Arr) {
	ofstream fout;
	fout.open(fileName.c_str());
	if (fout.is_open()) {
	    fout << Arr.count << endl;
	    for (int i = 0; i < Arr.count; i++) {
		Task &entry = Arr.RemoveMin();
		entry.Output(fout);
		delete &entry;
	   }
	} else {
	   cout << "Unable to open " << fileName << " to output data." << endl;
	}
	fout.close();
}

void submitTask(Queue<double, Task> &Arr) {
	Task *entry = new Task();
	try {
	    Arr.Enqueue(entry->time, *entry);
	    cout << "Task has been successfully added to the priority queue." << endl;
	} catch (Queue<double, Task>::FullQueue) {
	    cout << "Task queue is full." << endl;
	}
}

void executeTask(Queue<double, Task> &Arr) {
	try {
	    Task &entry = Arr.RemoveMin();
	    entry.DisplayTask();
	    delete &entry;
	} catch (Queue<double, Task>::EmptyQueue) {
	    cout << "The task queue is empty." << endl;
	}
}

void executeRandomTask(Queue<double, Task> &Arr) {
	try {
	    Task &entry = Arr.RemoveRandom();
	    entry.DisplayTask();
	    delete &entry;
	} catch (Queue<double, Task>::EmptyQueue) {
	    cout << "The task queue is empty." << endl;
	}
}
