/**
 * @file 4_Exercise2.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 
 * @date 16/10/23
*/

/**
 * @ESERCIZIO2
 * Scrivete un programma che generi una “passeggiata aleatoria” (random walk) in un array bidimensionale di dimensione 10×10.
 * L’array sarà riempito di caratteri (inizialmente da punti). Il programma dovrà muoversi di elemento in elemento spostandosi ogni volta
 * di un passo in direzione su, giù, destra o sinistra. Gli elementi visitati andranno etichettati con le lettere dalla A alla Z,
 * nell’ordine in cui vengono visitati. E’ importante controllare ad ogni passo che la passeggiata non esca dall’array e che non ritorni
 * su posizioni già visitate. Quando si verifica una di queste condizioni, provare le altre direzioni.
 * Se tutte e quattro le direzioni sono bloccate, il programma deve terminare.
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    srand(time(NULL));
    char array[10][10], lettere = 'A';
    int x = 0, y = 0, d, f= 0;
    for (int i = 0; i < 10; i++){
        for(int u = 0; u < 10; u++){
            array[i][u] = '.';
        }
    }
    for (int i = 0; i < 10; i++){
        for(int u = 0; u < 10; u++){
           printf(" %c", array[i][u]);
        }
        printf("\n");
    }
    printf("\n");
    array[0][0] = lettere;
    lettere ++;
    do{
        d = rand() % 4;
        if( d == 0 && x+1 < 10 && array[x+1][y] == '.'){
            x++;
            array[x][y] = lettere;
            lettere++;

        }
        if( d == 1 && y-1 >= 0 && array[x][y-1] == '.'){
            y--;
            array[x][y] = lettere;
            lettere++;

        }
        if( d == 2 && x-1 >= 0 && array[x-1][y] == '.'){
            x--;
            array[x][y] = lettere;
            lettere++;

        }
        if( d == 3 && y+1 < 10 && array[x][y+1] == '.'){
            y++;
            array[x][y] = lettere;
            lettere++;

        }
        if(lettere > 'Z') break;
        if(array[x+1][y] != '.' || x+1 >= 10){
            if(array[x-1][y] != '.' || x-1 < 0){
               if(array[x][y+1] != '.' || y+1 >= 10){
                   if(array[x][y-1] != '.' || y-1 < 0){
                       break;
                   }
               }
            }
        }

    } while (f = 1);
    for (int i = 0; i < 10; i++){
        for(int u = 0; u < 10; u++){
            printf(" %c", array[i][u]);
        }
        printf("\n");
    }
    // Your code here

    printf("\n\n");
    return 0;
}