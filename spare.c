#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    printf("\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\nPERSONAL FINANCE MANAGEMENT\n");
    printf("\nMenu:\n");
    printf("1. Insert a record\n");
    printf("2. Display records\n");
    printf("3. Search a record by name\n");
    printf("4. Modify a record\n");
    printf("5. Delete a record\n");
    printf("6. Sort data based on the amount\n");
    printf("7. Display Income sources\n");
    printf("8. Display expenses\n");
    printf("9. Calculate interest of loan\n");
    printf("10. Generate Report\n");
    printf("11. Exit\n");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
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
        if(
            strcmp(record.expenseType, "NEED") == 0 ||
            strcmp(record.expenseType, "WANT") == 0 ||
            strcmp(record.expenseType, "INVEST") == 0
        ){}
        else{
            printf("\nInvalid Input\n");
            return;
        }
    } 
    else {
        printf("\nInvalid Input\n");
        return;
    }
    fprintf(fp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    printf("\n\nRECORD SUCCESSFULLY INSERTED\n");
    fclose(fp);
}

// Function to display all records from the file
void displayRecord() {
    no_of_records = getNoOfRecords();
    if(no_of_records <= 0){
        printf("\n\nFILE IS EMPTY\n");
        return;
    }
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    printf("\n\nPERSONAL FINANCE MANAGEMENT\n");
    printf("\n%-4s %-20s %-8s %-10s %-10s\n", "IDX", "Record Name", "Amount", "RType", "EType");
    printf("----------------------------------------------------------\n");
    while(fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        printf("%-4d %-20s %-8d %-10s %-10s\n", record.idx, record.name, record.amount, record.recordType, record.expenseType);
    }
    printf("\n\n%d records matched\n", no_of_records);
    fclose((fp));
}

// Function to search for records by name
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
    printf("\n\nPERSONAL FINANCE MANAGEMENT\n");
    printf("\n%-4s %-20s %-8s %-10s %-10s\n", "IDX", "Record Name", "Amount", "RType", "EType");
    printf("----------------------------------------------------------\n");
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
    
    fclose(fp);
}

// Function to modify the name of a record
void modifyName(int index){
    no_of_records = getNoOfRecords();
    if (index > no_of_records || index < 1)
    {
        printf("\n\nINVALID INDEX\n");
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
    printf("\n\nRECORD SUCCESSFULLY UPDATED\n");
}

// Function to modify the amount of a record
void modifyAmount(int index){
    no_of_records = getNoOfRecords();
    if (index > no_of_records || index < 1)
    {
        printf("\n\nINVALID INDEX\n");
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
    printf("\nEnter the Amount: ");
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
    printf("\n\nRECORD SUCCESSFULLY UPDATED\n");
}

// Function to modify the type of a record
void modifyRtype(int index){
    no_of_records = getNoOfRecords();
    if (index > no_of_records || index < 1)
    {
        printf("\n\nINVALID INDEX\n");
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
    printf("\nEnter type of the record -> Ex. INCOME / EXPENSE : ");
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
    printf("\n\nRECORD SUCCESSFULLY UPDATED\n");
}

// Function to modify a record (name, amount, type)
void modifyRecord(int index) {
    no_of_records = getNoOfRecords();
    if (index > no_of_records || index < 1)
    {
        printf("\n\nINVALID INDEX\n");
        return;
    }
    
    int choice;
    printf("\n\n1. Update Record Name: \n");
    printf("2. Update Record Amount: \n");
    printf("3. Update Record Type or Expense Type: \n");
    printf("4. Update all: \n");
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
            printf("\n\nINVALID INPUT\n");
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
        printf("\n\nRECORD SUCCESSFULLY UPDATED\n");
    
    default:
        printf("\n\nInvalid choice. Please enter a valid option.\n");
        break;
    }
}

// Function to delete a record by index
void deleteRecord(int index) {
    no_of_records = getNoOfRecords();
    if (index > no_of_records || index < 1)
    {
        printf("\n\nINVALID INDEX\n");
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
        
    while(fscanf(fp, "%d\t %s\t %d\t %s\t\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        fprintf(tp, "%-4d %-20s %-8d %-10s %-10s\n", record.idx - 1, record.name, record.amount, record.recordType, record.expenseType);
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
    printf("\n\nRECORD SUCCESSFULLY DELETED\n");
}

// Function to sort records by amount
void sortRecordsByAmount() {
    no_of_records = getNoOfRecords();
    struct Record recordsArr[no_of_records];
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
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
    printf("\n\nPERSONAL FINANCE MANAGEMENT\n");
    printf("\n%-4s %-20s %-8s %-10s %-10s\n", "IDX", "Record Name", "Amount", "RType", "EType");
    printf("----------------------------------------------------------\n");
    for(int i = 0; i < no_of_records; i++){
        printf("%-4d %-20s %-8d %-10s %-10s\n", i + 1, recordsArr[i].name, recordsArr[i].amount, recordsArr[i].recordType, recordsArr[i].expenseType);
    }
    printf("\n\n%d records matched\n", no_of_records);
}

// Function to display income sources
void displayIncomeSources() {
    no_of_records = getNoOfRecords();
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    printf("\n\nPERSONAL FINANCE MANAGEMENT\n");
    printf("\n%-4s %-20s %-8s %-10s %-10s\n", "IDX", "Record Name", "Amount", "RType", "EType");
    printf("----------------------------------------------------------\n");
    int similarRecord = 0;
    while(fscanf(fp, "%d\t %s\t %d\t %s\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        if(strcmp(record.recordType, "INCOME") == 0){
            similarRecord++;
            printf("%-4d %-20s %-8d %-10s %-10s\n", similarRecord, record.name, record.amount, record.recordType, record.expenseType);
        }
    }
    if (similarRecord == 0)
        printf("\n\nNo such record exist in the file\n");
    else 
        printf("\n\n%d records matched\n", similarRecord);
    
    fclose(fp);
}

// Function to display expenses
void displayExpenses() {
    no_of_records = getNoOfRecords();
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
        return;
    }
    printf("\n\nPERSONAL FINANCE MANAGEMENT\n");
    printf("\n%-4s %-20s %-8s %-10s %-10s\n", "IDX", "Record Name", "Amount", "RType", "EType");
    printf("----------------------------------------------------------\n");
    int similarRecord = 0;
    while(fscanf(fp, "%d\t %s\t %d\t %s\t %s\n", &record.idx, record.name, &record.amount, record.recordType, record.expenseType) != EOF){
        if(strcmp(record.recordType, "EXPENSE") == 0){
            similarRecord++;
            printf("%-4d %-20s %-8d %-10s %-10s\n", similarRecord, record.name, record.amount, record.recordType, record.expenseType);
        }
    }
    if (similarRecord == 0)
        printf("\n\nNo such record exist in the file\n");
    else 
        printf("\n\n%d records matched\n", similarRecord);
    
    fclose(fp);
}

// Function to calculate loan interest
void calculateLoanInterest() {
    double loanAmount, annualInterestRate, monthlyInterestRate;
    int loanDurationMonths;
    
    printf("\nEnter loan amount: ");
    scanf("%lf", &loanAmount);
    printf("Enter annual interest rate (in percentage): ");
    scanf("%lf", &annualInterestRate);
    printf("Enter loan duration (in months): ");
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
    printf("\n\nPERSONAL FINANCE MANAGEMENT\n");
    printf("\nLoan Details:\n\n");
    printf("Loan Amount           : %.2lf\n", loanAmount);
    printf("Annual Interest Rate  : %.2lf%%\n", annualInterestRate);
    printf("Loan Duration (months): %d\n", loanDurationMonths);
    printf("\nMonthly Payment       : %.2lf\n", monthlyPayment);
    printf("Total Payment         : %.2lf\n", totalPayment);
    printf("Total Interest Paid   : %.2lf\n", totalInterest);
}

void generateReport() {
    double income = 0;
    double needsExpenses = 0;
    double wantsExpenses = 0;
    double savingsExpenses = 0;

    int no_of_records = getNoOfRecords();
    FILE *fp = fopen("File_Of_Records.txt", "r");
    if(fp == NULL){
        printf("\n\nError opening the file\n");
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

    printf("\n\nFinancial Distribution Report\n\n");
    printf("Income                         :  %.2f\n", income);
    printf("Total Expenses                 :  %.2f\n", totalExpenses);
    printf("Remaining Income               :  %.2f\n\n", remainingIncome);
    printf("Needs Expenses                 :  %.2f\n", needsExpenses);
    printf("Wants Expenses                 :  %.2f\n", wantsExpenses);
    printf("Savings and Investment Expenses:  %.2f\n\n", savingsExpenses);
    printf("Needs Expected                 :  %.2f\n", needsAmount);
    printf("Wants Expected                 :  %.2f\n", wantsAmount);
    printf("Savings and Investment Expected:  %.2f\n", savingsAmount);
    
    if (totalExpenses > income) {
        printf("\nWarning: Your total expenses exceed your income.\n");
        printf("Ensure your expenses do not exceed your income to maintain financial stability.\n");
    }
    if (needsExpenses > needsAmount || wantsExpenses > wantsAmount || savingsExpenses < savingsAmount) {
        printf("\nWarning: Your income distribution does not meet the recommended ratio.\n");
        printf("Consider adjusting your spending priorities to align with the following ratio:\n");
        printf("Needs: 50%%, Wants: 30%%, Investment: 20%%\n\n");

        // Provide suggestions for adjusting spending priorities
        if (needsExpenses > needsAmount) {
            double adjustment = needsExpenses - needsAmount;
            printf("-> Reduce your needs expenses by %.2f to align with the recommended ratio.\n", adjustment);
            printf("-> Ensure that your essential needs are being met, but consider evaluating your expenses to see if any non-essential items can be reduced.\n\n");
        }
        if (wantsExpenses > wantsAmount) {
            double adjustment = wantsExpenses - wantsAmount;
            printf("-> Reduce your wants expenses by %.2f to align with the recommended ratio.\n", adjustment);
            printf("-> Review your discretionary spending on non-essential items such as entertainment, dining out, or luxury purchases. Consider cutting back on these expenses to bring them in line with your financial goals.\n\n");
        }
        if (savingsExpenses < savingsAmount) {
            double adjustment = savingsAmount - savingsExpenses;
            printf("-> Increase your savings and Invesment expenses by %.2f to align with the recommended ratio.\n", adjustment);
            printf("-> While it's important to prioritize savings, ensure that you are not neglecting your current needs and wants. Consider reallocating some funds from other categories to boost your savings.\n\n");
        }
    }
    else {
        printf("\nCongratulations! Your income distribution meets the recommended ratio of, Needs: 50%%, Wants: 30%%, Investment: 20%%\n\n");
        printf("Keep up the good work! Consistently managing your finances in this way will help you achieve your financial goals.\n\n");
        printf("Remember to review your finances regularly and make adjustments as needed to stay on track.\n\n");
    }
}

int main() {
    int choice;
    int index;
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
                scanf("%d", &index);
                modifyRecord(index);
                break;
            case 5:
                printf("\nEnter index number of the record you want to delete: ");
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
                printf("\nPROGRAM IS TERMINATED\n\n");
                exit(0);
                break;
            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
        }
    } while (choice != 11);

    return 0;
}