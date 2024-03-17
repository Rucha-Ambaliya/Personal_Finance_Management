#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// The code defines colors for styling the output

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_HEADER "\x1b[38;2;255;99;97m"    // #ff6361
#define ANSI_COLOR_MENU "\x1b[38;2;188;80;144m"     // #bc5090
#define ANSI_COLOR_ROW "\x1b[38;2;88;80;141m"       // #58508d
#define ANSI_COLOR_CHOICE "\x1b[38;2;255;166;0m"    // #ffa600
#define ANSI_COLOR_SUBCHOICE "\e[38;2;229;193;133m"
#define ANSI_COLOR_OTHERS "\x1b[38;2;0;63;92m"     // #003f5c


int no_of_records;

// Struct Record is defined to represent each record in the file
struct Record {
    int idx;
    char name[20];
    int amount;
    char recordType[8];
    char expenseType[8];
} record;

// Function to print the main menu
void printMenu() {
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\n" ANSI_COLOR_HEADER "PERSONAL FINANCE MANAGEMENT" ANSI_COLOR_RESET "\n");
    printf("\n" ANSI_COLOR_MENU "1. Insert record\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MENU "2. Display record \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MENU "3. Search record by name\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MENU "4. Modify record \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MENU "5. Delete record \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MENU "6. Sort data based on the amount\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MENU "7. Display Income sources \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MENU "8. Display expenses \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MENU "9. Calculate interest of loan \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MENU "10. Generate Report \n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_MENU "11. Exit \n" ANSI_COLOR_RESET);
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
}

// Function to count the number of records in the file
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

// Function to insert a new record into the file
void insertRecord() {
    FILE *fp = fopen("File_Of_Records.txt", "a");
    if(fp == NULL){
        printf(ANSI_COLOR_HEADER"\n\nError opening the file\n"ANSI_COLOR_RESET);
        return;
    }
    no_of_records = getNoOfRecords();
    record.idx = no_of_records + 1;
    printf(ANSI_COLOR_OTHERS "\nEnter Name of the record: "ANSI_COLOR_RESET);
    scanf("%s", record.name);
    printf(ANSI_COLOR_OTHERS "Enter the Amount: " ANSI_COLOR_RESET);
    scanf("%d", &record.amount);
    printf(ANSI_COLOR_OTHERS "Enter type of the record -> Ex. INCOME / EXPENSE : " ANSI_COLOR_RESET);
    scanf("%s", record.recordType);
    if(strcmp(record.recordType, "INCOME") == 0)
        strcpy(record.expenseType, "NULL");
    else if(strcmp(record.recordType, "EXPENSE") == 0){
        printf(ANSI_COLOR_OTHERS "Type of the Expense -> Ex. NEED / WANT / INVEST : " ANSI_COLOR_RESET);
        scanf("%s", record.expenseType);
    } 
    else {
        printf(ANSI_COLOR_OTHERS "\nInvalid Input" ANSI_COLOR_RESET "\n");
        return;
    }
    fprintf(fp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    fclose(fp);
}

// Function to display all records from the file
void displayRecord() {
    no_of_records = getNoOfRecords();
    if(no_of_records <= 0){
        printf(ANSI_COLOR_OTHERS "\n\nFILE IS EMPTY\n\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    printf("\n\n" ANSI_COLOR_HEADER "PERSONAL FINANCE MANAGEMENT" ANSI_COLOR_RESET "\n");
    printf("\n" ANSI_COLOR_ROW "%-4s %-20s %-8s %-10s %-10s\n" ANSI_COLOR_RESET, "IDX", "Record Name", "Amount", "RType", "EType");
    while(fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        printf("%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose((fp));
}

// Function to search for records by name
void searchByName(char *nameToFind){
    no_of_records = getNoOfRecords();
    int similarRecord = 0;
    if(no_of_records <= 0){
        printf("\n\n" ANSI_COLOR_OTHERS "FILE IS EMPTY" ANSI_COLOR_RESET "\n\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    printf("\n\n" ANSI_COLOR_HEADER "PERSONAL FINANCE MANAGEMENT" ANSI_COLOR_RESET "\n");
    printf("\n" ANSI_COLOR_ROW "%-4s %-20s %-8s %-10s %-10s\n" ANSI_COLOR_RESET, "IDX", "Record Name", "Amount", "RType", "EType");
    while(fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        if(strcmp(record.name, nameToFind) == 0){
            printf("%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
            similarRecord++;
        }
    }
    if (similarRecord == 0)
        printf("\n\n" ANSI_COLOR_OTHERS "No such record exist in the file" ANSI_COLOR_RESET "\n");
    else 
        printf("\n\n" ANSI_COLOR_OTHERS "%d records matched" ANSI_COLOR_RESET "\n", similarRecord);
    
    fclose(fp);
}

// Function to modify the name of a record
void modifyName(int index){
    no_of_records = getNoOfRecords();
    if (index > no_of_records || index < 1)
    {
        printf("\n\n" ANSI_COLOR_OTHERS "INVALID INDEX" ANSI_COLOR_RESET "\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records.txt", "r");
    FILE *tp = fopen("temp.txt", "w");
    if(fp == NULL || tp == NULL){
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    for(int i = 1; i < index; i++){
        fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    
    fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
    printf("\n" ANSI_COLOR_OTHERS "Enter Name of the record: " ANSI_COLOR_RESET);
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
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    while(fscanf(tp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        fprintf(fp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose(fp);
    fclose(tp);
    printf("\n\n" ANSI_COLOR_OTHERS "RECORD SUCCESSFULLY UPDATED" ANSI_COLOR_RESET "\n");
}

// Function to modify the amount of a record
void modifyAmount(int index){
    no_of_records = getNoOfRecords();
    if (index > no_of_records || index < 1)
    {
        printf("\n\n" ANSI_COLOR_OTHERS "INVALID INDEX" ANSI_COLOR_RESET "\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records.txt", "r");
    FILE *tp = fopen("temp.txt", "w");
    if(fp == NULL || tp == NULL){
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    for(int i = 1; i < index; i++){
        fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    
    fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
    printf("\n" ANSI_COLOR_OTHERS "Enter the Amount: " ANSI_COLOR_RESET);
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
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    while(fscanf(tp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        fprintf(fp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose(fp);
    fclose(tp);
    printf("\n\n" ANSI_COLOR_OTHERS "RECORD SUCCESSFULLY UPDATED" ANSI_COLOR_RESET "\n");
}

// Function to modify the type of a record
void modifyRtype(int index){
    no_of_records = getNoOfRecords();
    if (index > no_of_records || index < 1)
    {
        printf("\n\n" ANSI_COLOR_OTHERS "INVALID INDEX" ANSI_COLOR_RESET "\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records.txt", "r");
    FILE *tp = fopen("temp.txt", "w");
    if(fp == NULL || tp == NULL){
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    for(int i = 1; i < index; i++){
        fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    
    fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
    printf("\n" ANSI_COLOR_OTHERS "Enter type of the record -> Ex. INCOME / EXPENSE : " ANSI_COLOR_RESET);
    scanf("%s", record.recordType);
    if(strcmp(record.recordType, "INCOME") == 0)
        strcpy(record.expenseType, "NULL");
    else if(strcmp(record.recordType, "EXPENSE") == 0){
        printf(ANSI_COLOR_OTHERS "Type of the Expense -> Ex. NEED / WANT / INVEST : " ANSI_COLOR_RESET);
        scanf("%s", record.expenseType);
    } 
    else {
        printf("\n" ANSI_COLOR_OTHERS "Invalid Input" ANSI_COLOR_RESET "\n");
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
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    while(fscanf(tp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        fprintf(fp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose(fp);
    fclose(tp);
    printf("\n\n" ANSI_COLOR_OTHERS "RECORD SUCCESSFULLY UPDATED" ANSI_COLOR_RESET "\n");
}

// Function to modify a record (name, amount, type)
void modifyRecord(int index) {
    no_of_records = getNoOfRecords();
    if (index > no_of_records || index < 1)
    {
        printf("\n\n" ANSI_COLOR_OTHERS "INVALID INDEX" ANSI_COLOR_RESET "\n");
        return;
    }
    
    int choice;
    printf("\n\n" ANSI_COLOR_OTHERS "1. Update Record Name: " ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_OTHERS "2. Update Record Amount: " ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_OTHERS "3. Update Record Type or Expense Type: " ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_OTHERS "4. Update all: " ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_SUBCHOICE "Enter choice: " ANSI_COLOR_RESET);
    scanf("%d", &choice);
    FILE *fp = fopen("File_Of_Records.txt", "r");
    FILE *tp = fopen("temp.txt", "w");
    if(fp == NULL || tp == NULL){
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
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
        
        printf("\n" ANSI_COLOR_OTHERS "Enter Name of the record: " ANSI_COLOR_RESET);
        scanf("%s", record.name);
        printf(ANSI_COLOR_OTHERS "Enter the Amount: " ANSI_COLOR_RESET);
        scanf("%d", &record.amount);
        printf(ANSI_COLOR_OTHERS "Enter type of the record -> Ex. INCOME / EXPENSE : " ANSI_COLOR_RESET);
        scanf("%s", record.recordType);
        if(strcmp(record.recordType, "INCOME") == 0)
            strcpy(record.expenseType, "NULL");
        else if(strcmp(record.recordType, "EXPENSE") == 0){
            printf(ANSI_COLOR_OTHERS "Type of the Expense -> Ex. NEED / WANT / INVEST : " ANSI_COLOR_RESET);
            scanf("%s", record.expenseType);
        } 
        else {
            printf("\n\n" ANSI_COLOR_OTHERS "INVALID INPUT" ANSI_COLOR_RESET "\n");
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
            printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
            return;
        }
        while(fscanf(tp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
            fprintf(fp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
        }
        fclose(fp);
        fclose(tp);
        printf("\n\n" ANSI_COLOR_OTHERS "RECORD SUCCESSFULLY UPDATED" ANSI_COLOR_RESET "\n");
    
    default:
        printf("\n\n" ANSI_COLOR_OTHERS "Invalid choice. Please enter a valid option." ANSI_COLOR_RESET "\n");
        break;
    }
}

// Function to delete a record by index
void deleteRecord(int index) {
    no_of_records = getNoOfRecords();
    if (index > no_of_records || index < 1)
    {
        printf("\n\n" ANSI_COLOR_OTHERS "INVALID INDEX" ANSI_COLOR_RESET "\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records.txt", "r");
    FILE *tp = fopen("temp.txt", "w");
    if(fp == NULL || tp == NULL){
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    for(int i = 1; i < index; i++){
        fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    
    fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType);
        
    while(fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx - 1, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose(fp);
    fclose(tp);
    fp = fopen("File_Of_Records.txt", "w");
    tp = fopen("temp.txt", "r");
    if(fp == NULL || tp == NULL){
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    while(fscanf(tp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        fprintf(fp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    fclose(fp);
    fclose(tp);
    printf("\n\n" ANSI_COLOR_OTHERS "RECORD SUCCESSFULLY DELETED" ANSI_COLOR_RESET "\n");
}

// Function to sort records by amount
void sortRecordsByAmount() {
    no_of_records = getNoOfRecords();
    struct Record recordsArr[no_of_records];
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    int k = 0;
    while(fscanf(fp, "%d\t %s\t %d\t %s\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        recordsArr[k] = record;
        k++;
    }
    fclose(fp);

    for(int i = 0; i < no_of_records; i++){
        for (int j = 0; j < no_of_records; j++)
        {
            if (recordsArr[j].amount > recordsArr[i].amount)
            {
                struct Record temp = recordsArr[i];
                recordsArr[i] = recordsArr[j];
                recordsArr[j] = temp;
            }
        }
    }
    printf("\n\n" ANSI_COLOR_HEADER "PERSONAL FINANCE MANAGEMENT" ANSI_COLOR_RESET "\n");
    printf("\n" ANSI_COLOR_ROW "%-4s %-20s %-8s %-10s %-10s\n" ANSI_COLOR_RESET, "IDX", "Record Name", "Amount", "RType", "EType");
    for(int i = 0; i < no_of_records; i++){
        printf("%-4d %-20s %-8d %-10s %-10s\n", i + 1, recordsArr[i].name, recordsArr[i].amount, recordsArr[i].recordType, recordsArr[i].expenseType);
    }

}

// Function to display income sources
void displayIncomeSources() {
    no_of_records = getNoOfRecords();
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    printf("\n\n" ANSI_COLOR_HEADER "PERSONAL FINANCE MANAGEMENT" ANSI_COLOR_RESET "\n");
    printf("\n" ANSI_COLOR_ROW "%-4s %-20s %-8s %-10s %-10s\n" ANSI_COLOR_RESET, "IDX", "Record Name", "Amount", "RType", "EType");
    int similarRecord = 0;
    while(fscanf(fp, "%d\t %s\t %d\t %s\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        if(strcmp(record.recordType, "INCOME") == 0){
            similarRecord++;
            printf("%-4d %-20s %-8d %-10s %-10s\n", similarRecord, record.name, record.amount, record.recordType, record.expenseType);
        }
    }
    if (similarRecord == 0)
        printf("\n\n" ANSI_COLOR_OTHERS "No such record exist in the file" ANSI_COLOR_RESET "\n");
    else 
        printf("\n\n" ANSI_COLOR_OTHERS "%d records matched" ANSI_COLOR_RESET "\n", similarRecord);
    
    fclose(fp);
}

// Function to display expenses
void displayExpenses() {
    no_of_records = getNoOfRecords();
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }
    printf("\n\n" ANSI_COLOR_HEADER "PERSONAL FINANCE MANAGEMENT" ANSI_COLOR_RESET "\n");
    printf("\n" ANSI_COLOR_ROW "%-4s %-20s %-8s %-10s %-10s\n" ANSI_COLOR_RESET, "IDX", "Record Name", "Amount", "RType", "EType");
    int similarRecord = 0;
    while(fscanf(fp, "%d\t %s\t %d\t %s\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        if(strcmp(record.recordType, "EXPENSE") == 0){
            similarRecord++;
            printf("%-4d %-20s %-8d %-10s %-10s\n", similarRecord, record.name, record.amount, record.recordType, record.expenseType);
        }
    }
    if (similarRecord == 0)
        printf("\n\n" ANSI_COLOR_OTHERS "No such record exist in the file" ANSI_COLOR_RESET "\n");
    else 
        printf("\n\n" ANSI_COLOR_OTHERS "%d records matched" ANSI_COLOR_RESET "\n", similarRecord);
    
    fclose(fp);
}

// Function to calculate loan interest
void calculateLoanInterest() {
    double loanAmount, annualInterestRate, monthlyInterestRate;
    int loanDurationMonths;
    
    printf("\n" ANSI_COLOR_OTHERS "Enter loan amount: " ANSI_COLOR_RESET);
    scanf("%lf", &loanAmount);
    printf(ANSI_COLOR_OTHERS "Enter annual interest rate (in percentage): " ANSI_COLOR_RESET);
    scanf("%lf", &annualInterestRate);
    printf(ANSI_COLOR_OTHERS "Enter loan duration (in months): " ANSI_COLOR_RESET);
    scanf("%d", &loanDurationMonths);
    
    // Convert annual interest rate to monthly interest rate
    monthlyInterestRate = annualInterestRate / 12.0 / 100.0;
    
    // Calculate monthly payment using formula for amortizing loan
    double monthlyPayment = loanAmount * (monthlyInterestRate * pow(1 + monthlyInterestRate, loanDurationMonths)) / (pow(1 + monthlyInterestRate, loanDurationMonths) - 1);
    
    // Calculate total payment over the loan term
    double totalPayment = monthlyPayment * loanDurationMonths;
    
    // Calculate total interest paid over the loan term
    double totalInterest = totalPayment - loanAmount;
    
    // Print results
    printf("\n\n" ANSI_COLOR_HEADER "PERSONAL FINANCE MANAGEMENT" ANSI_COLOR_RESET "\n");
    printf("\n" ANSI_COLOR_OTHERS "Loan Details:" ANSI_COLOR_RESET "\n");
    printf(ANSI_COLOR_OTHERS "Loan Amount: " ANSI_COLOR_RESET "%.2lf\n", loanAmount);
    printf(ANSI_COLOR_OTHERS "Annual Interest Rate: " ANSI_COLOR_RESET "%.2lf%%\n", annualInterestRate);
    printf(ANSI_COLOR_OTHERS "Loan Duration (months): " ANSI_COLOR_RESET "%d\n", loanDurationMonths);
    printf("\n" ANSI_COLOR_OTHERS "Monthly Payment: " ANSI_COLOR_RESET "%.2lf\n", monthlyPayment);
    printf(ANSI_COLOR_OTHERS "Total Payment: " ANSI_COLOR_RESET "%.2lf\n", totalPayment);
    printf(ANSI_COLOR_OTHERS "Total Interest Paid: " ANSI_COLOR_RESET "%.2lf\n", totalInterest);
}

void generateReport() {
    double income = 0;
    double needsExpenses = 0;
    double wantsExpenses = 0;
    double savingsExpenses = 0;

    int no_of_records = getNoOfRecords();
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\n" ANSI_COLOR_OTHERS "Error opening the file" ANSI_COLOR_RESET "\n");
        return;
    }

    while(fscanf(fp, "%d\t %s\t %d\t %s\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        if(strcmp(record.recordType, "INCOME") == 0){
            income += record.amount;
        } else if(strcmp(record.recordType, "EXPENSE") == 0) {
            if(strcmp(record.expenseType, "NEED") == 0) {
                needsExpenses += record.amount;
            } else if(strcmp(record.expenseType, "WANT") == 0) {
                wantsExpenses += record.amount;
            } else if(strcmp(record.expenseType, "INVEST") == 0) {
                savingsExpenses += record.amount;
            }
        }
    }
    fclose(fp);

    double needsRatio = 0.50;
    double wantsRatio = 0.30;
    double savingsRatio = 0.20;

    // Calculate the total expenses in each category
    double totalExpenses = needsExpenses + wantsExpenses + savingsExpenses;

    // Calculate the remaining income after deducting total expenses
    double remainingIncome = income - totalExpenses;

    // Calculate the needs, wants, and savings amount based on the remaining income
    double needsAmount = income * needsRatio;
    double wantsAmount = income * wantsRatio;
    double savingsAmount = income * savingsRatio;

    printf(ANSI_COLOR_HEADER "\n\nFinancial Distribution Report\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_OTHERS "Income: " ANSI_COLOR_RESET "%.2f\n", income);
    printf(ANSI_COLOR_OTHERS "Total Expenses: " ANSI_COLOR_RESET "%.2f\n", totalExpenses);
    printf(ANSI_COLOR_OTHERS"Remaining Income: " ANSI_COLOR_RESET "%.2f\n", remainingIncome);
    printf(ANSI_COLOR_OTHERS "Needs Expenses: " ANSI_COLOR_RESET "%.2f\n", needsExpenses);
    printf(ANSI_COLOR_OTHERS "Wants Expenses: " ANSI_COLOR_RESET "%.2f\n", wantsExpenses);
    printf(ANSI_COLOR_OTHERS "Savings Expenses: " ANSI_COLOR_RESET "%.2f\n", savingsExpenses);
    printf(ANSI_COLOR_OTHERS "Needs Expected: " ANSI_COLOR_RESET "%.2f\n", needsAmount);
    printf(ANSI_COLOR_OTHERS "Wants Expected: " ANSI_COLOR_RESET "%.2f\n", wantsAmount);
    printf(ANSI_COLOR_OTHERS "Investment Expected: " ANSI_COLOR_RESET "%.2f\n", savingsAmount);
    
    // Check if the user's distribution matches the standard ratio
    if (needsExpenses > needsAmount || wantsExpenses > wantsAmount || savingsExpenses < savingsAmount) {
        printf("\n" ANSI_COLOR_HEADER "Warning: Your income distribution does not meet the recommended ratio.\n" ANSI_COLOR_RESET);
        printf("Consider adjusting your spending to align with the following ratio:\n");
        printf("Needs: 50%%, Wants: 30%%, Savings: 20%%\n");
    } else {
        printf(ANSI_COLOR_SUBCHOICE "\nCongratulations! Your income distribution meets the recommended ratio.\n" ANSI_COLOR_RESET);
    }

    // Check individual expenses against the standard ratios
    if (needsExpenses > needsAmount) {
        printf("\n" ANSI_COLOR_HEADER "Warning: Your needs expenses exceed the recommended ratio.\n" ANSI_COLOR_RESET);
    }
    if (wantsExpenses > wantsAmount) {
        printf(ANSI_COLOR_HEADER "Warning: Your wants expenses exceed the recommended ratio.\n" ANSI_COLOR_RESET);
    }
    if (savingsExpenses < savingsAmount) {
        printf(ANSI_COLOR_HEADER "Warning: Your savings expenses exceed the recommended ratio.\n" ANSI_COLOR_RESET);
    }
}

int main() {
    int choice;
    int index;
    do {
        printMenu();
        printf(ANSI_COLOR_CHOICE "\nEnter your choice: " ANSI_COLOR_RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertRecord();
                break;
            case 2:
                displayRecord();
                break;
            case 3:
                printf("\n" ANSI_COLOR_OTHERS "Enter record name you want to find: " ANSI_COLOR_RESET);
                char str[30];
                scanf("%s", str);
                searchByName(str);
                break;
            case 4:
                printf("\n" ANSI_COLOR_OTHERS "Enter index number of the record you want to modify: " ANSI_COLOR_RESET);
                scanf("%d", &index);
                modifyRecord(index);
                break;
            case 5:
                printf("\n" ANSI_COLOR_OTHERS "Enter index number of the record you want to delete: " ANSI_COLOR_RESET);
                scanf("%d", &index);
                deleteRecord(index);
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
                generateReport();
                break;
            case 11:
                printf("\n" ANSI_COLOR_OTHERS "PROGRAM IS TERMINATED" ANSI_COLOR_RESET "\n\n");
                exit(0);
                break;
            default:
                printf("\n" ANSI_COLOR_OTHERS "Invalid choice. Please enter a valid option." ANSI_COLOR_RESET "\n");
        }
    } while (choice != 11);

    return 0;
}
