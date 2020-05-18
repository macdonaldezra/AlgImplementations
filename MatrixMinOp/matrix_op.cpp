// Author: Ezra MacDonald
// Compile Commpand: g++ -Wall matrix_op.cpp -o matrix_op

#include <iostream>
#include <string>

using namespace std;

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

// p[]: array of matrix dimensions
// dim: dimension of the passed array p
void matrixSize(int p[], int dim);

// i: starting row index
// j: starting col index
// s**: multidimensional array with split indices
void printOrder(int i, int j, int **s);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cout << "Must enter at least two matrix dimensions to run application." << endl
             << "Execute function with parameters: N dim1 dim2 ... dimN" << endl;
        exit(0);
    }

    int dim = atoi(argv[1])-1; 
    if (dim == 0) {
        cout << "Must provide an integer for number of dimensions." << endl;
        exit(0);
    }

    int p[dim];
    for (int i = 0; i <= dim; i++)
        p[i] = atoi(argv[i+2]);

    matrixSize(p, dim);

    return 0;
}

void matrixSize(int p[], int dim) {
    // minSum memoizes the count of matrix multiplication scalar operations
    int minSum[dim][dim];
    // split memoizes the split index required to minimze amount of said operations
    int** split = 0;
    split = new int*[dim];
    int row, col, k;

    // Initialize split array
    for (int m = 0; m < dim; m++)
        split[m] = new int[dim];

    // Initialize main diagonal with 0 values
    for (int q = 0; q < dim; q++) {
        minSum[q][q] = 0;
        split[q][q] = 0;
    }

    // Begin iterating from 
    for (int Link = 1; Link < dim; Link++) {
        for (row = 0; row < dim-Link; row++) {
            // col determines the column that we are iterating up to
            // during each call of the internal loop.
            col = row + Link;
            // Set the current minimum to INT_MAX and use this value to hold the amount
            // of scalar operations required for two given matrices to be multiplied.
            minSum[row][col] = INT_MAX;
            // q holds the current sum of matrix scalar operations
            int q;
            for (k = row; k < col; k++) {
                // minSum[row][k]: Entry in minSum to left of current row & col index
                // minSum[k+1][col]: Entry in minSum below current row & col index
                // p[row]*p[k+1]*p[col+1]: Number of scalar operations from multiplying 
                //  given matrices
                q = minSum[row][k] + minSum[k+1][col] + p[row]*p[k+1]*p[col+1];
                // If current number of operations (given by q) is less than previously calculated
                // min sum, then replace minSum[row][col] with q and assign split index.
                if (q < minSum[row][col]) {
                    minSum[row][col] = q;
                    split[row][col] = k;
                }
            }
        }
    }

    // Print matrix multiplication order
    // dim-2 will begin detecting splits from the first row and the right-most position
    // in our split matrix.
    printOrder(0, dim-1, split);

    // Iterate over all k values and print 
    cout << " " << minSum[0][dim-1] << endl;
}



void printOrder(int i, int j, int **s) {
    // If diagonal indices match, print x to represent a given matrix
    if (i == j) {
        cout << "X";
    } else {
        // Recursively print brackets around matrices to indicate multiplication split
        cout << "(";
        printOrder(i, s[i][j], s);
        printOrder(s[i][j]+1, j, s);
        cout << ")";
    }
}
