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
#include <stdbool.h>
#include <time.h>
#include <math.h>


bool guess(long double x, long double y);
int xpTime(long start);
int xpDifficulty();

int main() {
    // Your code here
    char game = 'y';
    long double x, y, X, Y;
    long time = time(NULL);



    while(game == 'Y' || game == 'y') {

        printf("\n\nVuoi iniziare una nuova partita (Y/n)? ");
        scanf("%c", &game);

        if(game != 'y' && game != 'Y' && game != 'N' && game != 'n')
            printf("Inserisci Y (si) o n (no)\n\n");
    }

    printf("\nTerminato con successo ...");

    printf("\n\n");
    return 0;
}

bool guess(long double x, long double y) {


    return true;
}
int xpTime(long start) {
    long finish = time(NULL);
    long result = finish - start;


}
int xpDifficulty() {

}