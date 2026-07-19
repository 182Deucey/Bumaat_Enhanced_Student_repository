#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student_registry.h"

Student students[MAX_STUDENTS];
int count = 0;

int checkSame(char a[], char b[])
{
    int i = 0;
    while(a[i] != '\0' && b[i] != '\0')
    {
        if(a[i] != b[i])
        return 0;
        i++;
    }
    if(a[i] == '\0' && b[i] == '\0')
    return 1;
    else
    return 0;
}

void addStudent()
{
    if(count == MAX_STUDENTS)
    {
        printf("cant add more, list is full\n");
        return;
    }
    printf("Enter ID: ");
    scanf("%d", &students[count].id);
    printf("Enter Name: ");
    scanf("%s", students[count].name);
    printf("Enter Major: ");
    scanf("%s", students[count].major);
    printf("Enter GPA: ");
    scanf("%f", &students[count].gpa);
    printf("Enter Credits: ");
    scanf("%d", &students[count].credits);
    count = count + 1;
    printf("student added!\n");
}

void displayAllStudents()
{
    int i;
    if(count == 0)
    {
        printf("no students yet\n");
        return;
    }
    for(i = 0; i < count; i++)
    {
        printf("ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Major: %s\n", students[i].major);
        printf("GPA: %f\n", students[i].gpa);
        printf("Credits: %d\n", students[i].credits);
        printf("------------------\n");
    }
}

void searchByID()
{
    int x, i, found;
    found = 0;
    printf("Enter ID to find: ");
    scanf("%d", &x);
    for(i = 0; i < count; i++)
    {
        if(students[i].id == x)
        {
            printf("Found it!\n");
            printf("Name: %s\n", students[i].name);
            printf("Major: %s\n", students[i].major);
            printf("GPA: %f\n", students[i].gpa);
            printf("Credits: %d\n", students[i].credits);
            found = 1;
        }
    }
    if(found == 0)
    printf("no student with that id\n");
}

void findByGPA()
{
    float t;
    int i;
    int found = 0;
    printf("Enter min GPA: ");
    scanf("%f", &t);
    for(i = 0; i < count; i++)
    {
        if(students[i].gpa >= t)
        {
            printf("%d %s %s %f %d\n", students[i].id, students[i].name, students[i].major, students[i].gpa, students[i].credits);
            found = 1;
        }
    }
    if(found == 0)
    printf("nobody has that gpa\n");
}

void findByMajor()
{
    char m[50];
    int i;
    int total = 0;
    printf("Enter major: ");
    scanf("%s", m);
    for(i = 0; i < count; i++)
    {
        if(checkSame(students[i].major, m) == 1)
        {
            printf("%d %s %s %f %d\n", students[i].id, students[i].name, students[i].major, students[i].gpa, students[i].credits);
            total++;
        }
    }
    printf("total students in this major = %d\n", total);
}

void saveStudentsToFile()
{
    FILE *file = fopen(DATA_FILE, "w");
    int i;
    if(file == NULL)
    {
        printf("Error: Cannot open file\n");
        return;
    }
    for(i = 0; i < count; i++)
    {
        fprintf(file, "%d|%s|%s|%.2f|%d\n", students[i].id, students[i].name, students[i].major, students[i].gpa, students[i].credits);
    }
    fclose(file);
    printf("saved %d students to file\n", count);
}

void loadStudentsFromFile()
{
    FILE *file = fopen(DATA_FILE, "r");
    char buffer[300];
    char *token;
    if(file == NULL)
    {
        printf("no data file yet, starting fresh\n");
        return;
    }
    count = 0;
    while(fgets(buffer, 300, file) != NULL && count < MAX_STUDENTS)
    {
        token = strtok(buffer, "|");
        students[count].id = atoi(token);

        token = strtok(NULL, "|");
        strcpy(students[count].name, token);

        token = strtok(NULL, "|");
        strcpy(students[count].major, token);

        token = strtok(NULL, "|");
        students[count].gpa = atof(token);

        token = strtok(NULL, "|\n");
        students[count].credits = atoi(token);

        count++;
    }
    fclose(file);
    printf("loaded %d students from file\n", count);
}
