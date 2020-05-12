#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

const string Influence = "influence";
const string Controversial = "controversial";
const string Outreach = "outreach";
const string Link = "link";
const string Update = "update";
const string Help = "help";
const string Quit = "quit";

string readCommand();

string getVal();

int getInt();

void helpMenu();

int main(int argc, char *argv[]) {
	string fileName;
	if (argc != 2) {
		cout << "Sample usage: ./pex3 <filename>." << endl;
		return 0;
	}
	fileName = argv[1];
	Graph<string> network;
	network.InputData(fileName);

	helpMenu();
	string command = readCommand();
	string usr1, usr2;
	int dist;

	while (command != Quit) {
		 if (command == Influence) {
		 	network.MaxPositiveDegree();
		 } else if (command == Controversial) {
		 	network.MaxDegree();
		 } else if (command == Outreach) {
		 	usr1 = getVal();
		 	try {
			 	network.BreadthFirstSearch(usr1);
		 	} catch (Graph<string>::VertexDoesNotExist) {
		 		cout << usr1 << " does not exist." << endl;
		 	}
		 } else if (command == Link) {
		 	usr1 = getVal();
		 	usr2 = getVal();
		 	try {
			 	network.ShortestPath(usr1, usr2);		 		
			 } catch (Graph<string>::VertexDoesNotExist) {
			 	cout << "One of the given users does not exist." << endl;
			 } catch (Graph<string>::PathDoesNotExist) {
			 	cout << "A path does not exist between the users." << endl;
			 }
		 } else if (command == Update) {
		 	usr1 = getVal();
		 	usr2 = getVal();
		 	dist = getInt();
		 	network.InsertEdge(usr1, usr2, dist);
		 } else if (command == Help) {
		 	helpMenu();
		 } else {
		 	cout << "Unknown command." << endl;
		 }

		 command = readCommand();
	}
	network.OutputData(fileName);
	return 0;
}

string readCommand() {
	string command;
	cout << "------------------------" << endl
		 << "Enter your command: ";
	cin >> command;
	cin.ignore();
	cout << "------------------------" << endl;
	return command;
}

string getVal() {
	string val;
	cin >> val;
	cin.ignore();
	return val;
}

int getInt() {
	int val;
	cin >> val;
	cin.ignore();
	return val;
}

void helpMenu() {
	cout << "/////////////////////////////////////////////////////////////////////////" << endl
		 << "Enter " << Influence << "  to list the name of the user who can directly and"
		 << "\n\tpositively influence the most users." << endl
		 << "      " << Controversial << "  to list the name of the user who can directly"
		 << "\n\tinfluence the most users." << endl
		 << "      " << Outreach << " user1  to count the total number of users that user1"
		 << "\n\tcan influence directly, indirectly, positively or negatively." << endl
		 << "      " << Link << " user1 user2  to list the shortest positive influence"
		 << "\n\tfrom user1 to user2." << endl
		 << "      " << Update << " user1 user2 edge  to update the influence distance from"
		 << "\n\tuser1 to user2 with the new edge value provided." << endl
		 << "      " << Help << "  to show this menu." << endl
		 << "      " << Quit << "  to quit the program." << endl
		 << "/////////////////////////////////////////////////////////////////////////" << endl;
}









