/**
 * @file 8_Exercise1.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 
 * @date 28/11/23
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256
#define WARNING "\033[31m"
#define RESET "\033[0m"
#define PATH "\033[36m"
#define H1 "\e[1;5m"

typedef struct {
    bool alternativa; //c’è un ristorante nei paraggi (vero, falso)
    bool bar; //il ristorante ha un’area bar per l’attesa (vero, falso)
    bool giorno; //giorno della settimana in cui si vuole andare al ristorante (vero se venerdì oppure sabato, falso diversamente)
    bool fame; //siamo affamati (vero, falso)
    unsigned int affollato; //quante persone sono presenti nel ristorante (0:nessuno, 1:qualcuno, 2:pieno)
    unsigned int prezzo; //categoria di costo del ristorante ($, $$, $$$)
    bool pioggia; //fuori sta piovendo (vero, falso)
    bool prenotazione; //abbiamo prenotato (vero, falso)
    char tipo[MAX]; //tipo di ristorante (italiano, francese, fast-food, thai)
    unsigned int attesa_stimata; //stima del tempo di attesa (<10, 10-29, 30-60, >60)
} Ristorante;

bool aspettiamo(Ristorante);
int get_filelength(const char *nomeFile);
void print_data(Ristorante *data, int data_length);

int main(int argc, char *argv[]) {
    char retry;
    Ristorante *dataset;
    int scelta, size;

    do {
        printf("\n1: File\n2: Terminale\nCome vuoi inserire i dati per il training: ");
        fflush(stdin);
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

        //choose file
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
                fflush(stdin);
                break;
            } else
                printf("Impossibile trovare il file: " PATH "%s\n" RESET, path);
        } while(file == NULL);

        size = get_filelength(path);
        dataset = (Ristorante *)malloc( size * sizeof(Ristorante));
        int i = 0;
        char ch[MAX];
        while (fscanf(file, "%hhu %hhu %hhu %hhu %u %s %hhu %hhu %s %u",
                      (unsigned char*)&dataset[i].alternativa,
                      (unsigned char*)&dataset[i].bar,
                      (unsigned char*)&dataset[i].giorno,
                      (unsigned char*)&dataset[i].fame,
                      &dataset[i].affollato,
                      ch,
                      (unsigned char*)&dataset[i].pioggia,
                      (unsigned char*)&dataset[i].prenotazione,
                      dataset[i].tipo,
                      &dataset[i].attesa_stimata) == 10) {
            if(strcmp("$", ch) == 0)
                dataset[i].prezzo = 1;
            else if(strcmp("$$", ch) == 0)
                dataset[i].prezzo = 2;
            else if(strcmp("$$$", ch) == 0)
                dataset[i].prezzo = 3;
            i++;
        }
    } else {
        //da terminale
        int n;
        printf("\nInserisci il numero di righe: ");
        fflush(stdin);
        scanf("%d", &n);

        size = n;
        dataset = (Ristorante *)malloc(size * sizeof(Ristorante));
        for(int i = 0; i < n; ++i) {
            printf("\nC’e' un ristorante nei paraggi (1: vero, 0: falso)? ");
            fflush(stdin);
            scanf("%1d", &dataset[i].alternativa);

            printf("\nIl ristorante ha un’area bar per l’attesa (1: vero, 0: falso)? ");
            fflush(stdin);
            scanf("%1d", &dataset[i].bar);

            printf("\nGiorno della settimana in cui si vuole andare al ristorante (1 se venerdì oppure sabato, 0 diversamente)? ");
            fflush(stdin);
            scanf("%1d", &dataset[i].giorno);

            printf("\nSiamo affamati (1: vero, 0: falso)? ");
            fflush(stdin);
            scanf("%1d", &dataset[i].fame);

            printf("\nQuante persone sono presenti nel ristorante (0:nessuno, 1:qualcuno, 2:pieno)? ");
            fflush(stdin);
            scanf("%1d", &dataset[i].affollato);

            char costo[3];
            printf("\nCategoria di costo del ristorante ($, $$, $$$)? ");
            fflush(stdin);
            scanf("%c", costo);

            if(strcmp("$", costo) == 0) {
                dataset[i].prezzo = 1;
            } else if(strcmp("$$", costo) == 0) {
                dataset[i].prezzo = 2;
            } else if(strcmp("$$$", costo) == 0) {
                dataset[i].prezzo = 3;
            }

            printf("\nFuori sta piovendo (1: vero, 0: falso)? ");
            fflush(stdin);
            scanf("%1d", &dataset[i].pioggia);

            printf("\nAbbiamo prenotato (1: vero, 0: falso)? ");
            fflush(stdin);
            scanf("%1d", &dataset[i].prenotazione);

            printf("\nTipo di ristorante (italiano, francese, fast-food, thai)? ");
            fflush(stdin);
            fgets(dataset[i].tipo, sizeof(dataset[i].tipo), stdin);
            if (dataset[i].tipo[strlen(dataset[i].tipo) - 1] == '\n')
                dataset[i].tipo[strlen(dataset[i].tipo) - 1] = '\0';

            printf("\nStima del tempo di attesa? ");
            fflush(stdin);
            scanf("%d", &dataset[i].attesa_stimata);
        }
    }

    do {
        print_data(dataset, size);
        /** TEST **/
        printf(H1 "\n\nTESTING" RESET);

        /*
        bool risultato = aspettiamo();
        if(risultato)
            printf("\nAspettiamo");
        else
            printf("\nCambiamo ristorante");
        */




        do {
            printf("\nVuoi riprovare (Y/n)? ");
            fflush(stdin);
            scanf(" %1c", &retry);
            if(retry != 'y' && retry != 'Y' && retry != 'N' && retry != 'n') //alert
                printf("Inserisci Y (si) o n (no)\n");
        } while(retry != 'y' && retry != 'Y' && retry != 'N' && retry != 'n');
    } while(retry != 'n' && retry != 'N');

    free(dataset);
    printf("\nTerminato con successo ...\n");
    return EXIT_SUCCESS;
}

bool aspettiamo(Ristorante) {
    bool response;

    return response;
}

int get_filelength(const char *nomeFile) {
    FILE *filename = fopen(nomeFile, "r");
    if (filename == NULL) {
        fprintf(stderr, "Impossibile aprire il file %s.\n", nomeFile);
        return -1;
    }

    int conteggio = 0;
    char carattere;

    while ((carattere = fgetc(filename)) != EOF) {
        if (carattere == '\n') {
            conteggio++;
        }
    }

    fclose(filename);
    return conteggio;
}

void print_data(Ristorante *data, int data_length) {
    for (int i = 0; i < data_length; ++i)
        printf("\n%d %d %d %d %d %d %d %d %s %d", data[i].alternativa, data[i].bar, data[i].giorno, data[i].fame,
               data[i].affollato, data[i].prezzo, data[i].pioggia, data[i].prenotazione, data[i].tipo,
               data[i].attesa_stimata);
}