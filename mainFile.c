#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int no_of_records;

struct Record {
    int idx;
    char name[30];
    unsigned int amount;
    char recordType[7];
    char expenseType[6];
} record;

int getNoOfRecords(){
    FILE *fp = fopen("File_Of_Records", "r");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
        return -1;
    }
    no_of_records = 0;
    while(fread(&record, sizeof(record), 1, fp)){
        no_of_records++;
    }
    fclose(fp);
    return no_of_records;
}

void insertRecord() {
    no_of_records = getNoOfRecords();
    record.idx = no_of_records + 1;
    printf("\nEnter Name of the record: ");
    scanf("%s", record.name);
    printf("Enter the Amount: ");
    scanf("%d", &record.amount);
    printf("Enter type of the record -> Ex. INCOME / EXPENSE : ");
    scanf("%s", record.recordType);
    if(strcmp(record.recordType, "INCOME") == 0)
        strcpy(record.expenseType, "NULL");
    else if(strcmp(record.recordType, "EXPENSE") == 0){
        printf("Type of the Expense -> Ex. NEED / WANT / INVEST : ");
        scanf("%s", record.expenseType);
    } 
    else {
        printf("\nInvalid Input\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records", "a");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    fwrite(&record, sizeof(record), 1, fp);
    fclose(fp);
}

void displayRecord() {
    no_of_records = getNoOfRecords();
    if(no_of_records <= 0){
        printf("\n\nFILE IS EMPTY\n\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records", "r");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    printf("PERSONAL FINANCE MANAGEMENT");
    printf("\n\nIDX\t Name\t Amount\t RType\t EType\n\n");
    while(fread(&record, sizeof(record), 1, fp)){
        printf("%d\t %s\t %d\t %s\t %s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose((fp));
}

void modifyRecord() {
    // Add code to modify a record
}

void deleteRecord() {
    // Add code to delete a record
}

void sortRecordsByAmount() {
    // Add code to sort records by amount
}

void displayIncomeSources() {
    // Add code to display income sources
}

void displayExpenses() {
    // Add code to display expenses
}

void calculateLoanInterest() {
    // Add code to calculate loan interest
}

void printMenu() {
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
    printf(ANSI_COLOR_RED "1. Insert record\n" ANSI_COLOR_RESET);
    printf("2. Display record \n");
    printf("3. Modify record \n");
    printf("4. Delete record \n");
    printf("5. Sort data based on the amount\n");
    printf("6. Display Income sources \n");
    printf("7. Display expenses \n");
    printf("8. Calculate interest of loan \n");
    printf("9. Exit \n");
    printf("\n\n                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
}

int main() {
    int choice;
    printMenu();
    do {
        printMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertRecord();
                break;
            case 2:
                displayRecord();
                break;
            case 3:
                modifyRecord();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                sortRecordsByAmount();
                break;
            case 6:
                displayIncomeSources();
                break;
            case 7:
                displayExpenses();
                break;
            case 8:
                calculateLoanInterest();
                break;
            case 9:
                printf("\n\nPROGRAM IS TEMINATED\n\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 9);

    return 0;
}
