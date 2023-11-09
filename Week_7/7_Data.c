/**
 * @file 7_Exercise.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 
 * @date 06/11/23
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "string.h"

#define K 11 //meglio dispari, numero di vicini più vicini
#define LINES (int) 10000
#define MAX 256
#define NA false //not-available

/* Store csv data */
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
struct prestito {
    bool credit_policy; //1 se il cliente soddisfa i criteri di sottoscrizione del credito; 0 altrimenti
    char purpose[MAX]; //Lo scopo del prestito
    double int_rate; //Il tasso di interesse del prestito (ai mutuatari più rischiosi vengono assegnati tassi di interesse più elevati)
    unsigned int installment; //Le rate mensili dovute dal mutuatario se il prestito viene finanziato
    float log_annual_inc; //Il log naturale del reddito annuo autodichiarato del mutuatario
    float dti; //Il rapporto debito/reddito del mutuatario (importo del debito diviso per il reddito annuale)
    unsigned int fico; //Il punteggio di credito FICO del mutuatario.
    unsigned int days_with_cr_line; //Il numero di giorni in cui il debitore ha avuto una linea di credito
    unsigned int revol_bal; //Il saldo revolving del debitore (importo non pagato alla fine del ciclo di fatturazione della carta di credito)
    unsigned int revol_util; //Il tasso di utilizzo della linea revolving del debitore (l'importo della linea di credito utilizzata rispetto al credito totale disponibile)
    unsigned int inq_last_6mths; //Il numero di richieste di informazioni da parte dei creditori negli ultimi 6 mesi
    unsigned int delinq_2yrs; //Il numero di volte in cui il debitore è stato in ritardo di oltre 30 giorni con i pagamenti negli ultimi 2 anni.
    unsigned int pub_rec; //Il numero di registri pubblici in deroga del mutuatario
    bool not_fully_paid; //1 se il prestito non è stato completamente pagato; 0 altrimenti.
};

int linesofFile(FILE *myfile); //restituisce il numero di righe del file
void fillData(FILE *myfile, struct credit ar[], int ar_length);
void printDataset(struct credit ar[], int ar_length);
void findValues(struct credit *credito, struct prestito *prestito);

int main() { //TODO: da controllare
    FILE *fp = fopen("credit.csv", "r"); //TODO da cambiare quando si consengna

    if(fp == NULL) {
        printf("\nErrore nell'apertura del file");
        exit(1);
    } else {
        int n_row = linesofFile(fp);
        struct credit data[n_row];
        struct credit new_loan;
        struct prestito database[LINES];

        fillData(fp,data, n_row); //write into the array all the data
        printDataset(data, n_row);

        for(int i = 0; i < LINES; i++) {
            findValues(&data[i], &database[i]);
        }




        /** Add new loan */
        printf("\nInserisci il codice del prestito: ");
        scanf("%s", new_loan.loanID);


        fclose(fp);
        printf("\n\n");
        exit(0);
    }
}

int linesofFile(FILE *myfile) {
    int n = 0;
    for(char c = getc(myfile); c != EOF; c = getc(myfile)) //count the number of lines
        if (c == '\n')
            n++;

    return n;
}

void fillData(FILE *myfile, struct credit ar[], int ar_length) {//TODO: skip first line of csv file
    for(int i = 0; i < ar_length; i++) {
        //TODO: fill structure with data (virtuale for info)
    }
}
//idk if it is right
void printDataset(struct credit ar[], int ar_length) {
    for(int i = 1; i <= ar_length; i++) {
        printf("\n%s,%s,%s,%d,%s,%d,%d,%s,%s,%s,%f,%f,%f,%d,%d,%d,%d,%d,%d", \
                ar[i-1].loanID, ar[i-1].customerID, ar[i-1].loanStatus, ar[i-1].currentLoanAmount, ar[i-1].term, ar[i-1].creditScore, ar[i-1].annualIncome,     \
                ar[i-1].yearJob, ar[i-1].homeOwnership, ar[i-1].purpose, ar[i-1].monthlyDebt, ar[i-1].yearsOfCreditHistory, ar[i-1].monthsSinceLastDelinquent,  \
                ar[i-1].numberOfOpenAccounts, ar[i-1].numberOfCreditProblems, ar[i-1].currentCreditBalance, ar[i-1].maximumOpenCredit, ar[i-1].bankruptcies,    \
                ar[i-1].taxLiens);
    }
}

/*
 * double euclide(struct prestito a, struct prestito b) {
 * return sqrt(pow(a.credit_policy, 2) + pow(a.));
 * }
 *
 */

//TODO update file via ex 2
//

void findValues(struct credit *credito, struct prestito *prestito) {
    if()
        prestito->credit_policy = true;
    else if()
        prestito->credit_policy = false;

    strcpy(credito->purpose, prestito->purpose);



}