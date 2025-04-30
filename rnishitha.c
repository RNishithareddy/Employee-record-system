#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Employee {
    int id;
    char name[50];
    float salary;
    struct Employee* next;
} Employee;

Employee* head = NULL;

// Function to create a new employee node
Employee* createEmployee(int id, const char* name, float salary) {
    Employee* newEmp = (Employee*)malloc(sizeof(Employee));
    newEmp->id = id;
    strcpy(newEmp->name, name);
    newEmp->salary = salary;
    newEmp->next = NULL;
    return newEmp;
}

// Add employee to the linked list
void addEmployee(int id, const char* name, float salary) {
    Employee* newEmp = createEmployee(id, name, salary);
    newEmp->next = head;
    head = newEmp;
}

// Display all employee records
void displayEmployees() {
    Employee* temp = head;
    if (temp == NULL) {
        printf("No records found.\n");
        return;
    }
    printf("Employee Records:\n");
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", temp->id, temp->name, temp->salary);
        temp = temp->next;
    }
}

// Save all employee records to a file
void saveToFile(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Unable to open file.\n");
        return;
    }
    Employee* temp = head;
    while (temp != NULL) {
        fprintf(fp, "%d,%s,%.2f\n", temp->id, temp->name, temp->salary);
        temp = temp->next;
    }
    fclose(fp);
    printf("Data saved to file.\n");
}

// Load employee records from a file
void loadFromFile(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("No previous records found.\n");
        return;
    }

    int id;
    char name[50];
    float salary;

    while (fscanf(fp, "%d,%49[^,],%f\n", &id, name, &salary) == 3) {
        addEmployee(id, name, salary);
    }

    fclose(fp);
    printf("Data loaded from file.\n");
}

int main() {
    int choice, id;
    char name[50];
    float salary;

    loadFromFile("employees.txt");

    while (1) {
        printf("\nEmployee Record System\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Save to File\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // consume newline

        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                getchar(); // consume newline
                printf("Enter Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;  // remove newline
                printf("Enter Salary: ");
                scanf("%f", &salary);
                addEmployee(id, name, salary);
                break;

            case 2:
                displayEmployees();
                break;

            case 3:
                saveToFile("employees.txt");
                break;

            case 4:
                saveToFile("employees.txt");
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}