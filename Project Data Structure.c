#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a bank account
typedef struct BankAccount {
    int accountNumber;
    char name[50];
    float balance;
    struct BankAccount* next; // Pointer for linked list
} BankAccount;

// Head pointer for the linked list
BankAccount* head = NULL;

// Function prototypes
void createAccount();
void displayAccount();
void depositMoney();
void withdrawMoney();
void closeAccount();
void menu();

// Main function
int main() {
    while (1) {
        menu();
    }
    return 0;
}

// Function to display the menu
void menu() {
    int choice;
    printf("\n=== Bank Management System ===\n");
    printf("1. Create Account\n");
    printf("2. View Account Details\n");
    printf("3. Deposit Money\n");
    printf("4. Withdraw Money\n");
    printf("5. Close Account\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            displayAccount();
            break;
        case 3:
            depositMoney();
            break;
        case 4:
            withdrawMoney();
            break;
        case 5:
            closeAccount();
            break;
        case 6:
            printf("Exiting... Thank you for using the system!\n");
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
    }
}

// Function to create a new account
void createAccount() {
    BankAccount* newAccount = (BankAccount*)malloc(sizeof(BankAccount));
    if (newAccount == NULL) {
        printf("Memory allocation failed! Cannot create a new account.\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &newAccount->accountNumber);
    printf("Enter account holder name: ");
    getchar(); // To consume newline left by scanf
    fgets(newAccount->name, sizeof(newAccount->name), stdin);
    newAccount->name[strcspn(newAccount->name, "\n")] = 0; // Remove newline character
    printf("Enter initial deposit: ");
    scanf("%f", &newAccount->balance);
    newAccount->next = head; // Insert at the beginning of the list
    head = newAccount;

    printf("Account created successfully!\n");
}

// Function to display account details
void displayAccount() {
    int accountNumber, found = 0;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    BankAccount* temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accountNumber) {
            printf("\nAccount Details:\n");
            printf("Account Number: %d\n", temp->accountNumber);
            printf("Account Holder: %s\n", temp->name);
            printf("Account Balance: %.2f\n", temp->balance);
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Account not found!\n");
    }
}

// Function to deposit money
void depositMoney() {
    int accountNumber, found = 0;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    BankAccount* temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accountNumber) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            if (amount > 0) {
                temp->balance += amount;
                printf("Deposit successful! New balance: %.2f\n", temp->balance);
            } else {
                printf("Invalid amount!\n");
            }
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Account not found!\n");
    }
}

// Function to withdraw money
void withdrawMoney() {
    int accountNumber, found = 0;
    float amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    BankAccount* temp = head;
    while (temp != NULL) {
        if (temp->accountNumber == accountNumber) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount > 0 && temp->balance >= amount) {
                temp->balance -= amount;
                printf("Withdrawal successful! New balance: %.2f\n", temp->balance);
            } else {
                printf("Insufficient balance or invalid amount!\n");
            }
            found = 1;
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        printf("Account not found!\n");
    }
}

// Function to close an account
void closeAccount() {
    int accountNumber, found = 0;
    printf("Enter account number to close: ");
    scanf("%d", &accountNumber);

    BankAccount *temp = head, *prev = NULL;

    while (temp != NULL) {
        if (temp->accountNumber == accountNumber) {
            if (prev == NULL) {
                head = temp->next; // Remove head node
            } else {
                prev->next = temp->next; // Remove middle or last node
            }
            free(temp);
            printf("Account closed successfully!\n");
            found = 1;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    if (!found) {
        printf("Account not found!\n");
    }
}

