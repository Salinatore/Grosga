/*

Alessandro Gardini n. matricola: 0001114867
Filippo Greppi n. matricola:
Lorenzo Rossi n. matricola:

Exercise number: 1

*/

#include <stdio.h>

int main(){
    //declaration-->
    char c;
    int i = 27, l = 5;
    short int si;
    long int li;
    unsigned char uc;
    unsigned int ui;
    unsigned long ul;
    float f;
    double d;
    long double ld;

    //stampo variabili con le dimensioni che occupano
    printf("Stampo variabili con le dimensioni che occupano-->");
    printf("\nvalore:%d -- dimensione:%d", c, sizeof(c));
    printf("\nvalore:%d -- dimensione:%d", i, sizeof(i));
    printf("\nvalore:%d -- dimensione:%d", si, sizeof(si));
    printf("\nvalore:%d -- dimensione:%d", li, sizeof(li));
    printf("\nvalore:%d -- dimensione:%d", uc, sizeof(uc));
    printf("\nvalore:%d -- dimensione:%d", ui, sizeof(ui));
    printf("\nvalore:%d -- dimensione:%d", ul, sizeof(ul));
    printf("\nvalore:%d -- dimensione:%d", f, sizeof(f));
    printf("\nvalore:%d -- dimensione:%d", d, sizeof(d));
    printf("\nvalore:%d -- dimensione:%d", ld, sizeof(ld));
    printf("\n\n");

    //stampo usando i vari modificatori e il numero dei caratteri che usano
    printf("Stampo usando i vari modificatori e il numero dei caratteri che usano-->");
    l = printf("\n %-d", i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n %+d", i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n % d", i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n %#d",i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n %0d", i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n %10d", i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n %.10d", i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n %ld", i);
    printf(" -- numero di caratteri: %d", l);

    return 0;
}