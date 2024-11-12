//
// Created by marcu on 12/11/2024.
//

#ifndef STUDENT_IO_H
#define STUDENT_IO_H

typedef enum Filter {
    FILTER_DOMESTIC,
    FILTER_INTERNATIONAL,
    FILTER_ALL
} Filter;
typedef enum Filter Filter;

void filter_students(char *input_file, char *output_file, const Filter option);
Filter get_filter_option(const char *filter_arg);

FILE* open_input_file(const char *input_file);
FILE* open_output_file(const char *output_file);

#endif //STUDENT_IO_H
