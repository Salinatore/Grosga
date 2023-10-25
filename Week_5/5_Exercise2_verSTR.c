/**
 * @file 5_Exercise2_verSTR.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 
 * @date 23/10/23
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char p1[31], p2[31], t;
    int l1, l2, c = 0, y;
    printf("inserire parola 1: \n ");
    scanf("%30s", p1);
    printf("inserire parola 2: \n ");
    scanf("%30s", p2);
    l1 = strlen (p1);
    l2 = strlen (p2);
    for(int i = 0; i <= l1 - l2; i++) {
            if (strncmp(p1 + i, p2, l2) == 0){
                p1[i] = '*';
                for(int j = 1; j < l2; j++){
                    p1[i+j] = ' ';
                }
        }

    }

 for(int i = 0; i < l1; i++){
     if(p1[i] != ' '){
         p1[c] = p1[i];
         c++;
     }
 }
 p1[c] = '\0';

        for(int i = 0; i < l1; i++){
        printf("%c", p1[i]);
    }
}

