#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <ctime>

template<typename K, typename T>
class Queue {
private:
	struct Entry {
	    K key;
	    T *val;
	};
	int parent(int i) {	return (i-1)/2; }
	int left(int i) { return (2*i+1); }
	int right(int i) { return (2*i+2); }
	void swap(Entry *obj1, Entry *obj2) {
	    Entry temp = *obj1;
	    *obj1 = *obj2;
	    *obj2 = temp;
	}
public:
	int size;
	int count;
	Entry *data;
	class FullQueue
		{	};
	class EmptyQueue
		{	};

	Queue() {
	    size = 10;
	    count = 0;
	    data = new Entry[size];
	}

	Queue(int s) {
	    size = s;
	    count = 0;
	    data = new Entry[size];
	}

	~Queue() {
	    for (int i = 0; i < count; count++)
		delete data[i].val;
	    delete [] data;
	}

	// Enqueue adds a value to the end of the priority queue
	// then calles HeapUp from the index value to ensure the
	// minimum property is maintained.
	void Enqueue(K key, T &obj) throw (Queue::FullQueue) {
	    if (count == size)
		throw Queue::FullQueue();

	    count++;
	    int index = count-1;
	    data[index].val = &obj;
	    data[index].key = key;
	    HeapUp(index);
	}

	// HeapUp swaps the values of a parent and its child if the
	// parent value has a larger value than it's child element.
	void HeapUp(int i) {
	    while (i > 0 && data[parent(i)].key > data[i].key) {
		swap(&data[i], &data[parent(i)]);
		i = parent(i);
	    }
	}

	// HeapDown rearranges the data elements of all child objects
	// beginning from an index i, to ensure that the smallest value
	// is at i.
	void HeapDown(int i) {
	    int smallest;
	    while (left(i) < count) {
		if (right(i) >= count) {
	            smallest = left(i);
		} else {
		    if (data[left(i)].key < data[right(i)].key) {
		        smallest = left(i);
		    } else {
			smallest = right(i);
		    }
		}
		if (data[smallest].key < data[i].key) {
		    swap(&data[i], &data[smallest]);
		}
		    i = smallest;
		}
	}

	// RemoveMin removes value from the beginning of the priority queue,
	// then assigns the last value on the queue to the front of the
	// priority, and HeapDown from this value.
	T& RemoveMin() throw (Queue::EmptyQueue) {
	    if (count == 0)
	        throw Queue::EmptyQueue();

	    T &itr = *(data[0].val);
	    data[0] = data[count-1];
	    count--;
	    HeapDown(0);

	    return itr;
	}

	// RemoveRandom generates a random index value in the priority
	// queue, then swaps that value with the beginning of the priority
	// queue and then calls RemoveMin.
	T& RemoveRandom() throw (Queue::EmptyQueue) {
	    if (count == 0)
		throw Queue::EmptyQueue();

	    srand(time(NULL));
	    int random = rand() % count;
	    swap(&data[0], &data[random]);
	    return RemoveMin();
	}
};
#endif
