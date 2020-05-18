#include "poset.h"

int NO_VERTEX=-1;

poset::poset(): n(0)
{
   n = 0;
}

poset::poset(int num): n(num)
{
}

int poset::posetRead(char *fn)
{
   destroy();

   ifstream f;

   f.open(fn);
   if (!f) {
      cerr << "File not openable. " << endl;
      return 0;
   }
   f >> n;
   // UpperIdeal holds all elements greater than indexed element in poset
   UpperIdeal = new vector<int>[n];
   // LowerCover holds all elements covering indexed element
   UpperCover = new vector<int>[n];
   Less = new bool* [n]; // Less is nxn array of bool 
   Covers = new bool* [n];

   for (int i=0; i < n; i++) {  // Less[u][v] means u<v in the poset
      Less[i] = new bool[n];
      Covers[i] = new bool[n];

      for (int j = 0; j < n; j++) {
         Less[i][j] = false;
         Covers[i][j] = false;
      }
   }
   
   cout << "Reading " << n <<  " nodes..." << endl;
   if (n > 100000) { 
      cerr << "n too large: " << n <<endl; 
      return 0;
   } // arbitrary

   int row;
   f >> row;
   
   int val;
   while (row < n && f) {
      f >> val;
	   while (val < n && f) {
         Less[row][val] = true;
         f >> val;
	   }
	   f >> row;
   }

   f.close();

   // compute transitive closure and transitive reduction
   computeClosure(); 
   computeReduction();

   return 1;
}

int poset::posetWrite(char *fn)
{
   ofstream o;

   // write transitive reduction file
   o.open((string(fn) + ".treduc").c_str());

   o << n << endl << endl;

   for (int u=0; u<n; u++) {
      o << u;

      vector<int>::iterator currneighb = UpperCover[u].begin();

      while (currneighb != UpperCover[u].end())
      {
         o << " " << *currneighb;
         currneighb ++;
      }
      o << " " << n << endl;
   }

   o << n << endl;

   o.close();

   cout << "Write successfully completed." << endl;

   return 1;
}

// destructor to call when all arrays are no longer needed
void poset::destroy() {
   if (n > 0) {
      for (int i = 0; i < n; i++) {
         delete [] Less[i];
         delete [] Covers[i];
      }
      delete [] Less;
      delete [] Covers;
      delete [] UpperIdeal;
      delete [] UpperCover;
   }
}

poset::~poset()
{
   destroy();
}


void poset::computeClosure() {
   for (int i = 0; i < n-1; i++) {
      for (int j = 0; j < n-1; j++) {
        for (int k = 0; k < n-1; k++) {
            Less[i][j] = Less[i][j] || (Less[k][j] && Less[i][k]);
        }
        // UpperIdeal: push jth column of ith row if it is greater than ith vertex.
        // LowerIdeal: if the jth column is greater than ith value, then we know that column i
        // is less than related to the jth vertex, thus i is on the LowerIdeal of the jth vertex.
        if (Less[i][j]) {
           UpperIdeal[i].push_back(j);
        }

        // Covers will begin by containing all values that a given
        // row is less than.
        Covers[i][j] = Less[i][j];
      }
   }
}


void poset::computeReduction() {
   for (int i = 0; i < n-1; i++) {
      for (int j = 0; j < n-1; j++) {
        for (int k = 0; k < n-1; k++) {
            // We apply De Morgan's law to the above algorithm to find Covers.
            // This removes the redundancy of relations for each of the ith rows
            Covers[i][j] = Covers[i][j] && !(Covers[k][j] && Covers[i][k]);
        }
        if (Covers[i][j]) {
           UpperCover[i].push_back(j);
        }
      }
   }
}

