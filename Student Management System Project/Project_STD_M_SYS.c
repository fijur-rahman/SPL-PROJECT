#include <stdio.h>
#include <string.h>

#define MAX 100

const char *departments[] = 
{
    "CSE", "EEE", "ECE", "BBA", "CIVIL", "PHARMACY", "Mechanical Engineer", "Aeronautical Engineer"
};
const int deptCount = 8;

struct Student {
    char name[50];
    char id[20];
    float cgpa;
    char department[10];
    int trimester;
};

struct Student students[MAX];
int count = 0;

void loadFromFile();
void saveToFile();
void addStudent();
void searchStudent();
void findTopStudent();
void findAverageCGPA();
void displayStudents();
void editStudent();
void deleteStudent();

int main() 
{
    int choice;
    loadFromFile();

    while (1) 
    {
        printf("\n====== Student Management System ======\n");
        printf("1. Add New Student\n");
        printf("2. Search Student by ID\n");
        printf("3. Find Top Student (Highest CGPA)\n");
        printf("4. Find Average CGPA\n");
        printf("5. Display Students (by Department or ALL)\n");
        printf("6. Edit Student by ID\n");
        printf("7. Delete Student by ID\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) 
        {
            case 1: 
                addStudent(); 
                break;
            case 2: 
                searchStudent(); 
                break;
            case 3: 
                findTopStudent(); 
                break;
            case 4: 
                findAverageCGPA(); 
                break;
            case 5: 
                displayStudents(); 
                break;
            case 6: 
                editStudent(); 
                break;
            case 7: 
                deleteStudent(); 
                break;
            case 8:
                saveToFile();
                printf("Exiting program. Thank you!\n");
                return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

void loadFromFile() 
{
    FILE *fp = fopen("E:\\Project\\file\\Student.txt", "r");
    if (fp == NULL) return;

    while (!feof(fp)) 
    {
        if (fscanf(fp, "Student Name: %[^\n]\n", students[count].name) != 1) break;
        if (fscanf(fp, "ID: %[^\n]\n", students[count].id) != 1) break;
        if (fscanf(fp, "CGPA: %f\n", &students[count].cgpa) != 1) break;
        if (fscanf(fp, "Department: %[^\n]\n", students[count].department) != 1) break;
        if (fscanf(fp, "Trimester: %d\n", &students[count].trimester) != 1) break;

        count++;
    }

    fclose(fp);
}

void saveToFile() 
{
    FILE *fp = fopen("E:\\Project\\file\\Student.txt", "a");
    for (int i = 0; i < count; i++) 
    {
        fprintf(fp, "Student Name: %s\nID: %s\nCGPA: %.2f\nDepartment: %s\nTrimester: %d\n",
                students[i].name, students[i].id,
                students[i].cgpa, students[i].department,
                students[i].trimester);
    }
    fclose(fp);
}

void addStudent() 
{
    if (count >= MAX) 
    {
        printf("All sit fill up. Please try next trimester\n");
        return;
    }

    printf("Enter Name: ");
    fgets(students[count].name, sizeof(students[count].name), stdin);
    students[count].name[strcspn(students[count].name, "\n")] = 0;

    printf("Enter ID: ");
    fgets(students[count].id, sizeof(students[count].id), stdin);
    students[count].id[strcspn(students[count].id, "\n")] = 0;

    printf("Enter CGPA: ");
    scanf("%f", &students[count].cgpa);
    getchar();

    printf("Select Department:\n");
    for (int i = 0; i < deptCount; i++)
        {
            printf("%d. %s\n", i + 1, departments[i]);
        }
    int deptChoice;
    do
    {
    printf("Enter choice (1-%d): ", deptCount);
    scanf("%d", &deptChoice);
    getchar();
    } while (deptChoice < 1 || deptChoice > deptCount);

    strcpy(students[count].department, departments[deptChoice - 1]);

    printf("Enter Trimester: ");
    scanf("%d", &students[count].trimester);
    getchar();

    count++;
    saveToFile();
    printf("Student added Successfully!\n");
}

void searchStudent() 
{
    char searchID[20];
    printf("Enter ID: ");
    fgets(searchID, sizeof(searchID), stdin);
    searchID[strcspn(searchID, "\n")] = 0;

    for (int i = 0; i < count; i++) 
    {
        if (strcmp(students[i].id, searchID) == 0) 
        {
            printf("Name: %s\nID: %s\nCGPA: %.2f\nDept: %s\nTrimester: %d\n",
                   students[i].name, students[i].id, students[i].cgpa,
                   students[i].department, students[i].trimester);
            return;
        }
    }

    printf("Student not found.\n");
}

void findTopStudent() 
{
    if (count == 0) 
    {
        printf("No students available.\n");
        return;
    }

    int top = 0;
    for (int i = 1; i < count; i++) 
    {
        if (students[i].cgpa > students[top].cgpa)
            top = i;
    }

    printf("Top Student:\nName: %s\nID: %s\nCGPA: %.2f\nDept: %s\nTrimester: %d\n",
           students[top].name, students[top].id, students[top].cgpa,
           students[top].department, students[top].trimester);
}

void findAverageCGPA() 
{
    if (count == 0) 
    {
        printf("No data.\n");
        return;
    }

    float total = 0;
    for (int i = 0; i < count; i++)
        total += students[i].cgpa;

    printf("Total Students: %d\nAverage CGPA: %.2f\n", count, total / count);
}

void displayStudents() 
{
    char dept[10];
    printf("Select Department to show:\n");
    for (int i = 0; i < deptCount; i++) 
    {
    printf("%d. %s\n", i + 1, departments[i]);
    }
    printf("%d. ALL\n", deptCount + 1);
    int deptChoice;
    do 
    {
    printf("Enter choice (1-%d): ", deptCount + 1);
    scanf("%d", &deptChoice);
    getchar();
    } while (deptChoice < 1 || deptChoice > deptCount + 1);

    const char *selectedDept = NULL;
    if (deptChoice != deptCount + 1)
    selectedDept = departments[deptChoice - 1];

    int found = 0;
    for (int i = 0; i < count; i++) 
    {
        if (selectedDept == NULL || strcmp(students[i].department, selectedDept) == 0) 
        {
        printf("\nName: %s\nID: %s\nCGPA: %.2f\nDept: %s\nTrimester: %d\n",
               students[i].name, students[i].id, students[i].cgpa,
               students[i].department, students[i].trimester);
        found = 1;
        }
    }

    if (!found) 
        printf("No students found.\n");

}

void editStudent() 
{
    char id[20];
    printf("Enter ID to edit: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    for (int i = 0; i < count; i++) 
    {
        if (strcmp(students[i].id, id) == 0) 
        {
            printf("Editing Student: %s\n", students[i].name);

            printf("Enter new Name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = 0;

            printf("Enter new CGPA: ");
            scanf("%f", &students[i].cgpa);
            getchar();

            printf("Select new Department:\n");
            for (int i = 0; i < deptCount; i++) 
            {
            printf("%d. %s\n", i + 1, departments[i]);
            }
            int deptChoice;
            do {
            printf("Enter choice (1-%d): ", deptCount);
            scanf("%d", &deptChoice);
            getchar();
            } while (deptChoice < 1 || deptChoice > deptCount);

            strcpy(students[i].department, departments[deptChoice - 1]);


            printf("Enter new Trimester: ");
            scanf("%d", &students[i].trimester);
            getchar();

            saveToFile();
            printf("Student updated.\n");
            return;
        }
    }

    printf("ID not found.\n");
}

void deleteStudent() 
{
    char id[20];
    printf("Enter ID to delete: ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;

    for (int i = 0; i < count; i++) 
    {
        if (strcmp(students[i].id, id) == 0) 
        {
            for (int j = i; j < count - 1; j++)
                students[j] = students[j + 1];

            count--;
            saveToFile();
            printf("Student deleted.\n");
            return;
        }
    }

    printf("ID not found.\n");
}
