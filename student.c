//
// Created by marcu on 12/11/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void filter_students(char *input_file, char *output_file, const Filter option) {
    Student **students;
    const int student_count = read_students(input_file, students);

    if(student_count == 0) {
        printf("No students found in the input file.\n");
        return;
    }

    merge_sort(students, student_count);
    // write_to_file(output_file, students, student_count, option);

    free(students);
    students = NULL;
}

int read_students(const char *input_file, Student **students) {
    FILE *file = open_input_file(input_file);
    int student_count = INITIAL_CLASS_SIZE;
    char curr_line[MAX_LINE_SIZE];

    // TODO: read students with realloc
    while(fgets(curr_line, MAX_LINE_SIZE, file)) {
        resize_students_arr(students, student_count + 1);
        *students[student_count] = get_student_from_line(curr_line);
        student_count++;
    }

    fclose(file);

    return student_count;
}

void resize_students_arr(Student **students, int new_size) {
    if(new_size < MIN_STUDENTS_SIZE) {
        new_size = MIN_STUDENTS_SIZE;
    }

    *students = (Student *) realloc(students, new_size * sizeof(Student));

    if(*students == NULL) {
        perror("Could not allocate memory for student array.\n");
        exit(EXIT_FAILURE);
    }
}

Student get_student_from_line(char *curr_line) {
    Student student;

    char date[DATE_STRING_SIZE];
    char status;
    const int scanned_data = sscanf(curr_line, "%s %s %s %f %c %d",
                student.info.domestic.last_name,
                student.info.domestic.first_name,
                date,
                &status,
                &student.info.domestic.gpa,
                &student.info.international.toefl);

    // TODO: error handling for when scanned data is not right
    if(scanned_data != MIN_DOMESTIC_INFO &&
        scanned_data != MIN_INTERNATIONAL_INFO) {

        perror("Error when scanning data for student.\n");
        return get_blank_student();
    }

    // TODO: error handling for each stat

    // TODO: get ymd
    get_ymd(&student, date);
    student.is_international = is_student_international(status);

    return student;
}

// void get_ymd();

Student get_blank_student() {
    return (Student) {
        .is_international = STUDENT_ERROR_CODE,
        .info.international = (InternationalStudent) {
            .first_name = "\0",
            .last_name = "\0",
            .gpa = STUDENT_ERROR_CODE,
            .toefl = STUDENT_ERROR_CODE,
        }
    };
}

int is_student_international(const char status) {
    if (status == 'I' || status == 'i') {
        return 1;
    }

    if(status == 'D' || status == 'd') {
        return 0;
    }

    // If not I/i or D/d, then send error code.
    return STUDENT_ERROR_CODE;
}

void merge_sort(Student *students, int length) {
    // Just starts the recursion
    // This function just makes it more intuitive to use merge sort
    // since the programmer only needs to input the length of the array
    merge_sort_recursion(students, 0, length - 1);
}

void merge_sort_recursion(Student *students, int left, int right) {
    if(left < right) {
        const int mid = left + (right - left) / 2;
        merge_sort_recursion(students, left, mid);    // Recursion from beginning to middle
        merge_sort_recursion(students, mid + 1, right);    // Recursion from middle to end
        merge(students, left, mid, right);  // Merge the 2 halves after being sorted
    }
}

void merge(Student *students, int left, int mid, int right) {
    const int left_length = mid - left + 1;
    const int right_length = right - mid;

    // Temporary arrays for the left and right part
    Student temp_left_students[left_length];
    Student temp_right_students[right_length];

    for(int i = 0; i < left_length; i++)
        temp_left_students[i] = students[left + i];
    for(int j = 0; j < right_length; j++)
        temp_right_students[j] = students[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while(k <= right) {
        // Copies into left array if all elements of temp_left_students are not copied yet
        // and either all students from temp_right_students were copied
        // or if the student at the left is smaller
        if((i < left_length) &&
            (j >= right_length ||
            compare_students(&temp_left_students[i], &temp_right_students[j]) <= EQUAL)) {

            students[k] = temp_left_students[i];
            k++;
            i++;

            } else {
                students[k] = temp_right_students[j];
                k++;
                j++;

            }
    }
}

int compare_students(const Student *a, const Student *b) {
    if(a->info.domestic.year_birth != b->info.domestic.year_birth)
        return a->info.domestic.year_birth - b->info.domestic.year_birth;

    if(a->info.domestic.month_birth != b->info.domestic.month_birth)
        return a->info.domestic.month_birth - b->info.domestic.month_birth;

    if(a->info.domestic.day_birth != b->info.domestic.day_birth)
        return a->info.domestic.day_birth - b->info.domestic.day_birth;

    int cmp = strcmp(a->info.domestic.last_name, b->info.domestic.last_name);
    if(cmp != EQUAL) return cmp;

    cmp = strcmp(a->info.domestic.first_name, b->info.domestic.first_name);
    if(cmp != EQUAL) return cmp;

    if(a->info.domestic.gpa != b->info.domestic.gpa)
        return a->info.domestic.gpa - b->info.domestic.gpa;

    // Checks if they are both international or domestic.
    // If they are different, just needs to check if a is the one that is international
    // and if so, returns 1 as it should come after
    if(a->is_international != b->is_international)
        return a->is_international == 1 ? 1 : -1;

    if(!a->is_international)
        return EQUAL;

    return a->info.international.toefl - b->info.international.toefl;
}

FILE *open_input_file(const char *input_file) {
    FILE *file = fopen(input_file, "r");
    if(!file) {
        perror("Error: Could not find given input file.\n");
        exit(EXIT_FAILURE);
    }

    return file;
}

FILE *open_output_file(const char *output_file) {
    FILE *file = fopen(output_file, "w");
    if(!file) {
        perror("Error: Could not open output file.\n");
        exit(EXIT_FAILURE);
    }

    return file;
}
