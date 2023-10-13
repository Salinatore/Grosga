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

#define max_lenght 80

char guess(long double x, long double y);
int xpTime(long start);
int xpDifficulty(long double x, long double y);
double velocita_Decadimento(double t);

int main() {
    srand(time(NULL));
    char game = 'y', user_guess[max_lenght], indovina[max_lenght];
    int score = 0;

    /** Game session */
     do {
         long game_time = time(NULL);

         while(1) {
             long double x = rand(), y = rand(); //imposta il rand

             printf("\nInserisci la tua risposta (Africa, ...): ");
             scanf("% s", &user_guess);

             if(user_guess != guess(x, y)) {
                 printf("Sbagliato! La risposta corretta era %s", guess(x, y));
                 break;
             } else {
                printf("Hai indovinato!");
                score += xpDifficulty(x, y);
                printf("\n*************************************************************************+");
            }

         }
         score += xpTime(game_time);

         /** New Game **/
        printf("\n\nVuoi iniziare una nuova partita (Y/n)? ");
        scanf(" %c", &game);

        if(game != 'y' && game != 'Y' && game != 'N' && game != 'n') //alert
            printf("Inserisci Y (si) o n (no)");

    } while(game != 'N' && game != 'n');

    printf("\n\nUSER SCORE: %d", score);

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
    double k = 0.1; //velocità decadimento
    return tolerance / (1 + k * t);
}

/** Funzione per il calcolo dei punti in base alle coordinate **/
int xpDifficulty(long double x, long double y) {
    const int incremento = 10;
    return (int) (incremento * sqrt(pow(x, 2) + pow(y, 2)));
}
/** Funzione per restituire il continente corrispondente **/
char guess(long double x, long double y) {
    /**
     * todo
     * Restituisci una stringa in base al continente e suddividere i continenti + oceano in coordinate
     */

    return 'oceano';
}