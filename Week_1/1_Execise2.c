/**
 * @file Esercizio2.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.2
 * @date 2023-10-03
*/

#include <stdio.h>

int main() {
    float mi, gal;
    const float mi_to_km = 1.609;
    const float gal_to_lit = 3.785;

    // ask for input
    printf("\nInserisci il numero di miglia percorse: ");
    scanf("%f", &mi);
    printf("\nInserisci il numero di galloni di benzina comsumati: ");
    scanf("%f", &gal);

    // miles per gallon
    float mpg = mi / gal;
    printf("\nLe miglia per galloni sono: %.2f", mpg);

    // conversion (miles per gallon to L/100Km)
    float lp100km = (gal * gal_to_lit) / (100 * mi * mi_to_km);
    printf("\nLitri per 100km: %.3f", lp100km);

    printf("\n\n");
    return 0;
}
