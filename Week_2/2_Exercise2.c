/**
 * @file 2_Exercise2.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 - unlimited
 * @date 2023-10-06
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int min=-1, max=0, scelta=0;

    //controlla che l'intervallo inserito rispetti il vincolo 0<min<=max
    while(min>max || min<0) {
        printf("\nInserisci un intervallo separato da una virgola (min,max): ");
        scanf("%d,%d", &min, &max);

        if(min>max) /**Alert*/
            printf("Il minimo non può essere più grande del massimo, rispetta il vincolo 0<min<=max!\n");
        else if(min<0)
            printf("Il minimo non può essere sotto allo 0!\n");
    }

    int tentativi = 0, n = min + rand() % (max - min + 1); //estrai un numero random all'interno del range prestabilito

    while(scelta != 3) {
        printf("\nIl numero è %1d?", n); //stampa il numero estratto
        printf("\nInserisci 1 - se e' piu' grande, 2 - se e' piu' piccolo, 3 - se ho indovinato: ");
        scanf("%d", &scelta);

        /*Se il giocatore dice piu grande quando il numero è massimo o piu piccolo quando il numero è minimo, si interrompe*/
        if((scelta == 1 && n >= max) || (scelta == 2 && n <= min)) {
            printf("\n\nImpossibile, stai barando o ti sei scordat* il numero!\n\n");
            return 0;
        }
        else if(scelta == 1) {
            min = n + 1; //modifica il minimo portandolo al numero successivo dell'estratto
            n = (max+min) / 2; //estrai numo numero con la ricerca binaria
        }
        else if(scelta == 2) {
            max = n - 1; //modifica il massimo portandolo al numero precedente dell'estratto
            n = (max+min) / 2; //estrai numo numero con la ricerca binaria
        }
        tentativi++;
    }

    printf("\n\nHo indovinato con %d tentativi!", tentativi);

    printf("\n\n");
    return 0;
}