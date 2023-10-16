/**
 * @file 4_Exercise1.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 
 * @date 16/10/23
*/

/**
 * @ESERCIZIO1
 * Siano dati due vettori di interi di lunghezza differente.
 * Scrivere un programma C che inserisca i valori da tastiera e che lo faccia anche generandoli in maniera pseudo-casuale.
 * Il programma deve poi generare un terzo vettore contenente l’intersezione tra i due vettori di input.
 * Implementare sia la variante in cui le ripetizioni di un elemento nei vettori di input vengono riportate anche nel vettore risultato,
 * sia quella in cui le ripetizioni non sono inserite nel risultato. Implementare poi la generazione di un quarto vettore contenente
 * l'unione dei due vettori di input. Il programma deve inoltre stampare gli indirizzi di memoria occupati dagli elementi dei vettori e
 * la loro dimensione totale in termini di numero di byte.
 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

int main() {
    srand((unsigned int) time(NULL)); //initializing rand

    int user_array_width = -1, pc_array_width = -1;

    printf("Inserisci la grandezza del tuo array: ");
    scanf("%d", &user_array_width); //initializing width of user_array

    pc_array_width = (rand() % user_array_width) + 1; //using the width of the user array to limit the pc array + 1

    int user[user_array_width], pc[pc_array_width];

    /** initializing user and pc*/
    printf("\nInserisci i valori del tuo vettore-->\n");
    for(int i = 0; i < user_array_width; i++){
        printf("\t%d°: ", i);
        scanf("%d", &user[i]);
    }

    for(int i = 0; i < pc_array_width; i++){
        pc[i] = rand() % 100; //values inside pc are limited form 0 to 99
    }

    /** initializing intersection array */
    int max_width = -1;

    if(user_array_width > pc_array_width){
        max_width = user_array_width;

    }
    else{
        max_width = pc_array_width;
    }


    if()

    /** initializing sum array*/

    printf("\n\n");
    return 0;
}

int