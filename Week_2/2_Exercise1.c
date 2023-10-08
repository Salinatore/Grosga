/*
* ESERCIZIO 1
* Scrivere un programma C che mostri l’utilizzo di tutti gli operatori studiati.#
* Il programma deve inoltre mostrare il comportamento scorretto che si ottiene utilizzando tipi non appropriati
* alla dimensione delle variabili,#
 *
* quello che si ottiene usando più operatori con side effect all’interno della stessa istruzione,#
 *
*  quello che si ottiene quando le regole di conversione implicita sono applicate #
* quando si supera il range dei valori disponibili per un tipo di dato.#
*
* Il programma deve poi mostrare l’utilizzo di tutte le funzioni matematiche della libreria math.h.
*
*/

#include <stdio.h>
#include <math.h>

int main() {
    int n, b =0, c= 1;
    float f, decimale;

    //lista operatori studiati
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

    n = (b++, c++);
    printf("\n%d", n);

    //casting
    decimale = f - (int)f;
    printf("\nStampa parte decimale: %f", decimale);

    //utilizzo tipi non appropriati alla dimensione delle variabil
    printf("\n%f", n);

    //più operatori con side effect
    n = 1;
    b = n*n++;
    printf("\n%d", b);

    //conversione implicita di variabile
    char h;
    int i;
    i = h;

    // si supera il range dei valori disponibili
    short int s;
    int x = 999999;
    s = x;
    printf("\n%d", s);

    //tutte funzioni della libreria math.h
    double r = 0.0, y = 2.25, o = 3.5;
    r = floor(y);
    printf("\n%f", r);
    r = ceil(y);
    printf("\n%f", r);
    r = fabs(y);
    printf("\n%f", r);
    r = log(y);
    printf("\n%f", r);
    r = log10(y);
    printf("\n%f", r);
    r = exp(y);
    printf("\n%f", r);
    r = sqrt(y);
    printf("\n%f", r);
    r = pow(o, y);
    printf("\n%f", r);

    printf("\n\n");
    return 0;
}
