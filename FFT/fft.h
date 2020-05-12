#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <stdlib.h>


// Compute the recursive Fast Fourier Transform of an array of
// complex numbers. Note that N must indicate the size of the coeffs
// array.
long double complex* recursiveFFT(long double complex *coeffs, int N);

// Compute the recursive Inverse Fast Fourier Transform of an array of
// complex numbers. Note that N must indicate the size of the coeffs
// array.
long double complex* recursiveIFFT(long double complex *coeffs, int N);

// Reverse the bits of a provided index number
int reverseBits(unsigned int oldIndex, int logN);

// Compute the Fast Fourier Transform iteratively using butterfly
// operations as demonstrated in MIT's Introduction to Algorithms textbook
// found on p. 841.
long double complex* iterativeFFT(long double complex *coeffs, unsigned int N);

// Compute the recursive Inverse Fast Fourier Transform of an array.
long double complex* iterativeIFFT(long double complex *coeffs, unsigned int N);