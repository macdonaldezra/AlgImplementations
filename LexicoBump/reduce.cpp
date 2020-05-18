// Course: CSCI 422
// Student: Ezra MacDonald
// Date: October 15, 2019

#include "poset.h"
#include <iostream>


int main(int argc, char **argv)
{
   poset P;

   if (argc < 2) {
      cout << "Must pass filename as command line argument." << endl;
      exit(0);
   }

   P.posetRead(argv[1]);
   P.posetWrite(argv[1]);

   return 0;
}

