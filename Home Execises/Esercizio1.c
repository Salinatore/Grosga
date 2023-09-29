/*
 * @file Esercizio1.c
 * @author Filo, Gardo, Rossi
 * @brief 
 * @version 0.1
 * @date 2023-09-25
 * 
 * @copyright Copyright (c) 2023
 *
 */

/*
* %TODO
* Scrivere un programma C che dichiari una variabile per ogni tipo studiato (usando anche i qualificatori short, long, signed e unsigned), 
* ne stampi il valore e l’occupazione di memoria in byte. Utilizzare TUTTI gli argomenti della funzione printf() studiati e TUTTE le diverse varianti 
* (modificatore, campoMinimo, precisione, modificatoreLunghezza). 
* Per ogni chiamata alla funzione printf(), mostrare a video anche il numero di caratteri che quest’ultima ha stampato. 
* Stampare inoltre il valore minimo e il valore massimo ammissibile per ogni tipo utilizzato. Commentare adeguatamente il programma.
*
*/

#include <stdio.h>
#include <stdlib.h>


#include <stdio.h>

int main() {
    char c;
    int i=27, l=5;
    short int si;
    long int li;
    unsigned char uc;
    unsigned int ui;
    unsigned long ul;
    float f;
    double d;
    long double ld;

    printf("\n valore:%d dimensione:%d", c, sizeof(c) );
    printf("\nvalore:%d dimensione:%d", i, sizeof(i) );
    printf("\nvalore:%d dimensione:%d", si, sizeof(si) );
    printf("\nvalore:%d dimensione:%d", li, sizeof(li) );
    printf("\nvalore:%d dimensione:%d", uc, sizeof(uc) );
    printf("\nvalore:%d dimensione:%d", ui, sizeof(ui) );
    printf("\nvalore:%d dimensione:%d", ul, sizeof(ul) );
    printf("\nvalore:%d dimensione:%d", f, sizeof(f) );
    printf("\nvalore:%d dimensione:%d", d, sizeof(d) );
    printf("\nvalore:%d dimensione:%d", ld, sizeof(ld) );
    l = printf("\n %-d,numero di caratteri %d", i, l ); //da finire
    l = printf("\n %+d,numero di caratteri %d", i, l);
    l = printf("\n % d", i, l);
    printf("\n %#d");
    printf("\n %0d");
    printf("\n %10d");
    printf("\n %.10d");
    printf("\n %ld");
    return 0;
}