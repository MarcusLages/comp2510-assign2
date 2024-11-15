//
// Created by marcu on 12/11/2024.
//

#ifndef STUDENT_IO_H
#define STUDENT_IO_H

/**
 * Enum that represents all possible filters for students.
 */
typedef enum Filter {
    FILTER_DOMESTIC = 1,
    FILTER_INTERNATIONAL,
    FILTER_ALL
} Filter;
typedef enum Filter Filter;

/**
 * Function to read, sort and filter students from an input file
 * and output them to an output file.
 *
 * @param input_file input filename
 * @param output_file output filename
 * @param option filtering option according to Filter enum
 */
void filter_students(char *input_file, char *output_file, const Filter option);

/**
 * Function to transform the filter argument from the cmd line into an int
 * according to the Filter enum in student.h.
 *
 * @param filter_arg string argument from the cmd line that represents the filtering option
 * @return enum value with the filter option
 */
Filter get_filter_option(const char *filter_arg);

/**
 * Helper function to open an input file.
 *
 * @param input_file input filename
 * @return pointer to FILE buffer
 */
FILE* open_input_file(const char *input_file);

/**
 * Helper function to open an output file.
 *
 * @param output_file output filename
 * @return pointer to FILE buffer
 */
FILE* open_output_file(const char *output_file);

#endif //STUDENT_IO_H
