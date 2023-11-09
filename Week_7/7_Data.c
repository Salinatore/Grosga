/**
 * @file 7_Exercise.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 
 * @date 06/11/23
*/

#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"

#define K 11 //meglio dispari
#define MAX 256
#define NA false //not-available

struct credit {
    char loanID[MAX];
    char customerID[MAX];
    char loanStatus[MAX];
    int currentLoanAmount;
    char term[MAX];
    int creditScore;
    int annualIncome;
    char yearJob[MAX];
    char homeOwnership[MAX];
    char purpose[MAX];
    float monthlyDebt;
    float yearsOfCreditHistory;
    float monthsSinceLastDelinquent;
    int numberOfOpenAccounts;
    int numberOfCreditProblems;
    int currentCreditBalance;
    int maximumOpenCredit;
    int bankruptcies;
    int taxLiens;
};

int linesofFile(FILE *myfile);
void fillData(FILE *myfile, struct credit ar[], int ar_length);
void printDataset(struct credit ar[], int ar_length);

int main() {
    FILE *fp = fopen("Week_7/credit.csv", "r"); //TODO da cambiare quando si consengna

    if(fp == NULL) {
        printf("\nErrore nell'apertura del file");
        return EXIT_FAILURE;
    } else {
        int n_row = linesofFile(fp);

        struct credit *data = malloc(n_row * sizeof(struct credit));

        struct credit data[n_row];

        fillData(fp,data, n_row); //write into the array all the data
        printDataset(data, n_row);

        fclose(fp);
        printf("\n\n");
        return EXIT_SUCCESS;
    }
}

int linesofFile(FILE *myfile) {
    int n = 0;
    for(char c = getc(myfile); c != EOF; c = getc(myfile)) //count the number of lines
        if (c == '\n')
            n++;

    return n;
}

void fillData(FILE *myfile, struct credit ar[], int ar_length) {
    for(int i = 0; i < ar_length; i++)
        fscanf(myfile, "%s,%s,%s,%d,%s,%d,%d,%s,%s,%s,%f,%f,%f,%d,%d,%d,%d,%d,%d", \
                ar[i-1].loanID, ar[i-1].customerID, ar[i-1].loanStatus, ar[i-1].currentLoanAmount, ar[i-1].term, ar[i-1].creditScore, ar[i-1].annualIncome,     \
                ar[i-1].yearJob, ar[i-1].homeOwnership, ar[i-1].purpose, ar[i-1].monthlyDebt, ar[i-1].yearsOfCreditHistory, ar[i-1].monthsSinceLastDelinquent,  \
                ar[i-1].numberOfOpenAccounts, ar[i-1].numberOfCreditProblems, ar[i-1].currentCreditBalance, ar[i-1].maximumOpenCredit, ar[i-1].bankruptcies,    \
                ar[i-1].taxLiens);
}

void printDataset(struct credit ar[], int ar_length) {
    for(int i = 1; i <= ar_length; i++) {
        printf("\n%s,%s,%s,%d,%s,%d,%d,%s,%s,%s,%f,%f,%f,%d,%d,%d,%d,%d,%d", \
                ar[i-1].loanID, ar[i-1].customerID, ar[i-1].loanStatus, ar[i-1].currentLoanAmount, ar[i-1].term, ar[i-1].creditScore, ar[i-1].annualIncome,     \
                ar[i-1].yearJob, ar[i-1].homeOwnership, ar[i-1].purpose, ar[i-1].monthlyDebt, ar[i-1].yearsOfCreditHistory, ar[i-1].monthsSinceLastDelinquent,  \
                ar[i-1].numberOfOpenAccounts, ar[i-1].numberOfCreditProblems, ar[i-1].currentCreditBalance, ar[i-1].maximumOpenCredit, ar[i-1].bankruptcies,    \
                ar[i-1].taxLiens);
    }
}