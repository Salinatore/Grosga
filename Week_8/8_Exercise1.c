/**
 * @file 8_Exercise1.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 
 * @date 28/11/23
*/

#include <stdio.h>
#include "stdbool.h"
#define MAX 256

struct ristorante {
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
};

bool aspettiamo(struct ristorante);

int main() {
    int scelta;
    do {
        printf("\n1: File\n2: Terminale\nCome vuoi inserire i dati:");
        scanf("%1d", &scelta);
        if(scelta != 1 && scelta != 2)
            printf("Inserisci un'opzione valida!\n");
    } while(scelta != 1 && scelta != 2);

    if(scelta == 1) {
        //da file
    } else {
        //da terminale

    }


    printf("\n\n");
    return 0;
}
