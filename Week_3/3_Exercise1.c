/**
 * @file 3_Exercise1.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 
 * @date 09/10/23
*/

/*
 * ESERCIZIO 1
 * Indovina il continente
 * In questo gioco, il computer visualizza una coppia di coordinate generata in maniera random sullo schermo per un breve periodo di tempo.
 * Il giocatore deve indovinare a quale continente appartiene la coppia di coordinate generate; fino a quando l’utente indovina, il gioco prosegue con
 * la generazione di una nuova coppia di coordinate. L'obiettivo è quello di continuare il processo il più a lungo possibile.
 * Al termine del gioco il programma calcolerà un punteggio ottenuto, quantomeno sulla base del numero di iterazioni eseguite
 * (è possibile valutare altri criteri, ad esempio, la velocità con cui l’utente risponde, oppure un calcolo basato sulla difficoltà delle coordinate prodotte)
 * e inviterà il giocatore a giocare di nuovo.
 * N.B.: i margini che definiscono i confini dei vari continenti sono decisi da voi
 */
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define max_lenght 80

int guess(int x, int y);
int xpTime(long start);
int xpDifficulty(int x, int y);
double velocita_Decadimento(double t);

int main() {
    srand(time(NULL));
    char game = 'y', user_guess[max_lenght], indovina[max_lenght];
    int score, count;
    long game_time;

    /** Game session */
    do {
        score = 0, count = 0, game_time = time(NULL);

        while(1) {
            /** Randomizzatore meridiani e paralleli e il loro segno */
            int meridiani = rand() % 181, paralleli = rand() % 91;
            if(rand() % 2 == 0)
                meridiani *= -1;
            if(rand() % 2 == 0)
                paralleli *= -1;

            printf("\033[H\033[J");
            printf("Coordinate: %d paralleli, %d meridiani", paralleli, meridiani);
            getchar();
            printf("\033[H\033[J");  //Clear the screen

            printf("\n Inserisci la tua risposta: \n [1] America \n [2] Asia \n [3] Europa \n [4] Africa \n [5] Oceania \n [6] Antartide \n [7] Oceano");
            printf("\n Risposta: ");
            printf("%d", guess(paralleli, meridiani));
            scanf("%d", &user_guess);

            if (user_guess < 1 || user_guess > 7){
              printf("\n Risposta non valida");
                break;
            }

            if(guess(paralleli, meridiani) != user_guess) {
                printf("Sbagliato! La risposta corretta era '%d'", guess(paralleli, meridiani));
                break;
            }
            else {
                printf("Hai indovinato!");
                score += xpDifficulty(meridiani, paralleli);
                score += xpTime(game_time);
                printf("\n*************************************************************************\n");
                count++;
            }
        }
        score += count * 10; //incremento score per iterazioni vinte

        /** Stampa dei punti ottentuti */
        printf("\nUSER SCORE: %d", score);
        printf("\n*************************************************************************");

        /** New Game **/
        printf("\n\nVuoi iniziare una nuova partita (Y/n)? ");
        scanf(" %c", &game);

        if(game != 'y' && game != 'Y' && game != 'N' && game != 'n') //alert
            printf("Inserisci Y (si) o n (no)");

    } while(game != 'N' && game != 'n');

    printf("\n\nTerminato con successo ...");

    printf("\n\n");
    return 0;
}

/** Restituisce i punti in base al tempo **/
int xpTime(long start) {
    long finish = time(NULL);
    double result = (double)finish - (double)start; //delta tempo

    return velocita_Decadimento(result);
}

/** Funzione per il calcolo della velocita di decadimento**/
double velocita_Decadimento(double t) {
    const double tolerance = 100000000000.0; //valore di grandezza dei punti
    double k = 0.01; //velocità decadimento
    return tolerance / (1 + k * t);
}

/** Funzione per il calcolo dei punti in base alle coordinate **/
int xpDifficulty(int x, int y) {
    const int incremento = 10;
    return (int) (incremento * sqrt(pow(x, 2) + pow(y, 2)));
}

/** Funzione per restituire il continente corrispondente */
int guess(int x, int y) {
    if( x <= 70 && x >= -60 && y >= -180 && y <= -45){
    return 1; //america
    }
    if( x <= 35 && x >= -35 && y >= -20 && y <= 45){
    return 4; //africa
    }
    if( x <= 80 && x >= 5 && y >= 40 && y <= 180){
    return 2; //asia
    }
    if( x <= 75 && x >= 35 && y >= -10 && y <= 40){
    return 3; //europa
    }
    if( x <= 5 && x >= -45 && y >= 90 && y <= 180){
    return 5; //oceania
    }
    if( x <= -60 && x >= -80 && y >= -180 && y <= 180){
    return 6; //antartide
    }

    return 7; //default
}
