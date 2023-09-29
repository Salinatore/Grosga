/*

Alessandro Gardini n. matricola: 0001114867
Filippo Greppi n. matricola:
Lorenzo Rossi n. matricola:

Exercise number: 2

*/

#include <stdio.h>
#include <stdlib.h>

float converter(float mi_gal);

int main() {
    float mi, gal;

    printf("\nInserisci il numero di miglia percorse: ");
    scanf("%f", &mi);
    printf("\nInserisci il numero di galloni di benzina comsumati: ");
    scanf("%f", &gal);

    float mpg = mi/gal;
    printf("\nLe miglia per galloni sono: %.2f", mpg);

    float lp100km = converter(mpg);
    printf("\nLitri per 100km: %.3f", lp100km);

    printf("\n\n");
    system("pause");
    return 0;
}

float converter(float mi_gal) {
    return mi_gal * 235.2143;
}
