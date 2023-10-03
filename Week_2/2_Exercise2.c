/*
 * ESERCIZIO 2
 * L’utente pensa ad un numero e il computer lo deve indovinare compiendo le seguenti operazioni.
 * L’utente fissa un intervallo entro cui generare il valore da indovinare (min, max). Se i valori inseriti non rispettano il vincolo 0<min≤max, l’operazione di lettura va ripetuta
 * L’utente pensa ad un numero compreso tra min e max. (QUI)
 * Il programma cerca di indovinare la scelta dell’utente e propone un numero. A seconda della situazione l’utente deve dire al programma se
 * o il numero da indovinare è più piccolo;
 * il numero da indovinare è più grande; ha indovinato.
 * Scrivere una versione di programma in cui non c'è limite al numero di tentativi che l’utente può fare per indovinare il numero e scriverne un'altra in cui invece viene posto tale limite.
 * Il programma deve stampare il numero di tentativi fatti.
 */

#include <stdio.h>
#include <stdio.h>

int main() {

    int n, min=0, max=0, max_try=-1;

    //controlla che l'intervallo inserito rispetti il vincolo 0<min<=max
    while(min<0 || min>=max) {
        printf("\nInserisci un intervallo separato da una virgola (min,max): ");
        scanf("%d,%d", &min, &max);

        if(min<0 || min>=max)
            printf("  Il minimo non può essere più grande del massimo, rispetta il vincolo 0<min<=max!!\n");
    }
    //controlla che n sia all'interno dell'intervallo, altrimenti richiedi il valore
    while(n>=min && n>=max) {
        printf("\nInserisci il numero da indovinare: ");
        scanf("%d", &n);

        if(n>=min && n>=max)
            printf("  Rispetta l'intervallo: %d<=numero<=%d!!\n", min, max);
    }

    //controlla se i tentativi siano maggiori di 0
    while(max_try<0){
        printf("\nInserisci i tentativi massimi: ");
        scanf("%d", &max_try);

        if(max_try<0){
            printf("  Inserisci un numero positivo!!\n");
        }
    }

    do{
        max_try--;
        printf("il tuo numero è %d", )
    } while(max_try>=0);

    printf("\n\n");
    return 0;
}