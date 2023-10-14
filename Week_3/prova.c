#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
    srand(time(NULL));

    int meridiani = rand()%181;

    printf("Meridiani: %d", meridiani);
}