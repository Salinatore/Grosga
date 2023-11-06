/**
 * @file 7_Exercise1.c
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
    bool loanStatus;
    int currentLoanAmount;
    bool term;
    int creditScore;
    int annualIncome;
    char yearJob[MAX];
    char homeOwnership[MAX];
    char purpose[MAX];
    float monthlyDebt;
    float yearsOfCreditHistory;
    float monthsSinceLastDelinquent;
    int NumberOfOpenAccounts;
    int numberOfCreditProblems;
    int currentCreditBalance;
    int maximumOpenCredit;
    int bankruptcies;
    int taxLiens;
} cr;

void fillStructFromFile(const char *filename, struct credit *s);

int main() {
    const char *myfile = "Week_7/credit.csv";
    fillStructFromFile(myfile, &cr);


    printf("\n\n");
    return 0;
}

void fillStructFromFile(const char *filename, struct credit *s) { //da fixare
    FILE *fp =fopen(filename, "r+");

    if(fp == NULL) {
        printf("\nErrore nell'apertura del file");
        exit(1);
    }
    //TODO
    /*
     * add a way to read the file into structure
     */
    fclose(fp);
}