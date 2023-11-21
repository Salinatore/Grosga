#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Definizione della struttura per rappresentare i dati di ciascun prestito
struct Loan {
    int credit_policy;
    char purpose[50];
    float int_rate;
    float installment;
    float log_annual_inc;
    float dti;
    int fico;
    float days_with_cr_line;
    float revol_bal;
    float revol_util;
    int inq_last_6mths;
    int delinq_2yrs;
    int pub_rec;
    int not_fully_paid;
};

// Funzione per leggere i dati da un file CSV
void readCSV(const char *filename, struct Loan **loans, int *datasetSize) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Errore nell'apertura del file");
        exit(EXIT_FAILURE);
    }

    // Conta il numero di righe nel file (presumendo che ogni riga sia un record)
    *datasetSize = 0;
    char line[1024];  // Assumiamo che ogni riga sia più corta di 1024 caratteri
    while (fgets(line, sizeof(line), file) != NULL) {
        (*datasetSize)++;
    }

    // Torna all'inizio del file
    rewind(file);

    // Alloca la memoria per memorizzare i dati
    *loans = (struct Loan *)malloc(*datasetSize * sizeof(struct Loan));

    // Leggi i dati dal file
    for (int i = 0; i < *datasetSize; i++) {
        fgets(line, sizeof(line), file);

        // Usa sscanf per estrarre i dati dalla riga del file CSV
        sscanf(line, "%d,%49[^,],%f,%f,%f,%f,%d,%f,%f,%f,%d,%d,%d,%d",
               &(*loans)[i].credit_policy, (*loans)[i].purpose, &(*loans)[i].int_rate,
               &(*loans)[i].installment, &(*loans)[i].log_annual_inc, &(*loans)[i].dti,
               &(*loans)[i].fico, &(*loans)[i].days_with_cr_line, &(*loans)[i].revol_bal,
               &(*loans)[i].revol_util, &(*loans)[i].inq_last_6mths, &(*loans)[i].delinq_2yrs,
               &(*loans)[i].pub_rec, &(*loans)[i].not_fully_paid);
    }

    fclose(file);
}

// Funzione per dividere il dataset in addestramento e test
void splitDataset(struct Loan *originalDataset, int datasetSize, struct Loan **trainingSet, int *trainingSetSize, struct Loan **testSet, int *testSetSize, float testFraction) {
    // Calcola il numero di elementi da utilizzare per il test
    int testSize = (int)(datasetSize * testFraction);

    // Alloca memoria per i set di addestramento e test
    *trainingSet = (struct Loan *)malloc((datasetSize - testSize) * sizeof(struct Loan));
    *testSet = (struct Loan *)malloc(testSize * sizeof(struct Loan));

    // Copia i dati di addestramento e test dai dati originali
    memcpy(*trainingSet, originalDataset, (datasetSize - testSize) * sizeof(struct Loan));
    memcpy(*testSet, originalDataset + (datasetSize - testSize), testSize * sizeof(struct Loan));

    // Imposta le dimensioni dei set di addestramento e test
    *trainingSetSize = datasetSize - testSize;
    *testSetSize = testSize;
}

// Funzione per calcolare la distanza euclidea tra due prestiti
float calculateEuclideanDistance(struct Loan loan1, struct Loan loan2) {
    // Implementazione semplificata della distanza euclidea
    return sqrt(pow(loan1.int_rate - loan2.int_rate, 2) +
                pow(loan1.installment - loan2.installment, 2) +
                pow(loan1.pub_rec - loan2.pub_rec, 2));
}

// Funzione per predire se un prestito sarà rimborsato utilizzando l'algoritmo KNN
int predictLoanRepayment(struct Loan testLoan, struct Loan *trainingSet, int k, int datasetSize) {
    // Array per memorizzare le distanze tra il prestito di test e quelli di addestramento
    float distances[datasetSize];

    // Calcolare le distanze e memorizzarle nell'array
    for (int i = 0; i < datasetSize; i++) {
        distances[i] = calculateEuclideanDistance(testLoan, trainingSet[i]);
    }

    // Trovare gli indici dei k vicini più prossimi
    for (int i = 0; i < k; i++) {
        int minIndex = i;
        for (int j = i + 1; j < datasetSize; j++) {
            if (distances[j] < distances[minIndex]) {
                minIndex = j;
            }
        }

        // Scambiare le distanze e gli indici
        float tempDistance = distances[i];
        distances[i] = distances[minIndex];
        distances[minIndex] = tempDistance;

        struct Loan tempLoan = trainingSet[i];
        trainingSet[i] = trainingSet[minIndex];
        trainingSet[minIndex] = tempLoan;
    }

    // Contare le classificazioni dei k vicini più prossimi
    int countClass0 = 0;
    int countClass1 = 0;
    for (int i = 0; i < k; i++) {
        if (trainingSet[i].not_fully_paid == 0) {
            countClass0++;
        } else {
            countClass1++;
        }
    }

    // Classificare il prestito di test in base alla maggioranza dei vicini più prossimi
    return (countClass0 > countClass1) ? 0 : 1;
}

// Funzione per valutare le previsioni sull'insieme di test
float evaluatePredictions(struct Loan *testSet, int testSetSize, struct Loan *trainingSet, int k, int trainingSetSize) {
    int correctPredictions = 0;

    for (int i = 0; i < testSetSize; i++) {
        int predictedClass = predictLoanRepayment(testSet[i], trainingSet, k, trainingSetSize);

        // Confronta la previsione con il vero risultato
        if (predictedClass == testSet[i].not_fully_paid) {
            correctPredictions++;
        }
    }

    // Calcola e restituisci la percentuale di successo
    return ((float)correctPredictions / testSetSize) * 100.0;
}

int main() {
    // Dichiarare un vettore per memorizzare i dati dei prestiti
    struct Loan *loans;
    int datasetSize = 0;

    // Leggi i dati dal file CSV
    readCSV("/Users/greppifilippo/Grosga/Week_7/loan_data.csv", &loans, &datasetSize);

    // Divide il dataset in addestramento e test
    struct Loan *trainingSet;
    int trainingSetSize;
    struct Loan *testSet;
    int testSetSize;
    float testFraction = 0.25; // Modifica questa variabile in base alla percentuale desiderata per il test
    splitDataset(loans, datasetSize, &trainingSet, &trainingSetSize, &testSet, &testSetSize, testFraction);

    // Utilizzare l'algoritmo KNN per prevedere se il prestito sarà rimborsato
    int k = 5;  // Scegliere un valore appropriato per k
    float accuracy = evaluatePredictions(testSet, testSetSize, trainingSet, k, trainingSetSize);

    // Stampare la percentuale di successo
    printf("Percentuale di successo sull'insieme di test: %.2f%%\n", accuracy);

    // Liberare la memoria allocata per gli array di addestramento e test
    free(trainingSet);
    free(testSet);
    free(loans);

    return 0;
}
