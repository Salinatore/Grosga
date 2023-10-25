/**
 * @file 5_Exercise1.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1
 * @date 23/10/23
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>

#define BLUE "\e[1;94m"
#define DEFAULT "\e[0;32m"

char random_char(); //random char generator

int main(){
    srand((unsigned int) time(NULL));

    char decrypted[10000], buffer;

    printf("\033[H\033[J\n");  //to clear terminal

    /** String form stdin with initial spaces*/
    printf("You can enter the string here--> ");
    bool string_has_began = false;
    int i = 0;

    do{
        buffer = getchar();

        if(buffer == ' ' && string_has_began == false)
            continue;
        else{
            if(buffer == '\n')
                break;
            else{
                decrypted[i] = buffer;
                i++;
                string_has_began = true; //the headspaces have been removed
            }
        }

        if(i == 9999) { //control
            printf("The string is too long sorry, error may occur");
            i = 9999;
            break;
        }
    }while(1);
    decrypted[i] = '\0'; //terminator add

    /** Crypted String Creation maintaing spaces */
    unsigned int string_width = strlen(decrypted);
    char encrypted[string_width+1];
    bool already_decrypted[string_width];
    fflush(stdin);

    for(i = 0; i < string_width; i++){
        if(decrypted[i] != ' ')
            encrypted[i] = random_char();
        else
            encrypted[i] = ' ';

        already_decrypted[i] = false; //used later for randomising decryption
    }
    encrypted[string_width] = '\0';

    /** Visual */
    printf("\nDecrypting your string--> " DEFAULT "%s", encrypted);
    fflush(stdout);
    sleep(1);
    int can_exit = 0;

    do{
        for(int k = 0; k < string_width; k++){ //reset the output
            printf("\b");
        }

        for(int k = 0; k < string_width; k++){
            if(already_decrypted[k] == false && rand()%2 == 0){ //random chance of being decrypted
                can_exit++;
                already_decrypted[k] = true;
            }

            if(already_decrypted[k] == true) //print
                printf(BLUE"%c", decrypted[k]);
            else
                printf(DEFAULT"%c", encrypted[k]);
        }

        fflush(stdout);
        usleep(900000);
    }while(can_exit < string_width);

    printf("\n\n");
    return 0;
}

char random_char(){
    char string[] = {"qwé*é*é()ty()uiopò°##ghjklz§cvbnm"};

    return string[rand()%33];
}
