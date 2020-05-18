#include <string>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <vector>   // STL vector, for adjacency list; ability to iterate

using namespace std;


class poset {
   private:
      int n;
      vector<int> *UpperIdeal;  // array of neighbour-vector
                                // all subsequent entries are names of neighbours
      vector<int> *UpperCover;  // array of neighbour-vector
      bool **Less; // nxn array of less-than relations from data file
      bool **Covers; // nxn array of Lower Cover relations 
                     // Covers[i][j]==1 means i covers j

   public: 
      poset();
      poset(int num);
      int posetRead(char *fn);
      int posetWrite(char *fn);
	   ~poset();
      void destroy();
	   int numElements() { return n; }
      void computeReduction();
      void computeClosure();
};


	
