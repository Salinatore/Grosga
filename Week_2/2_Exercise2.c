/**
 * @file 2_Exercise2.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 - unlimited attempts
 * @date 2023-10-05
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); //cambia ogni volta il numero random
    int min=0, max=0, scelta=0, tentativi=1;

    //controlla che l'intervallo inserito rispetti il vincolo 0<min<=max, altrimenti richiedi il numero
    while(min<0 || min>=max) {
        printf("\nInserisci un intervallo separato da una virgola (min,max): ");
        scanf("%d,%d", &min, &max);

        if(min<0 || min>=max) //Alert message
            printf("Il minimo non può essere più grande del massimo, rispetta il vincolo 0<min<=max!\n");
    }

    int MIN=min, MAX=max, n = rand() % (MAX-MIN+1) + MIN;

    //continua a ciclare se il numero è più grande o più piccolo
    while(scelta != 3) {
        printf("\nIl numero è %d?", n);

        printf("\nInserisci: 1 - se piu' piccolo, 2 - se piu' grande, 3 - se indovinato: ");
        scanf("%1d", &scelta); //inserisci il numero in base alla tua scelta

        if((n > MAX || n < MIN) && scelta != 3) { //stampa se il numero è fuori dal range
            printf("\n\nMi stai mentendo o ti sei dimenticato il numero!\n\n");
            return 0;
        }
        else if(n > min && scelta == 1) //trovo un numero più piccolo, imponendo il massimo del range il numero appena estratto
            MAX = n;
        else if(n < max && scelta == 2) //trovo un numero pù grande, imponendo il minimo del range il numero appena estratto
            MIN = n;
        else if(scelta == 3) {
            printf("\nHo indovinato con %d tentativi!", tentativi); //se indovino, stampo i tentativi e finisce il programma
            return 0;
        }

        n = (MAX+MIN)/2; //trovo un nuovo numero
        tentativi++; //aumento il contatore
    }
}