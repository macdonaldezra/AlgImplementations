#include "fft.h"


long double complex* recursiveFFT(long double complex *coeffs, int N) {
    long double complex *even, *odd;
    if (N == 1) {
        return coeffs;
    }

    // Divide coeffs array into odd and even pairs
    even = malloc(sizeof(long double complex) * (N/2));
    odd = malloc(sizeof(long double complex) * (N/2));
    for (int i = 0; i < N/2; i++) {
        even[i] = coeffs[i*2];
        odd[i] = coeffs[i*2+1];
    }

    long double complex *q = recursiveFFT(even, N/2);
    long double complex *r = recursiveFFT(odd, N/2);

    // Evaluate at kth roots and combine
    long double complex *yOut = malloc(sizeof(long double complex) * N);
    for (int k = 0; k < N/2; k++) {
        long double kthRoot = k * 2*M_PI / (long double) N;
        long double complex kthCoefficient = cosl(kthRoot) + sinl(kthRoot)*I;
        yOut[k] = q[k] + (kthCoefficient * r[k]);
        yOut[k+N/2] = q[k] - (kthCoefficient * r[k]);
    }

    free(even);
    free(odd);
    return yOut;
}


long double complex* recursiveIFFT(long double complex *coeffs, int N) {
    for (int i = 0; i < N; i++) {
        coeffs[i] = conjl(coeffs[i]);
    }
    coeffs = recursiveFFT(coeffs, N);

    for (int i = 0; i < N; i++) {
        coeffs[i] = conjl(coeffs[i]) * (1/(long double)N);
    }

    return coeffs;
}


int reverseBits(unsigned int oldIndex, int logN) {
    unsigned int index = 0;
    for (int i = 0; i < logN; i++) {
        index <<= 1;
        index |= (oldIndex & 1);
        oldIndex >>= 1;
    }
    return index;
}


long double complex* iterativeFFT(long double complex *coeffs, unsigned int N) {
    unsigned int logN = log2(N); // Note, that of course N must be a valid power of 2
    long double complex *outArr = malloc(sizeof(long double complex) * N);

    unsigned int revIndex;
    for (unsigned int i = 0; i < N; i++) {
        revIndex = reverseBits(i, logN);
        outArr[i] = coeffs[revIndex];
    }

    for (int s = 1; s <= logN; s++) {
        int m = 1 << s; // 2 ^ k using left bit-shift
        int m2 = m >> 1; // (m/2)-1
        long double complex nthRoot = CMPLXL(1, 0);
        long double complex J = CMPLXL(0, 1);


        long double complex principleRoot = cexpl(J*(M_PI/m2));
        long double complex temp;
        long double complex twiddleFactor;
        for (int k = 0; k < m2; k++) {
            for (int j = k; j < N; j = j + m) {
                twiddleFactor = nthRoot * outArr[j+m2];
                temp = outArr[j];
                outArr[j] = temp + twiddleFactor;
                outArr[j+m2] = temp - twiddleFactor;
            }
            nthRoot = nthRoot * principleRoot;
        }
    }

    return outArr;
 }

long double complex* iterativeIFFT(long double complex *coeffs, unsigned int N) {
    for (int i = 0; i < N; i++) {
        coeffs[i] = conjl(coeffs[i]);
    }
    coeffs = iterativeFFT(coeffs, N);

    for (int i = 0; i < N; i++) {
        coeffs[i] = conjl(coeffs[i]) * (1/(long double)N);
    }

    return coeffs;
}