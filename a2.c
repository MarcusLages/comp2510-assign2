#include <stdio.h>
#include <stdlib.h>

#define MIN_ARGS    4

enum Args {
    ARG_PROGRAM_NAME,
    ARG_INPUT_FILE,
    ARG_OUTPUT_FILE,
    ARG_OPTION
};
typedef enum Args Args;

FILE* openOutputFile(char *outputFile);
void closeFiles(FILE *ptrIn, FILE *ptrOut);

int main(int argc, char **argv) {
    if(argc < MIN_ARGS) {
        perror("Not enough arguments for the program");
        return EXIT_FAILURE;
    }

    const char *inputFile = argv[ARG_INPUT_FILE];
    char *outputFile = argv[ARG_OUTPUT_FILE];
    const int option = atoi(argv[ARG_OPTION]);

    FILE *ptrIn = fopen(inputFile, "r");
    FILE *ptrOut = openOutputFile(outputFile);

    if(ptrIn == NULL) {
        perror("Input file not found.");
        return EXIT_FAILURE;
    }

    // Logic of the assignment
    // sort(ptrIn, ptrOut, option);

    closeFiles(ptrIn, ptrOut);

    return EXIT_SUCCESS;
}

FILE* openOutputFile(char *outputFile) {
    // Removes file so it can be written using append
    // It is inefficient , but this avoids having to keep track of the
    // data using an array
    remove(outputFile);

    FILE *ptrOut = fopen(outputFile, "a");

    return ptrOut;
}

void closeFiles(FILE *ptrIn, FILE *ptrOut) {
    fclose(ptrIn);
    ptrIn = NULL;

    fclose(ptrOut);
    ptrOut = NULL;
}