#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>



int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: >./fft <max_coefficient_value> <max_number_of_coefficients>\n");
        exit(1);
    }

    DIR* dir = opendir("resource");
    if (dir) {
        closedir(dir);
    } else if (ENOENT == errno) {
        mkdir("./resource", 0700);
    } else {
        printf("Unable to output resource file.\n");
        exit(1);
    }

    srand(time(NULL));

    int maxVals = atoi(argv[1]);

    int maxCoefficient = atoi(argv[2]);
    int AxCoefficients = (rand() + 1) % maxCoefficient;
    int BxCoefficients = (rand() + 1) % maxCoefficient;

    char fileName[100] = "";
    sprintf(fileName, "resource/%dx%d.coeffs", AxCoefficients, BxCoefficients);
    FILE *outFile;


    outFile = fopen(fileName, "w");
    if (outFile == NULL) {
        printf("Error: unable to open file <%s>\n", argv[1]);
        exit(1);
    }

    int temp;
    fprintf(outFile, "%d ", AxCoefficients);
    fprintf(outFile, "%d\n", BxCoefficients);
    for (int i = 0; i < AxCoefficients; i++) {
        temp = (rand()+1) % maxVals;
        fprintf(outFile, "%d ", temp);
    }

    fprintf(outFile, "\n");
    for (int i = 0; i < BxCoefficients; i++) {
        temp = (rand()+1) % maxVals;
        fprintf(outFile, "%d ", temp);
    }

    fclose(outFile);

    return 0;
}
