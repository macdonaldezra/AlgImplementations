#include <iostream>
#include "bump.h"

using namespace std;

int main(int argc, char **argv)
{
   if (argc < 2) {
      cout << "Must pass filename as command line argument." << endl;
      exit(0);
   }

   Bump B(argv[1]);

   return 0;
}

