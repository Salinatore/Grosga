/**
 * @file 8_Exercise1.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 
 * @date 28/11/23
*/

#include <stdio.h>
#include <stdbool.h>
#include "string.h"

#define MAX 256
#define WARNING "\x1b[31m"
#define RESET "\x1b[0m"
#define PATH "\x1b[36m"
#define H1 "\e[1;5m"

typedef struct {
    bool alternativa; //c’è un ristorante nei paraggi (vero, falso)
    bool bar; //il ristorante ha un’area bar per l’attesa (vero, falso)
    bool giorno; //giorno della settimana in cui si vuole andare al ristorante (vero se venerdì oppure sabato, falso diversamente)
    bool fame; //siamo affamati (vero, falso)
    unsigned int affollato; //quante persone sono presenti nel ristorante (0:nessuno, 1:qualcuno, 2:pieno)
    char prezzo[MAX]; //categoria di costo del ristorante ($, $$, $$$)
    bool pioggia; //fuori sta piovendo (vero, falso)
    bool prenotazione; //abbiamo prenotato (vero, falso)
    char tipo[MAX]; //tipo di ristorante (italiano, francese, fast-food, thai)
    unsigned int attesa_stimata; //stima del tempo di attesa (<10, 10-29, 30-60, >60)
} Ristorante;

bool aspettiamo(Ristorante);

int main() {
    char retry;
    do {
        int scelta;
        do {
            printf("\n1: File\n2: Terminale\nCome vuoi inserire i dati: ");
            scanf("%1d", &scelta);
            if(scelta != 1 && scelta != 2)
                printf("Inserisci un'opzione valida!\n");
        } while(scelta != 1 && scelta != 2);

        /** TRAINING **/
        printf(H1 "\nTRAINING" RESET);
        if(scelta == 1) {
            //da file
            char path[MAX];
            FILE *file;

            do {
                printf(WARNING "\nIl file deve riportare i valori separati da uno spazio e avere un'estensione .txt" RESET);

                printf("\nInserisci il path del file .txt ('exit' per terminare): ");
                fflush(stdin);
                fgets(path, sizeof(path), stdin);

                //remove \n
                if (path[strlen(path) - 1] == '\n')
                    path[strlen(path) - 1] = '\0';

                if(strcmp("exit", path) == 0) {
                    fclose(file);
                    printf("\nTerminato con successo ...");
                    return 0;
                }

                if((file = fopen(path, "r")) != NULL) {
                    printf("Utilizzo il file: " PATH "%s\n" RESET, path);
                    break;
                } else {
                    printf("Impossibile trovare il file: " PATH "%s\n" RESET, path);
                }
            } while(file == NULL);

            //TODO read file


            fclose(file);
        } else {
            //da terminale
            int n;
            printf("\nInserisci il numero di");
            for (int i = 0; i < n; ++i) {

            }
        }

        /** TEST **/
        printf(H1 "\nTESTING" RESET);


        /*
        bool risultato = aspettiamo();
        if(risultato)
            printf("\nAspettiamo");
        else
            printf("\nCambiamo ristorante");
        */
        do {
            printf("\nVuoi riprovare (Y/n)? ");
            scanf(" %1c", &retry);
            if(retry != 'y' && retry != 'Y' && retry != 'N' && retry != 'n') //alert
                printf("Inserisci Y (si) o n (no)\n");
        } while(retry != 'y' && retry != 'Y' && retry != 'N' && retry != 'n');
    } while(retry != 'n' && retry != 'N');

    printf("\nTerminato con successo ...");
    return 0;
}

bool aspettiamo(Ristorante) {
    bool response;

    return response;
}
