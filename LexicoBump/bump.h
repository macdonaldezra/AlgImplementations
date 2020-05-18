#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <vector>
#include <queue>

using namespace std;

class Bump {
    private:
        struct Entry {
            int lowerCovers;
            int priority;
            int id;
        };
        int N;

        // Priority Queue to hold our Ordered Set
        struct HighestPriority {
            bool operator() (const Entry &lhs, const Entry &rhs) const {
                return lhs.priority < rhs.priority;
            }
        };
        priority_queue<Entry, std::vector<Entry>, HighestPriority> BumpQueue;

        Entry *Nodes;
        // vector<Entry> Nodes;
        vector<int> *UpperCover;
        int getPriority();
        string concatenate(const string& str, int num);
        void lowerCovers(int index);
        void decrementUpperCovers(int index);
    public:
        Bump(char *fName);
        ~Bump();
        void buildQueue();
};