#include <stdio.h>
#include <conio.h>

struct emp
{
    int empno;
    char name[10];
    int bpay, allow, ded, npay;
};

void addEmployee(struct emp e[], int *n);
void removeEmployee(struct emp e[], int *n, int empno);
void showEmployees(struct emp e[], int n);
void modifyEmployee(struct emp e[], int n, int empno);

void main()
{
    FILE *fp;
    struct emp e[100]; // Assuming maximum 100 employees
    int choice, n = 0, i;
    char filename[] = "employees.txt";

    fp = fopen(filename, "a+"); // Open file for append and read

    // Read existing data from file if any
    while (fread(&e[n], sizeof(struct emp), 1, fp) == 1)
    {
        n++;
    }

    fclose(fp);

    do
    {
        printf("\n\nMenu:\n");
        printf("1. Add a new employee\n");
        printf("2. Remove an employee\n");
        printf("3. Show all employees\n");
        printf("4. Modify employee details\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addEmployee(e, &n);
            break;
        case 2:
            {
                int empno;
                printf("Enter the employee number to remove: ");
                scanf("%d", &empno);
                removeEmployee(e, &n, empno);
            }
            break;
        case 3:
            showEmployees(e, n);
            break;
        case 4:
            {
                int empno;
                printf("Enter the employee number to modify: ");
                scanf("%d", &empno);
                modifyEmployee(e, n, empno);
            }
            break;
        case 5:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice! Please enter a number between 1 and 5.\n");
            break;
        }
    } while (choice != 5);

    // Write updated data to file
    fp = fopen(filename, "w"); // Open file for writing (truncate existing content)
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (i = 0; i < n; i++)
    {
        fwrite(&e[i], sizeof(struct emp), 1, fp);
    }

    fclose(fp);
    getch();
}

void addEmployee(struct emp e[], int *n)
{
    printf("\nEnter the employee number: ");
    scanf("%d", &e[*n].empno);
    printf("Enter the name: ");
    scanf("%s", e[*n].name);
    printf("Enter the basic pay, allowances & deductions: ");
    scanf("%d %d %d", &e[*n].bpay, &e[*n].allow, &e[*n].ded);
    e[*n].npay = e[*n].bpay + e[*n].allow - e[*n].ded;
    (*n)++;
}

void removeEmployee(struct emp e[], int *n, int empno)
{
    int i,j, found = 0;
    for (i = 0; i < *n; i++)
    {
        if (e[i].empno == empno)
        {
            // Shift remaining elements to the left
            for (j = i; j < *n - 1; j++)
            {
                e[j] = e[j + 1];
            }
            (*n)--;
            found = 1;
            printf("Employee with emp. no. %d removed successfully.\n", empno);
            break;
        }
    }
    if (!found)
    {
        printf("Employee with emp. no. %d not found.\n", empno);
    }
}

void showEmployees(struct emp e[], int n)
{
    int i;
    printf("\nEmp. No.\tName\tBpay\tAllow\tDed\tNpay\n\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t\t%s\t%d\t%d\t%d\t%d\n", e[i].empno, e[i].name, e[i].bpay, e[i].allow, e[i].ded, e[i].npay);
    }
}

void modifyEmployee(struct emp e[], int n, int empno)
{
    int i, found = 0;
    for (i = 0; i < n; i++)
    {
        if (e[i].empno == empno)
        {
            printf("Enter new basic pay, allowances & deductions: ");
            scanf("%d %d %d", &e[i].bpay, &e[i].allow, &e[i].ded);
            e[i].npay = e[i].bpay + e[i].allow - e[i].ded;
            found = 1;
            printf("Employee details modified successfully.\n");
            break;
        }
    }
    if (!found)
    {
        printf("Employee with emp. no. %d not found.\n", empno);
    }
}

