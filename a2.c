#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ARGS            4
#define INITIAL_CLASS_SIZE  30
#define MAX_LINE_SIZE       256
#define EQUAL               0

enum Args {
    ARG_PROGRAM_NAME,
    ARG_INPUT_FILE,
    ARG_OUTPUT_FILE,
    ARG_OPTION
};
typedef enum Args Args;

typedef enum Filter {
    FILTER_DOMESTIC,
    FILTER_INTERNATIONAL,
    FILTER_ALL
} Filter;
typedef enum Filter Filter;

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

void filter_students(char *input_file, char *output_file, const int option);
int read_students(const char *input_file, Student *students);
void merge_sort(Student *students, int length);
void merge_sort_recursion(Student *students, int left, int right);
void merge(Student *students, int left, int mid, int right);
int compare_students(const Student *a, const Student *b);
void write_to_file(const char *output_file, const Student students[], int count, int option);

FILE* open_input_file(const char *input_file);
FILE* open_output_file(const char *output_file);
int get_filter_option(const char *filter_arg);

int main(int argc, char **argv) {
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

void filter_students(char *input_file, char *output_file, const int option) {
    Student *students;
    const int student_count = read_students(input_file, students);

    if(student_count == 0) {
        printf("No students found in the input file.\n");
        return;
    }

    merge_sort(students, student_count);
    write_to_file(output_file, students, student_count, option);
}

int read_students(const char *input_file, Student *students) {
    FILE *file = open_input_file(input_file);
    int student_count = INITIAL_CLASS_SIZE;
    char currLine[MAX_LINE_SIZE];

    // TODO: read students with realloc
    while(fgets(currLine, MAX_LINE_SIZE, input_file)) {
        // const Student currStudent = getStudentFromLine(currLine);
        // appendStudentTo(currStudent, ptrOut, option);
        student_count++;
    }

    return student_count;
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
    // TODO: check for year-month-day order first

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

int get_filter_option(const char *filter_arg) {
    char *error;
    int filter_option = strtod(filter_arg, &error);

    // If there was any error, sets the filter_option as FILTER_ALL
    if(((*error != '\n') && (*error != '\0' || error == filter_arg)) ||
        (filter_option < FILTER_DOMESTIC + 1 || filter_option > FILTER_ALL + 1 )) {

        perror("Invalid filter option. Using default filter as all students.\n");
        return FILTER_ALL + 1;
        }

    return --filter_option;
}