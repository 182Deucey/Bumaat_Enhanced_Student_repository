#include <stdio.h>
#include "student_registry.h"

int main()
{
    int choice;

    loadStudentsFromFile();

    while(1)
    {
        printf("\n1 - add student\n");
        printf("2 - show all students\n");
        printf("3 - find by id\n");
        printf("4 - find by gpa\n");
        printf("5 - find by major\n");
        printf("6 - save and quit\n");
        printf("choice: ");
        scanf("%d", &choice);
        if(choice == 1)
        addStudent();
        else if(choice == 2)
        displayAllStudents();
        else if(choice == 3)
        searchByID();
        else if(choice == 4)
        findByGPA();
        else if(choice == 5)
        findByMajor();
        else if(choice == 6)
        {
            saveStudentsToFile();
            printf("bye!\n");
            break;
        }
        else
        printf("invalid choice try again\n");
    }
    return 0;
}
