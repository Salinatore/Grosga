#include <stdio.h>

#define MAX 5

int main(){

    //parte 1
    int numero = 75;
    char lettera = 'k';

    printf("%d\n", numero);
    printf("%c\n", lettera);
    printf("%c\n", numero);
    printf("%d\n", lettera);

    //parte2
    printf("\nparte 2:");

    float numero_float = 5.232;

    printf("numero float: %.1f", numero_float);

    int i = MAX;

    printf("MAX: %d", i);

    return 0;
}