/*

Alessandro Gardini n. matricola: 0001114867
Filippo Greppi n. matricola:
Lorenzo Rossi n. matricola:

Exercise number: 1

*/

#include <stdio.h>

int main(){
    //declaration-->
    char c = -1;
    int i = 27, l;
    short int si = -1;
    long int li = -1;
    unsigned char uc = 1;
    unsigned int ui = 1;
    unsigned long ul = 1;
    float f = -1;
    double d = -1;
    long double ld = -1;

    //stampo variabili con le dimensioni che occupano
    printf("Stampo variabili con le dimensioni che occupano-->");
    printf("\nvalore:%c -- dimensione:%d", c, sizeof(c));
    printf("\nvalore:%d -- dimensione:%d", i, sizeof(i));
    printf("\nvalore:%d -- dimensione:%d", si, sizeof(si));
    printf("\nvalore:%ld -- dimensione:%d", li, sizeof(li));
    printf("\nvalore:%c -- dimensione:%d", uc, sizeof(uc));
    printf("\nvalore:%d -- dimensione:%d", ui, sizeof(ui));
    printf("\nvalore:%d -- dimensione:%d", ul, sizeof(ul));
    printf("\nvalore:%f -- dimensione:%d", f, sizeof(f));
    printf("\nvalore:%f -- dimensione:%d", d, sizeof(d));
    printf("\nvalore:%f -- dimensione:%d", ld, sizeof(ld));
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