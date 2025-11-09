// Student Attendance Register
// Developed by Vyshnavi Denuvukonda
// Description: A file-handling based attendance system in C


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int classesHeld;
    int classesAttended;
    float percentage;
};

#define FILENAME "students.txt"

// Function to calculate percentage
float calcPercentage(int attended, int held) {
    if (held == 0)
        return 0;
    return (attended * 100.0) / held;
}

// Load students from file
int loadStudents(struct Student s[]) {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL)
        return 0;

    int count = 0;
    while (fscanf(fp, "%d %s %d %d %f",
                  &s[count].id, s[count].name,
                  &s[count].classesHeld,
                  &s[count].classesAttended,
                  &s[count].percentage) == 5) {
        count++;
    }
    fclose(fp);
    return count;
}

// Save students to file
void saveStudents(struct Student s[], int n) {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %s %d %d %.2f\n",
                s[i].id, s[i].name,
                s[i].classesHeld,
                s[i].classesAttended,
                s[i].percentage);
    }
    fclose(fp);
}

// Display all students
void showAll(struct Student s[], int n) {
    if (n == 0) {
        printf("\n  No student records found.\n");
        return;
    }

    printf("\n--------------------------------------------------------------\n");
    printf("%-5s %-15s %-15s %-18s %-12s\n", "ID", "NAME", "CLASSES_HELD", "CLASSES_ATTENDED", "PERCENTAGE");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-5d %-15s %-15d %-18d %.2f%%\n",
               s[i].id, s[i].name, s[i].classesHeld, s[i].classesAttended, s[i].percentage);
    }
    printf("--------------------------------------------------------------\n");
}

// Add new student
void addStudent(struct Student s[], int *n) {
    printf("\nEnter ID: ");
    scanf("%d", &s[*n].id);
    printf("Enter Name: ");
    scanf("%s", s[*n].name);
    printf("Enter Classes Held: ");
    scanf("%d", &s[*n].classesHeld);
    printf("Enter Classes Attended: ");
    scanf("%d", &s[*n].classesAttended);

    s[*n].percentage = calcPercentage(s[*n].classesAttended, s[*n].classesHeld);
    (*n)++;

    saveStudents(s, *n);
    printf(" Student added successfully and saved to file!\n");
    showAll(s, *n);
}

// Remove student
void removeStudent(struct Student s[], int *n) {
    int id, found = 0;
    printf("\nEnter ID to remove: ");
    scanf("%d", &id);

    for (int i = 0; i < *n; i++) {
        if (s[i].id == id) {
            for (int j = i; j < *n - 1; j++)
                s[j] = s[j + 1];
            (*n)--;
            found = 1;
            break;
        }
    }

    if (found) {
        saveStudents(s, *n);
        printf(" Student removed and file updated!\n");
    } else {
        printf(" Student not found!\n");
    }

    showAll(s, *n);
}

// Search student by ID
void searchStudent(struct Student s[], int n) {
    int id, found = 0;
    printf("\nEnter ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < n; i++) {
        if (s[i].id == id) {
            printf("\nRecord Found:\n");
            printf("ID: %d\nName: %s\nClasses Held: %d\nClasses Attended: %d\nPercentage: %.2f%%\n",
                   s[i].id, s[i].name, s[i].classesHeld, s[i].classesAttended, s[i].percentage);
            found = 1;
            break;
        }
    }
    if (!found)
        printf(" Student not found!\n");
}

// Recalculate all percentages
void calculatePercentage(struct Student s[], int n) {
    for (int i = 0; i < n; i++)
        s[i].percentage = calcPercentage(s[i].classesAttended, s[i].classesHeld);

    saveStudents(s, n);
    printf(" Percentages recalculated and saved!\n");
    showAll(s, n);
}

int main() {
    struct Student s[100];
    int n = 0;
    int choice;

    printf("\n STUDENT ATTENDANCE REGISTER (File Version) \n");

    n = loadStudents(s);
    printf("Loaded %d student(s) from file.\n", n);

    while (1) {
        printf("\n-------------------------------------------\n");
        printf("1. Add Student\n");
        printf("2. Remove Student\n");
        printf("3. Search Student\n");
        printf("4. Show All Students\n");
        printf("5. Calculate Percentages\n");
        printf("6. Exit\n");
        printf("-------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(s, &n);
                break;
            case 2:
                removeStudent(s, &n);
                break;
            case 3:
                searchStudent(s, n);
                break;
            case 4:
                showAll(s, n);
                break;
            case 5:
                calculatePercentage(s, n);
                break;
            case 6:
                printf(" Exiting... All data saved to file '%s'.\n", FILENAME);
                exit(0);
            default:
                printf(" Invalid choice! Try again.\n");
        }
    }

    return 0;
}
