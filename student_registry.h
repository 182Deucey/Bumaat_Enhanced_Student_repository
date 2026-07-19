#ifndef STUDENT_REGISTRY_H
#define STUDENT_REGISTRY_H

#define MAX_STUDENTS 10
#define DATA_FILE "students.dat"

typedef struct {
    int id;
    char name[100];
    char major[50];
    float gpa;
    int credits;
} Student;

extern Student students[MAX_STUDENTS];
extern int count;

void addStudent();
void displayAllStudents();
void searchByID();
void findByGPA();
void findByMajor();
void saveStudentsToFile();
void loadStudentsFromFile();

#endif
