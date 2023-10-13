/**
 * @file 3_Exercise2.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 
 * @date 13/10/23
*/

#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;
    int nChar = 0, nNew_line = 0, upperCase = 0, lowerCase = 0, nAlpha = 0, nNum = 0,
    alphaNum = 0, nSpace = 0, nPunt = 0, nCntrl = 0, nGraph = 0, nPrint = 0, nHex = 0,
    nAscii = 0, notAscii = 0;

    printf("Inserisci un testo terminante per '#':\n");
    while((ch = getchar()) != '#') {
        if(isupper(ch))
            upperCase++; //conta i caratteri maiuscoli
        else if(islower(ch))
            lowerCase++; // conta i caratteri minuscoli
        else if(isalpha(ch))
            nAlpha++; //conta i caratteri alfabetici
        else if(isdigit(ch))
            nNum++; //conta i caratteri numerici
        else if(isalnum(ch))
            alphaNum++; //conta i caratteri alfanumerici
        else if(isblank(ch)) {
            if(ch == '\n')
                nNew_line++; //conta i caratteri di nuova riga
        }
        else if(ispunct(ch))
            nPunt++;  //conta i caratteri di punteggiatura
        else if(iscntrl(ch))
            nCntrl++;  //conta i caratteri di controllo
        else if(isgraph(ch))
            nGraph++; //conta i caratteri grafici
        else if(isprint(ch))
            nPrint++;
        else if(isspace(ch)) {
            if(ch == ' ')
                nSpace++; //conta gli spazi
        }
        else if(isxdigit(ch))
            nHex++; //conta i caratteri esadecimali

        if(isascii(ch))
            nAscii++; //conta i caratteri ascii
        else
            notAscii++; //conta i caratteri non ascii

        nChar++; //conta i caratteri
    }

    printf("\n***********************************************************************");
    printf("\nNumero totale di caratteri: %d", nChar);
    printf("\nCaratteri maiuscoli: %d", upperCase);
    printf("\nCaratteri minuscoli: %d", lowerCase);
    printf("\nCaratteri alfabetici: %d", nAlpha);
    printf("\nCaratteri numerici: %d", nNum);
    printf("\nCaratteri alfanumerici: %d", alphaNum);
    printf("\nNumero di spazi: %d", nSpace);
    printf("\nNumero nuova riga: %d", nNew_line);
    printf("\nCaratteri punteggiatura: %d", nPunt);
    printf("\nCaratteri di controllo: %d", nCntrl);
    printf("\nCaratteri grafici: %d", nGraph);
    printf("\nCaratteri stampabili: %d", nPrint);
    printf("\nCaratteri hex: %d", nHex);
    printf("\nCaratteri ascii: %d", nAscii);
    printf("\nCaratteri non-ascii: %d", notAscii);

    printf("\n***********************************************************************");

    char UPPER = 'A', LOWER = 'b';
    printf("\nMaiuscolo\t->\t Minuscolo\nCarattere iniziale: %c,\tCarattere finale: %c", UPPER, tolower(UPPER)); //trasforma un carattere maiuscolo in uno minuscolo
    printf("\n\nMinuscolo\t->\t Maiuscolo\nCarattere iniziale: %c,\tCarattere finale: %c", LOWER, toupper(LOWER)); //trasforma un carattere minuscolo in uno maiuscolo

    printf("\n***********************************************************************");

    int letter = 0x2a; //carattere non ascii
    printf("\nCarattere non ascii: %#04x, Carattere trasformato ad ascii: %c", letter, toascii(letter)); //trasforma un carattere non ascii in uno ascii

    printf("\n\n");
    return 0;
}