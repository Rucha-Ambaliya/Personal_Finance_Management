#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int no_of_records;

struct Record {
    int idx;
    char name[20];
    int amount;
    char recordType[8];
    char expenseType[8];
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
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
        return -1;
    }
    no_of_records = 0;
    while (fscanf(fp, "%d\t%s\t%d\t%s\t%s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) == 5) {
        no_of_records++;
    }
    fclose(fp);
    return no_of_records;
}


void insertRecord() {
    FILE *fp = fopen("File_Of_Records.txt", "a");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
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
    fprintf(fp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    fclose(fp);
}

void displayRecord() {
    no_of_records = getNoOfRecords();
    if(no_of_records <= 0){
        printf("\n\nFILE IS EMPTY\n\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    printf("\n\nPERSONAL FINANCE MANAGEMENT");
    printf("\n\n%-4s %-20s %-8s %-10s %-10s\n", "IDX", "Record Name", "Amount", "RType", "EType");
    while(fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        printf("%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose((fp));
}

void searchByName(char *nameToFind){
    no_of_records = getNoOfRecords();
    int similarRecord = 0;
    if(no_of_records <= 0){
        printf("\n\nFILE IS EMPTY\n\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    printf("\n\nPERSONAL FINANCE MANAGEMENT\n\n");
    printf("%-4s %-20s %-8s %-10s %-10s\n", "IDX", "Record Name", "Amount", "RType", "EType");
    while(fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        if(strcmp(record.name, nameToFind) == 0){
            printf("%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
            similarRecord++;
        }
    }
    if (similarRecord == 0)
        printf("\n\nNo such record exist in the file\n");
    else 
        printf("\n\n%d records matched\n", similarRecord);
    
    fclose((fp));
}

void modifyName(int index){
    no_of_records = getNoOfRecords();
    if (index > no_of_records)
    {
        printf("\n\nIndex is out of bound\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records.txt", "r");
    FILE *tp = fopen("temp.txt", "w");
    if(fp == NULL || tp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    for(int i = 1; i < index; i++){
        fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    
    fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
    printf("\nEnter Name of the record: ");
    scanf("%s", record.name);
    fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", index, record.name, record.amount, record.recordType, record.expenseType);
    
    while(fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose(fp);
    fclose(tp);
    fp = fopen("File_Of_Records.txt", "w");
    tp = fopen("temp.txt", "r");
    if(fp == NULL || tp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    while(fscanf(tp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        fprintf(fp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose(fp);
    fclose(tp);
}

void modifyAmount(int index){
    no_of_records = getNoOfRecords();
    if (index > no_of_records)
    {
        printf("\n\nIndex is out of bound\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records.txt", "r");
    FILE *tp = fopen("temp.txt", "w");
    if(fp == NULL || tp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    for(int i = 1; i < index; i++){
        fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    
    fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
    printf("Enter the Amount: ");
    scanf("%d", &record.amount);
    fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", index, record.name, record.amount, record.recordType, record.expenseType);
    
    while(fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose(fp);
    fclose(tp);
    fp = fopen("File_Of_Records.txt", "w");
    tp = fopen("temp.txt", "r");
    if(fp == NULL || tp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    while(fscanf(tp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        fprintf(fp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose(fp);
    fclose(tp);
}

void modifyRtype(int index){
    no_of_records = getNoOfRecords();
    if (index > no_of_records)
    {
        printf("\n\nIndex is out of bound\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records.txt", "r");
    FILE *tp = fopen("temp.txt", "w");
    if(fp == NULL || tp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    for(int i = 1; i < index; i++){
        fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    
    fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
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
    fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", index, record.name, record.amount, record.recordType, record.expenseType);
    
    while(fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose(fp);
    fclose(tp);
    fp = fopen("File_Of_Records.txt", "w");
    tp = fopen("temp.txt", "r");
    if(fp == NULL || tp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    while(fscanf(tp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        fprintf(fp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose(fp);
    fclose(tp);
}

void modifyRecord(int index) {
    no_of_records = getNoOfRecords();
    if (index > no_of_records)
    {
        printf("\n\nIndex is out of bound\n");
        return;
    }
    
    int choice;
    printf("\n\n1. Update Record Name: \n");
    printf("2. Update Record Amount: \n");
    printf("3. Update Record Type or Expense Type: \n");
    printf("4. Update all\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    FILE *fp = fopen("File_Of_Records.txt", "r");
    FILE *tp = fopen("temp.txt", "w");
    if(fp == NULL || tp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }

    switch (choice)
    {
    case 1:
        modifyName(index);        
        break;
    case 2:
        modifyAmount(index);        
        break;
    case 3:
        modifyRtype(index);        
        break;
    case 4:
        for(int i = 1; i < index; i++){
            fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
            fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
        }
        
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
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", index, record.name, record.amount, record.recordType, record.expenseType);
        fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);

        while(fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
            fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
        }
        fclose(fp);
        fclose(tp);
        fp = fopen("File_Of_Records.txt", "w");
        tp = fopen("temp.txt", "r");
        if(fp == NULL || tp == NULL){
            printf("\n\nError opening the file\n");
            return;
        }
        while(fscanf(tp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
            fprintf(fp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
        }
        fclose(fp);
        fclose(tp);
    
    default:
        printf("Invalid choice. Please enter a valid option.\n");
        break;
    }
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
    do {
        printMenu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertRecord();
                break;
            case 2:
                displayRecord();
                break;
            case 3:
                printf("\nEnter record name you want to find: ");
                char str[30];
                scanf("%s", str);
                searchByName(str);
                break;
            case 4:
                printf("\nEnter index number of the record you want to modify: ");
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
                printf("\nPROGRAM IS TERMINATED\n\n");
                exit(0);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 10);

    return 0;
}
