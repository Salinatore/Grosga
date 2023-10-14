#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main(){
    srand(time(NULL));

    int meridiani = rand()%181;

    printf("Meridiani: %d", meridiani);
}