//
// Created by marcu on 12/11/2024.
//

#ifndef STUDENT_H
#define STUDENT_H

#include "student-io.h"

#define INITIAL_CLASS_SIZE  0
#define MAX_LINE_SIZE       256
#define MAX_NAME_SIZE       50
#define EQUAL               0
#define MIN_STUDENTS_SIZE   1
#define DATE_STRING_SIZE    12
#define STUDENT_ERROR_CODE  -1
#define MIN_DOMESTIC_INFO   5
#define MIN_INTERNATIONAL_INFO   6

typedef enum Month {
    JAN = 1,
    FEB,
    MAR,
    APR,
    MAY,
    JUN,
    JUL,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC
} Month;

/**
 * Structure that represents a Domestic student information.
 */
struct DomesticStudent {
    char first_name[MAX_NAME_SIZE];
    char last_name[MAX_NAME_SIZE];
    int year_birth;
    int month_birth;
    int day_birth;
    float gpa;
};

/**
 * Structure that represents an International student information.
 */
struct InternationalStudent {
    char first_name[MAX_NAME_SIZE];
    char last_name[MAX_NAME_SIZE];
    int year_birth;
    int month_birth;
    int day_birth;
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

int read_students(const char *input_file, Student **students);
void resize_students_arr(Student **students, int new_size);
Student get_student_from_line(char *curr_line);
void get_ymd(Student *student, char date[DATE_STRING_SIZE]);
Student get_blank_student();
int is_student_international(const char status);
void merge_sort(Student *students, int length);
void merge_sort_recursion(Student *students, int left, int right);
void merge(Student *students, int left, int mid, int right);
int compare_students(const Student *a, const Student *b);
void write_to_file(const char *output_file, const Student students[], int count, Filter option);

#endif //STUDENT_H
