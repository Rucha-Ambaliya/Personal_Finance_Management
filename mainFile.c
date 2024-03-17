#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_HEADER "\x1b[38;2;255;99;97m"    // #ff6361
#define ANSI_COLOR_MENU "\x1b[38;2;188;80;144m"     // #bc5090
#define ANSI_COLOR_ROW "\x1b[38;2;88;80;141m"       // #58508d
#define ANSI_COLOR_CHOICE "\x1b[38;2;255;166;0m"    // #ffa600
#define ANSI_COLOR_SUBCHOICE "\e[38;2;229;193;133m"
#define ANSI_COLOR_OTHERS "\x1b[38;2;0;63;92m"     // #003f5c


int no_of_records;

struct Record {
    int idx;
    char name[20];
    int amount;
    char recordType[8];
    char expenseType[8];
} record;

void printMenu() {
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
    printf(ANSI_COLOR_MENU "10. Exit \n" ANSI_COLOR_RESET);
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

void calculateLoanInterest() {
    double loanAmount, annualInterestRate, monthlyInterestRate;
    int loanDurationMonths;
    
    // Input loan details
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
                printf("\n" ANSI_COLOR_OTHERS "PROGRAM IS TERMINATED" ANSI_COLOR_RESET "\n\n");
                exit(0);
                break;
            default:
                printf("\n" ANSI_COLOR_OTHERS "Invalid choice. Please enter a valid option." ANSI_COLOR_RESET "\n");
        }
    } while (choice != 10);

    return 0;
}
