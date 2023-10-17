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
#include <stdbool.h>

int main(){
    srand((unsigned int) time(NULL)); //initializing rand

    /** initializing user and pc and print them*/
    int user_array_width = -1, pc_array_width = -1;

    printf("Inserisci la grandezza del tuo array: ");
    scanf("%d", &user_array_width); //initializing width of user_array

    pc_array_width = rand() % 100 + 1; //array limited form 1 to 50
    printf("Grandezza array pc: %d  (valori all'interno saranno tra 0 e 49)\n", pc_array_width); //*

    int user[user_array_width], pc[pc_array_width];

    printf("\nInserisci i valori del tuo vettore-->\n");
    for(int i = 0; i < user_array_width; i++){
        printf("\t%d°: ", i);
        scanf("%d", &user[i]);
    }

    for(int i = 0; i < pc_array_width; i++){
        pc[i] = rand() % 50; //values inside pc are limited form 0 to 49
    }

    //printing pc and user array
    printf("\nPC vector--> ");
    for(int i = 0; i < pc_array_width; i++){
        printf("%d ", pc[i]);
    }

    printf("\nUser vector--> ");
    for(int i = 0; i < user_array_width; i++){
        printf("%d ", user[i]);
    }

    /** initializing intersection array (without repetition)*/
    int inter_array[user_array_width + pc_array_width], pos = 0; //max intersection array width
    bool inside = false;

    for(int i = 0; i < user_array_width; i++){
        for(int k = 0; k < pc_array_width; k++){
            if(user[i] == pc[k]){
                for(int j = 0; j < pos; j++){ //control if value already exist in the intersection array
                    if(user[i] == inter_array[j]){
                        inside = true;
                        break;
                    }
                    else continue; //continue cycle if value hasn't been found
                }
                if(inside == false){ //if the value wasn't already in the inter_array
                    inter_array[pos] = user[i]; //inserting new value in the inter_array
                    pos++;
                }
                inside = false;
            }
            else continue;
        }
    }

    printf("\nIntersection vector without repetition--> ");
    if(pos != 0){
        for(int i = 0; i < pos; i++)
            printf("%d ", inter_array[i]);
    }
    else
        printf("NULL");

    /** initializing intersection array (with repetition)*/
    int inter_array_rep[user_array_width + pc_array_width], rep = 0;

    for(int i = 0; i < pos; i++){
        for(int u = 0; u < user_array_width; u++){
            if(user[u] == inter_array[i]){
                inter_array_rep[rep] = user[u];
                rep++;
            }
        }
        for(int p = 0; p < pc_array_width; p++){
            if(pc[p] == inter_array[i]) {
                inter_array_rep[rep] = pc[p];
                rep++;
            }
        }
    }

    printf("\nIntersection vector with repetition--> ");
    if(rep != 0){
        for(int i = 0; i < rep; i++)
            printf("%d ", inter_array_rep[i]);
    }
    else
        printf("NULL");


    /** initializing union array (without repetition)*/
    int union_array[user_array_width + pc_array_width];
    pos = 0; //reinitializing pos for union_array
    bool already_in = false;

    for(int i = 0; i < user_array_width; i++){ //add user to union
        for(int k = 0; k <= pos; k++){
            if(user[i] == union_array[k]){
                already_in = true;
                break;
            }
        }
        if(already_in == false){
            union_array[pos] = user[i];
            pos++;
        }
        already_in = false;
    }

    for(int i = 0; i < pc_array_width; i++){ //add pc to union
        for(int k = 0; k <= pos; k++){ //control for repetition
            if(pc[i] == union_array[k]){
                already_in = true;
                break;
            }
        }
        if(already_in == false){
            union_array[pos] = pc[i];
            pos++;
        }
        already_in = false;
    }

    printf("\nUnion vector without repetition--> ");
    for(int i = 0; i < pos; i++)
        printf("%d ", union_array[i]);

    printf("\n\n");
    return 0;
}

