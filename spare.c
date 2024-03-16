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

void printMenu() {
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
    printf(ANSI_COLOR_RED "1. Insert record\n" ANSI_COLOR_RESET);
    printf("2. Display record \n");
    printf("3. Search record by name\n");
    printf("4. Modify record \n");
    printf("5. Delete record \n");
    printf("6. Sort data based on the amount\n");
    printf("7. Display Income sources \n");
    printf("8. Display expenses \n");
    printf("9. Calculate interest of loan \n");
    printf("10. Exit \n");
    printf("\n\n                ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n");
}

int getNoOfRecords(){
    FILE *fp = fopen("File_Of_Records", "rb");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
        return -1;
    }
    fseek(fp, 0, SEEK_END);
    no_of_records = ftell(fp) / sizeof(record);
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
    FILE *fp = fopen("File_Of_Records", "ab");
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
    FILE *fp = fopen("File_Of_Records", "rb");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    printf("PERSONAL FINANCE MANAGEMENT");
    printf("\n\nIDX\t Name\t Amount\t RType\t\t EType\n\n");
    while(fread(&record, sizeof(record), 1, fp)){
        printf("%d\t %s\t %d\t %s\t\t %s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose((fp));
}

void searchByName(char *nameToFind){
    // Add code to search record by name
}

void modifyRecord(int index) {
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
                printf("\n\nEnter record name you want to find: ");
                char str[30];
                scanf("%s", str);
                searchByName(str);
                break;
            case 4:
                printf("\n\nEnter index number of the record you want to modify: ");
                int index;
                scanf("%d", &index);
                modifyRecord(index);
                break;
            case 5:
                deleteRecord();
                break;
            case 6:
                sortRecordsByAmount();
                break;
            case 7:
                displayIncomeSources();
                break;
            case 8:
                displayExpenses();
                break;
            case 9:
                calculateLoanInterest();
                break;
            case 10:
                printf("\n\nPROGRAM IS TEMINATED\n\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 9);

    return 0;
}
