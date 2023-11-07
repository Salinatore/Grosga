/**
 * @file 7_Exercise2.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1 
 * @date 07/11/23
*/

#include <stdio.h>
#include <stdlib.h>
#include "7_Exercise1.c"

int main() {
    FILE *database = fopen("Week_7/database.txt", "a+"); //a+ = open or create


    fclose(database);
    printf("\n\n");
    return EXIT_SUCCESS;
}