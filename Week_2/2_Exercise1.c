/*
* ESERCIZIO 1
* Scrivere un programma C che mostri l’utilizzo di tutti gli operatori studiati.
* Il programma deve inoltre mostrare il comportamento scorretto che si ottiene utilizzando tipi non appropriati alla dimensione delle variabili, quello che si ottiene usando più operatori con side
* effect all’interno della stessa istruzione, quello che si ottiene quando le regole di conversione implicita sono applicate e quando si supera il range dei valori disponibili per un tipo di dato.
*
* Il programma deve poi mostrare l’utilizzo di tutte le funzioni matematiche della libreria math.h.
*
*/

#include <stdio.h>
#include <math.h>

int main() {
    int n;
    float f, decimale;

    n = 3;
    printf("\n%d", n);

    n++;
    printf("\n%d", n);

    n--;
    printf("\n%d", n);

    n += 3;
    printf("\n%d", n);

    n -= 30;
    printf("\n%d", n);

    n *= -100;
    printf("\n%d", n);

    n /= 3;
    printf("\n%d", n);

    //casting
    decimale = f - (int)f;
    printf("\n%f", f);


    // stampa delle funzioni matemtiche di math.h
    printf("\nRadice");


    printf("\n\n");
    return 0;
}

void get_libraryFunction() {

}
