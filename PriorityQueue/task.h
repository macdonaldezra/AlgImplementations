#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Task {
private:
	string user, command, resources;
public:
	double time;
	Task();
	Task(ifstream &fin);
	Task(const Task &obj);
	~Task();
	double GetTime();
	string GetUser();
	string GetCommand();
	string GetResources();
	void DisplayTask();
	void Output(ofstream & fout);
};
#endif
