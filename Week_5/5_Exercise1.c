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

#define DELAY 9000

char random_char(); //random char generator

int main(){
    srand((unsigned int) time(NULL));

    char decrypted[10000], buffer;

    printf("\033[H\033[J\n");  //clear terminal

    /** Getting string form stdin*/
    printf("You can enter the string here--> ");
    bool string_has_began = false;
    int i;

    for(i = 0; ; ){
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
    }
    decrypted[i] = '\0';

    /** Creating Crypted String*/
    unsigned int string_width = strlen(decrypted);
    char encrypted[string_width+1];

    for(i = 0; i < string_width; i++){
        if(decrypted[i] != ' ')
            encrypted[i] = random_char();
        else
            encrypted[i] = ' ';
    }
    encrypted[string_width] = '\0';

    /** Visual */
    printf("\nDecrypting your string--> %s", encrypted);
    fflush(stdout);
    sleep(1);

    for(int count = (int)string_width; count > 0; count--){
        for(int k = 0; k < count; k++){ //cleaning the output
            printf("\b");

            fflush(stdout);
            usleep(DELAY);
        }

        for(int k = string_width-count; k < string_width; k++){ //print
            if(k <= (string_width - count)){
                printf("%c", decrypted[k]);
            }
            else{
                printf("%c", encrypted[k]);
            }

            fflush(stdout);
            usleep(DELAY);
        }
    }

    return 0;
}

char random_char(){
    char string[] = {"qwé*é*é()ty()uiopasdfghjklzxcvbnm"};

    return string[rand()%26];
}
