//
// Created by marcu on 12/11/2024.
//
#include "student-io.h"

#ifndef STUDENT_H
#define STUDENT_H

#define INITIAL_CLASS_SIZE  30
#define MAX_LINE_SIZE       256
#define EQUAL               0

/**
 * Structure that represents a Domestic student information.
 */
struct DomesticStudent {
    char *first_name;
    char *last_name;
    float gpa;
};

/**
 * Structure that represents an International student information.
 */
struct InternationalStudent {
    char *first_name;
    char *last_name;
    float gpa;
    int toefl;
};

typedef struct DomesticStudent DomesticStudent;
typedef struct InternationalStudent InternationalStudent;

/**
 * Union used to store information of a Domestic or International student information.
 */
union StudentInfo {
    DomesticStudent domestic;
    InternationalStudent international;
};

typedef union StudentInfo StudentInfo;

/**
 * Structure used to store information about a student information.
 * The student's information is different based if they are international or not, which
 * is represented by the StudentInfo union, which you must check the variable "isInternational"
 * to be able to determine the type of the student first.
 */
struct Student {
    int is_international;
    StudentInfo info;
};

typedef struct Student Student;



int read_students(const char *input_file, Student *students);
void merge_sort(Student *students, int length);
void merge_sort_recursion(Student *students, int left, int right);
void merge(Student *students, int left, int mid, int right);
int compare_students(const Student *a, const Student *b);
void write_to_file(const char *output_file, const Student students[], int count, Filter option);

#endif //STUDENT_H
