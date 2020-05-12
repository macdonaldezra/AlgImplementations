#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

using namespace std;

template<typename D>
class Queue{
private:
	struct Node {
		D data;
		Node *next;
	};
	Node *front, *rear;
	int size;
public:
	Queue() {
		front = 0;
		rear = 0;
		size = 0;
	}
	~Queue() {
		Node *victim = front;
		while (victim != 0) {
			Node *temp = victim->next;
			delete victim;
			victim = temp;
		}
	}

	void enqueue(D data) {
		Node *entry = new Node;
		entry->data = data;
		entry->next = 0;
		if (rear == 0) {
			front = rear = entry;
			return;
		}
		rear->next = entry;
		rear = entry;
	}

	D dequeue() {
		if (empty())
			return 0;

		Node *temp = front;
		D data = front->data;
		front = front->next;
		delete temp;

		if (empty())
			rear = 0;

		return data;
	}

	D peek() {
		return front->data;
	}

	bool empty() {
		return (front == 0);
	}
};
#endif
