#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "student-io.h"

int main(const int argc, char **argv) {
    if(argc < MIN_ARGS) {
        perror("Not enough arguments for the program");
        return EXIT_FAILURE;
    }

    const char *inputFile = argv[ARG_INPUT_FILE];
    const char *outputFile = argv[ARG_OUTPUT_FILE];
    const int option = get_filter_option(argv[ARG_OPTION]);

    // Logic of the assignment
    filter_students(inputFile, outputFile, option);

    return EXIT_SUCCESS;
}

Filter get_filter_option(const char *filter_arg) {
    char *error;
    Filter filter_option = strtod(filter_arg, &error);

    // If there was any error, sets the filter_option as FILTER_ALL
    if(((*error != '\n') && (*error != '\0' || error == filter_arg)) ||
        (filter_option < FILTER_DOMESTIC || filter_option > FILTER_ALL )) {

        perror("Invalid filter option. Using default filter as all students.\n");
        return FILTER_ALL;
        }

    return filter_option;
}