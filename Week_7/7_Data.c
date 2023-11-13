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
#include <string.h>

#define K 5 //meglio dispari, numero di vicini più vicini
#define LINES (int) 10000
#define ID_LENGTH 36
#define MAX 256
#define NA false //not-available

/* Store csv data */
struct credit {
    char loanID[ID_LENGTH];
    char customerID[ID_LENGTH];
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
    float revol_bal; //Il saldo revolving del debitore (importo non pagato alla fine del ciclo di fatturazione della carta di credito)
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
    FILE *fp = fopen("Week_7/credit.csv", "r"); //TODO da cambiare quando si consengna

    if(fp == NULL) {
        printf("\nErrore nell'apertura del file");
        exit(EXIT_FAILURE);
    } else {
        int n_row = linesofFile(fp);
        struct credit data[n_row];
        struct credit new_loan;
        struct prestito database[LINES];

        fillData(fp,data, LINES); //write into the array all the data
        printDataset(data, n_row);

        for(int i = 0; i < LINES; i++) {
            findValues(&data[i], &database[i]);
        }


        /** Add new loan */
        printf("\nInserisci il codice del prestito: ");
        scanf("%35s", new_loan.loanID);


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

void fillData(FILE *myfile, struct credit ar[], int ar_length) {
    char header[256];
    fgets(header, sizeof(header), myfile);  // Ignora l'intestazione

    for (int i = 0; i < ar_length; i++) {
        int result = fscanf(myfile, "%49[^,],%49[^,],%49[^,],%d,%49[^,],%d,%d,%49[^,],%49[^,],%49[^,],%f,%f,%f,%d,%d,%d,%d,%d,%d ",
                            ar[i].loanID, ar[i].customerID, ar[i].loanStatus, &ar[i].currentLoanAmount, ar[i].term, &ar[i].creditScore, &ar[i].annualIncome,
                            ar[i].yearJob, ar[i].homeOwnership, ar[i].purpose, &ar[i].monthlyDebt, &ar[i].yearsOfCreditHistory, &ar[i].monthsSinceLastDelinquent,
                            &ar[i].numberOfOpenAccounts, &ar[i].numberOfCreditProblems, &ar[i].currentCreditBalance, &ar[i].maximumOpenCredit, &ar[i].bankruptcies,
                            &ar[i].taxLiens);

        if (result != 18) {
            // La fscanf non ha letto tutti i campi correttamente
            fprintf(stderr, "Errore nella lettura della riga %d\n", i + 1);
            break;
        }
    }
}
//idk if it is right
void printDataset(struct credit ar[], int ar_length) {
    for(int i = 0; i < ar_length; i++) {
        printf("\n%s,%s,%s,%d,%s,%d,%d,%s,%s,%s,%f,%f,%f,%d,%d,%d,%d,%d,%d", \
                ar[i].loanID, ar[i].customerID, ar[i].loanStatus, ar[i].currentLoanAmount, ar[i].term, ar[i].creditScore, ar[i].annualIncome,     \
                ar[i].yearJob, ar[i].homeOwnership, ar[i].purpose, ar[i].monthlyDebt, ar[i].yearsOfCreditHistory, ar[i].monthsSinceLastDelinquent,  \
                ar[i].numberOfOpenAccounts, ar[i].numberOfCreditProblems, ar[i].currentCreditBalance, ar[i].maximumOpenCredit, ar[i].bankruptcies,    \
                ar[i].taxLiens);
    }
}

/**
 * Algoritmo:
 * 1.Scegliere il valore di K, cioè il numero di vicini più prossimi che verrà utilizzato per fare la previsione ✅
 * 2.Calcolare la distanza tra quel punto e tutti i punti dell'insieme di training
 * 3.Selezionare i K vicini più prossimi in base alle distanze calcolate
 * 4.Assegnare l'etichetta della classe maggioritaria al nuovo punto
 * 5.Ripetere i passaggi da 2 a 4 per tutti i punti dati dell'insieme di test
 * 6.Valutare l'accuratezza dell'algoritmo (usando il 25% dei dati del dataset dato).
 **/

/*
 * double euclide(struct prestito a, struct prestito b) {
 * return sqrt(pow(a.credit_policy, 2) + pow(a.));
 * }
 *
 */

//TODO update file via ex 2

void findValues(struct credit *credito, struct prestito *prestito) {
    if(strcmp(credito->loanStatus, "Fully Paid") == 0)
        prestito->credit_policy = true;
    else if(strcmp(credito->loanStatus, "Charged Off") == 0)
        prestito->credit_policy = false;

    strcpy(credito->purpose, prestito->purpose); //check it
    prestito->int_rate = 0.05 * (credito->annualIncome) / (1 + 0.1 * credito->creditScore);

    if(prestito->credit_policy == true) {
        double monthlyInterestRate = (prestito->int_rate / 100.0) / 12.0;
        prestito->installment = ceil(log(1 - (credito->currentLoanAmount * monthlyInterestRate) / credito->monthlyDebt) / log(1 + monthlyInterestRate));
    } else
        prestito->installment = 0;

    prestito->log_annual_inc = log(credito->annualIncome);
    //prestito->dti = credito->debtAmount / credito->annualIncome;
    prestito->fico = credito->creditScore;

    prestito->days_with_cr_line;
    prestito->revol_bal;
    prestito->revol_util; //Il tasso di utilizzo della linea revolving del debitore (l'importo della linea di credito utilizzata rispetto al credito totale disponibile)
    prestito->inq_last_6mths; //Il numero di richieste di informazioni da parte dei creditori negli ultimi 6 mesi

    int monthsInTwoYears = (int)(credito->yearsOfCreditHistory * 12);
    prestito->delinq_2yrs = (credito->monthsSinceLastDelinquent > 30) ? (monthsInTwoYears / 30) : 0; //Il numero di volte in cui il debitore è stato in ritardo di oltre 30 giorni con i pagamenti negli ultimi 2 anni.

    prestito->pub_rec = credito->bankruptcies;
    prestito->not_fully_paid = (credito->currentLoanAmount != 0);
}

