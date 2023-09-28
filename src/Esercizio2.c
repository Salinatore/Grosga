/**
 * @file Esercizio2.c
 * @author Filo, Gardo, Rossi
 * @brief 
 * @version 0.1
 * @date 2023-09-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * ESERCIZIO 2
 * Scrivere un programma C che chieda all'utente di inserire il numero di miglia percorse e il numero di galloni di benzina consumati. 
 * Il programma deve poi calcolare e visualizzare il valore di miglia per gallone usando due cifre decimali. 
 * Successivamente, il programma deve convertire il valore miglia per gallone in litri per 100 km, come si usa per esprimere il consumo di carburante in Europa,
 * e visualizzare il risultato, usando 3 cifre decimali. Usare costanti simboliche per i due fattori di conversione. Commentare adeguatamente il programma.
 * 
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