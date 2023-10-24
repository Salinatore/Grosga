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
    char p1[30], p2[30], t;
    int l1, l2, c;
    printf("inserire parola 1: \n ");
    scanf("%s", p1);
    printf("inserire parola 2: \n ");
    scanf("%s", p2);
    l1 = strlen (p1);
    l2 = strlen (p2);
    for(int i = 0; i < l1 - l2; i++){
        c = 0;
        for(int j = 0; j < l2; j++){
            if(p1[i+j] == p2[j]) c++;
        }
        if(c == l2 ){
            p1[i] = '*';
            for(int k = 1; k < l2; k++) {
                p1[k + i] = ' ';
            }
        }
    }
    for(int i = 1; i < l1; i++){
        if(p1[i - 1] == ' '){
            p1[i - 1] = p1[i];
            p1[i] = ' ';
            i =
        }
    }
    for(int i = 0; i < l1; i++){
        printf("%c", p1[i]);
    }
}

