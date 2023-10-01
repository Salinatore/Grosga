/**
 * @file Esercizio2.c
 * @author Gardini Alessandro, Greppi Filippo, Rossi Lorenzo
 * @version 0.1
 * @date 2023-09-29
*/

#include <stdio.h>

int main() {
    float mi, gal;

    // ask for input
    printf("\nInserisci il numero di miglia percorse: ");
    scanf("%f", &mi);
    printf("\nInserisci il numero di galloni di benzina comsumati: ");
    scanf("%f", &gal);

    // miles per gallon
    float mpg = mi / gal;
    printf("\nLe miglia per galloni sono: %.2f", mpg);

    // conversion (miles per gallon to L/100Km)
    float lp100km = 235.215 / mpg;
    printf("\nLitri per 100km: %.3f", lp100km);

    printf("\n\n");
    return 0;
}
