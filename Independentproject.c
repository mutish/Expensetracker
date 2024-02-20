#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define MAX_DESCRIPTION_LENGTH 100

struct Expense {
    char description[MAX_DESCRIPTION_LENGTH];
    float amount;
};

struct Expense expenses[MAX_EXPENSES];
int numExpenses = 0;

void displayMenu();
void addExpense();
void viewExpenses();
void deleteExpense();
void calculateTotal();
void saveExpenses();
void loadExpenses();

int main() {
    loadExpenses();

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                viewExpenses();
                break;
            case 3:
                deleteExpense();
                break;
            case 4:
                calculateTotal();
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void displayMenu() {
    printf("\n--- Expense Tracker Menu ---\n");
    printf("1. Add Expense\n");
    printf("2. View Expenses\n");
    printf("3. Delete Expense\n");
    printf("4. Calculate Total\n");
    printf("5. Exit\n");
}

void addExpense() {
    if (numExpenses >= MAX_EXPENSES) {
        printf("Maximum number of expenses reached.\n");
        return;
    }

    printf("\nEnter expense description: ");
    scanf(" %[^\n]s", expenses[numExpenses].description);
    printf("Enter expense amount: ");
    scanf("%f", &expenses[numExpenses].amount);

    saveExpenses();

    numExpenses++;
}

void viewExpenses() {
    if (numExpenses == 0) {
        printf("No expenses available.\n");
        return;
    }

    printf("\n--- Expenses ---\n");
    for (int i = 0; i < numExpenses; i++) {
        printf("Expense %d:\n", i + 1);
        printf("Description: %s\n", expenses[i].description);
        printf("Amount: Ksh %.2f\n", expenses[i].amount);
        printf("----------------\n");
    }
}

void deleteExpense() {
    if (numExpenses == 0) {
        printf("No expenses available to delete.\n");
        return;
    }

    int index;
    printf("Enter the index of the expense to delete: ");
    scanf("%d", &index);

    if (index < 1 || index > numExpenses) {
        printf("Invalid index.\n");
        return;
    }

    // Shift elements to the left to overwrite the deleted expense
    for (int i = index - 1; i < numExpenses - 1; i++) {
        strcpy(expenses[i].description, expenses[i + 1].description);
        expenses[i].amount = expenses[i + 1].amount;
    }

    numExpenses--;

    saveExpenses();

    printf("Expense deleted successfully.\n");
}

void calculateTotal() {
    if (numExpenses == 0) {
        printf("No expenses available.\n");
        return;
    }

    float total = 0;
    for (int i = 0; i < numExpenses; i++) {
        total += expenses[i].amount;
    }

    printf("Total expenses: Ksh %.2f\n", total);
}

void saveExpenses() {
    FILE *file = fopen("expenses.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numExpenses; i++) {
        fprintf(file, "%s %.2f\n", expenses[i].description, expenses[i].amount);
    }

    fclose(file);
    printf("Expenses saved to file successfully!\n");
}

void loadExpenses() {
    FILE *file = fopen("expenses.txt", "r");
    if (file == NULL) {
        printf("No previous expenses found.\n");
        return;
    }

    while (fscanf(file, " %[^\n] %f\n", expenses[numExpenses].description, &expenses[numExpenses].amount) != EOF) {
        numExpenses++;
    }

    fclose(file);
    printf("Expenses loaded from file.\n");
}
