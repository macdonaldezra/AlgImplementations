#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#include "fft.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

// Function to set size of array to be a power of 2
int set_size(int size);

void getCoefficients(FILE *inFile, int N, int max, long double complex *arr);

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: >./fft <filename>\n");
        exit(1);
    }

    FILE *inFile = fopen(argv[1], "r");
    if (inFile == NULL) {
        printf("Error: unable to open file <%s>\n", argv[1]);
        exit(1);
    }

    int AxSize, BxSize; // number of Ax and Bx coefficients respectively
    fscanf(inFile, "%d", &AxSize);
    fscanf(inFile, "%d", &BxSize);

    int productSize = max(AxSize, BxSize); // size of product
    int arrSize = set_size(productSize);

    // allocate and pad complex number arrays
    long double complex *Ax = (long double complex *) calloc(arrSize, sizeof(long double complex));
    long double complex *Bx = (long double complex *) calloc(arrSize, sizeof(long double complex));
    long double complex *Cx = (long double complex *) calloc(arrSize, sizeof(long double complex));
    getCoefficients(inFile, AxSize, arrSize, &Ax[0]);
    getCoefficients(inFile, BxSize, arrSize, &Bx[0]);
    fclose(inFile);


    // output coefficients before multiplication
    printf("A(x) = %.2f ", creal(Ax[0]));
    for (int i = 1; i < arrSize; i++) {
        printf("%- .2fx^%d ", creal(Ax[i]), i);
    }
    printf("\nB(x) = %.2f ", creal(Bx[0]));
    for (int i = 1; i < arrSize; i++) {
        printf("%- .2fx^%d ", creal(Bx[i]), i);
    }

    // Compute product of A(x) and B(x)
    Ax = recursiveFFT(Ax, arrSize/2);
    Bx = iterativeFFT(Bx, arrSize/2);

    // long double complex *Cx = (long double complex *) calloc(arrSize, sizeof(long double complex));
    printf("\n\nAbout to print the computed FFT's: \n");
    for (int i = 0; i < arrSize/2; i++) {
        Cx[i] = Ax[i] * Bx[i];
    }

    Cx = recursiveIFFT(Cx, arrSize);

    printf("\nA(x)*B(x) = ");
    printf("%- .2Lf ", creall(Cx[0]));
    for (int i = 1; i < productSize*2; i++) {
        printf("%- .2Lfx^%d ", creall(Cx[i]), i);
    }
    printf("\n\n");

    free(Ax);
    free(Bx);
    free(Cx);

    return 0;
}

int set_size(int size) {
    long double log_size = log2(size*2);
    return pow(2, ceil(log_size));
}

void getCoefficients(FILE *inFile, int N, int max, long double complex *arr) {
    long double temp;
    for (int i = 0; i < max; i++) {
        if (i < N) {
            fscanf(inFile, "%Lf", &temp);
            arr[i] = CMPLXL(temp, 0);
        } else {
            arr[i] = CMPLXL(0, 0);
        }
    }
}