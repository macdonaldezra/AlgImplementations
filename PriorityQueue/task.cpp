#include "task.h"

Task::Task() {
	time = GetTime();
	user = GetUser();
	command = GetCommand();
	resources = GetResources();
}

Task::Task(ifstream &fin) {
	string garbage;
	fin >> time;
	getline(fin, garbage);
	getline(fin, user);
	getline(fin, command);
	getline(fin, resources);
}

Task::Task(const Task &obj) {
	time = obj.time;
	user = obj.user;
	command = obj.command;
	resources = obj.resources;
}

Task::~Task() {
}

double Task::GetTime() {
	double value;
	string garbage;
	cout << "What is the time required for the task? " << endl;
	cin >> value;
	getline(cin, garbage);
	while (value < 0 || 100 < value) {
		cout << "Time must be less than between 0 and 100." << endl;
		cin >> value;
		getline(cin, garbage);
	}
	return value;
}

string Task::GetUser() {
	string value;
	cout << "Who is entering this task? " << endl;
	getline(cin, value);
	while (value == "" || 8 < value.length()) {
		cout << "User name must be less than 9 characters." << endl;
		getline(cin, value);
	}
	return value;
}

string Task::GetCommand() {
	string value, garbage;
	cout << "What is the command required to begin task? " << endl;
	cin >> value;
	getline(cin, garbage);
	while (value == "") {
		cout << "Task cannot be empty." << endl;
		cin >> value;
		getline(cin, garbage);
	}
	return value;
}

string Task::GetResources() {
	string value;
	cout << "What resources do you require? " << endl;
	getline(cin, value);
	while (value == "" || 80 < value.length()) {
		cout << "Description must be less than 80 characters." << endl;
		getline(cin, value);
	}
	return value;
}

void Task::DisplayTask() {
	cout << "     Time: " << time << endl
	     << "	  User: " << user << endl
	     << "  Command: " << command << endl
	     << "Resources: " << resources << endl;
}

void Task::Output(ofstream & fout) {
	fout << time << endl
	     << user << endl
	     << command << endl
	     << resources << endl;
}
