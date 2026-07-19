#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student_registry.h"

Student students[MAX_STUDENTS];
int count = 0;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addStudent()
{
    if(count == MAX_STUDENTS)
    {
        printf("Error: Cannot add more, list is full.\n");
        return;
    }
    
    int temp_id;
    printf("Enter ID: ");
    if (scanf("%d", &temp_id) != 1) {
        printf("Invalid input. ID must be a number.\n");
        clearBuffer();
        return;
    }
    
    for (int i = 0; i < count; i++) {
        if (students[i].id == temp_id) {
            printf("Error: A student with ID %d already exists.\n", temp_id);
            return;
        }
    }
    students[count].id = temp_id;

    printf("Enter Name: ");
    scanf(" %99[^\n]", students[count].name);
    
    printf("Enter Major: ");
    scanf(" %49[^\n]", students[count].major);
    
    printf("Enter GPA: ");
    if (scanf("%f", &students[count].gpa) != 1) {
        printf("Invalid input. GPA must be a number.\n");
        clearBuffer();
        return;
    }
    
    printf("Enter Credits: ");
    if (scanf("%d", &students[count].credits) != 1) {
        printf("Invalid input. Credits must be a number.\n");
        clearBuffer();
        return;
    }
    
    count++;
    printf("Student added successfully!\n");
}

void displayAllStudents()
{
    if(count == 0)
    {
        printf("No students yet.\n");
        return;
    }
    for(int i = 0; i < count; i++)
    {
        printf("ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Major: %s\n", students[i].major);
        printf("GPA: %.2f\n", students[i].gpa);
        printf("Credits: %d\n", students[i].credits);
        printf("------------------\n");
    }
}

void searchByID()
{
    int x, found = 0;
    printf("Enter ID to find: ");
    if (scanf("%d", &x) != 1) {
        printf("Invalid input.\n");
        clearBuffer();
        return;
    }
    
    for(int i = 0; i < count; i++)
    {
        if(students[i].id == x)
        {
            printf("Found it!\n");
            printf("Name: %s\n", students[i].name);
            printf("Major: %s\n", students[i].major);
            printf("GPA: %.2f\n", students[i].gpa);
            printf("Credits: %d\n", students[i].credits);
            found = 1;
            break; 
        }
    }
    if(found == 0)
        printf("No student with that ID.\n");
}

void findByGPA()
{
    float t;
    int found = 0;
    printf("Enter min GPA: ");
    if (scanf("%f", &t) != 1) {
        printf("Invalid input.\n");
        clearBuffer();
        return;
    }
    
    for(int i = 0; i < count; i++)
    {
        if(students[i].gpa >= t)
        {
            printf("%d | %s | %s | %.2f | %d\n", students[i].id, students[i].name, students[i].major, students[i].gpa, students[i].credits);
            found = 1;
        }
    }
    if(found == 0)
        printf("Nobody has that GPA or higher.\n");
}

void findByMajor()
{
    char m[50];
    int total = 0;
    printf("Enter major: ");
    scanf(" %49[^\n]", m); 
    
    for(int i = 0; i < count; i++)
    {
        if(strcmp(students[i].major, m) == 0) 
        {
            printf("%d | %s | %s | %.2f | %d\n", students[i].id, students[i].name, students[i].major, students[i].gpa, students[i].credits);
            total++;
        }
    }
    printf("Total students in this major = %d\n", total);
}

void saveStudentsToFile()
{
    FILE *file = fopen(DATA_FILE, "w");
    if(file == NULL)
    {
        printf("Error: Cannot open file for writing.\n");
        return;
    }
    for(int i = 0; i < count; i++)
    {
        fprintf(file, "%d|%s|%s|%.2f|%d\n", students[i].id, students[i].name, students[i].major, students[i].gpa, students[i].credits);
    }
    fclose(file);
    printf("Saved %d students to file.\n", count);
}

void loadStudentsFromFile()
{
    FILE *file = fopen(DATA_FILE, "r");
    char buffer[300];
    char *token;
    
    if(file == NULL)
    {
        printf("No data file yet, starting fresh.\n");
        return;
    }
    
    count = 0;
    while(fgets(buffer, sizeof(buffer), file) != NULL && count < MAX_STUDENTS)
    {
        token = strtok(buffer, "|");
        if (token == NULL) continue; 
        students[count].id = atoi(token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(students[count].name, token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy(students[count].major, token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        students[count].gpa = atof(token);

        token = strtok(NULL, "|\n");
        if (token == NULL) continue;
        students[count].credits = atoi(token);

        count++;
    }
    fclose(file);
    printf("Loaded %d students from file.\n", count);
}
