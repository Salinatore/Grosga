/**
 * @file 5_Exercise2.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 - no string.h
 * @date 16/10/23
*/

#include <stdio.h>
#include "stdbool.h"

#define MAX 30

int strlenght(char str[]);

int main() {
    char str1[MAX+1], str2[MAX+1];
    const char cambio = '*';
    bool check;

    printf("\nInserisci la prima parola (massimo 30 caratteri): ");
    scanf("%30s", str1); //leggi solo i primi 30 caratteri
    printf("\nInserisci la seconda parola (massimo 30 caratteri): ");
    scanf("%30s", str2); //leggi solo i primi 30 caratteri

    int len1 = strlenght(str1), len2 = strlenght(str2);
    int i = 0, k = 0;

    while(i < len1) {
        check = true;

        for(int j = 0; j < len2 && check == true; j++)
            if(str1[i + j] != str2[j])
                check = false; //la stringa 2 è inclusa nella prima => interrompi ciclo for

        if(check) { //modifica se non entra nell'if
            str1[k++] = cambio;
            i += len2;
        } else
            str1[k++] = str1[i++]; //sposta
    }

    str1[k] = '\0'; //concludi la parola
    printf("\nRISULTATO: %s", str1);

    printf("\n\n");
    return 0;
}

/** Restituisce la lunghezza di una stringa **/
int strlenght(char str[]) {
    int i = 0;
    while(str[i] != '\0')
        i++;

    return i;
}