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

bool aspettiamo(Ristorante *data, int length);
int get_filelength(const char *nomeFile);
void print_data(Ristorante *data, int data_length);
Ristorante get_info(Ristorante *data);

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
            if(path[strlen(path) - 1] == '\n')
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
        if(dataset == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        int i = 0;
        char ch[MAX];
        while(fscanf(file, "%hhu %hhu %hhu %hhu %u %s %hhu %hhu %s %u",
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
        fclose(file);
    } else {
        //da terminale
        int n;
        printf("\nInserisci il numero di righe: ");
        fflush(stdin);
        scanf("%d", &n);

        size = n;
        dataset = (Ristorante *)malloc(size * sizeof(Ristorante));
        if(dataset == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < n; ++i) {
            get_info(&dataset[i]);
        }
    }

    do {
        print_data(dataset, size);

        /** TEST **/
        printf(H1 "\n\nTESTING" RESET);
        size++;
        dataset = (Ristorante *)realloc(dataset, size * sizeof(Ristorante));
        if(dataset == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        get_info(&dataset[size-1]); //add new info


        bool risultato = aspettiamo(dataset, size);
        if(risultato)
            printf("\nAspettiamo");
        else
            printf("\nCambiamo ristorante");
        char result;
        printf("\nIn risultato e' corretto (Y/n)? ");
        fflush(stdin);
        scanf("%1c", result);

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

bool aspettiamo(Ristorante *data, int length) {
    Ristorante h = data[0];

    for(int i = 1; i < length-1; ++i) {
        if(h.alternativa != data[i].alternativa)
           h.alternativa = NULL;
        if(h.bar != data[i].bar)
            h.bar = NULL;
        if(h.giorno != data[i].giorno)
            h.giorno = NULL;
        if(h.fame != data[i].fame)
            h.fame = NULL;
        if(h.affollato != data[i].affollato)
            h.affollato = (unsigned int) NULL;
        if(h.prezzo != data[i].prezzo)
            h.prezzo = (unsigned int) NULL;
        if(h.pioggia != data[i].pioggia)
            h.pioggia = NULL;
        if(h.prenotazione != data[i].prenotazione)
            h.prenotazione = NULL;
        if (h.tipo != data[i].prenotazione)
            *h.tipo = (char)NULL;
        if(h.attesa_stimata != data[i].attesa_stimata)
            h.attesa_stimata = (unsigned int) NULL;
    }
    int count = 0;
    if(h.alternativa == data[length-1].alternativa)
        count++;
    if(h.bar == data[length-1].bar)
        count++;
    if(h.giorno == data[length-1].giorno)
        count++;
    if(h.fame == data[length-1].fame)
        count++;
    if(h.affollato == data[length-1].affollato)
        count++;
    if(h.prezzo == data[length-1].prezzo)
        count++;
    if(h.pioggia == data[length-1].pioggia)
        count++;
    if(h.prenotazione == data[length-1].prenotazione)
        count++;
    if(strcmp(h.tipo, data[length-1].tipo) == 0)
        count++;
    if(h.attesa_stimata == data[length-1].attesa_stimata)
        count++;

    if(count > 3)
        return true;
    return false;
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

Ristorante get_info(Ristorante *data) {
    printf("\nC’e' un ristorante nei paraggi (1: vero, 0: falso)? ");
    fflush(stdin);
    scanf("%1d", &data->alternativa);

    printf("\nIl ristorante ha un’area bar per l’attesa (1: vero, 0: falso)? ");
    fflush(stdin);
    scanf("%1d", &data->bar);

    printf("\nGiorno della settimana in cui si vuole andare al ristorante (1 se venerdì oppure sabato, 0 diversamente)? ");
    fflush(stdin);
    scanf("%1d", &data->giorno);

    printf("\nSiamo affamati (1: vero, 0: falso)? ");
    fflush(stdin);
    scanf("%1d", &data->fame);

    printf("\nQuante persone sono presenti nel ristorante (0:nessuno, 1:qualcuno, 2:pieno)? ");
    fflush(stdin);
    scanf("%1d", &data->affollato);

    char costo[MAX];
    printf("\nCategoria di costo del ristorante ($, $$, $$$)? ");
    fflush(stdin);
    scanf("%s", costo);

    if(strcmp("$", costo) == 0) {
        data->prezzo = 1;
    } else if(strcmp("$$", costo) == 0) {
        data->prezzo = 2;
    } else if(strcmp("$$$", costo) == 0) {
        data->prezzo = 3;
    }

    printf("\nFuori sta piovendo (1: vero, 0: falso)? ");
    fflush(stdin);
    scanf("%1d", &data->pioggia);

    printf("\nAbbiamo prenotato (1: vero, 0: falso)? ");
    fflush(stdin);
    scanf("%1d", &data->prenotazione);

    printf("\nTipo di ristorante (italiano, francese, fast-food, thai)? ");
    fflush(stdin);
    fgets(data->tipo, sizeof(data->tipo), stdin);
    if (data->tipo[strlen(data->tipo) - 1] == '\n')
        data->tipo[strlen(data->tipo) - 1] = '\0';

    printf("\nStima del tempo di attesa? ");
    fflush(stdin);
    scanf("%d", &data->attesa_stimata);
}