/**
 * @file Esercizio1.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.2
 * @date 2023-10-01
*/

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    //declaration-->
    char c = 'a';
    int i = 27, l;
    short int si = -1;
    long int li = -1;
    unsigned char uc = 1;
    unsigned int ui = 1;
    unsigned long ul = 1;
    float f = -1;
    double d = -1;
    long double ld = -1;

    //stampo variabili con le dimensioni che occupano
    printf("Stampo variabili con le dimensioni che occupano-->");
    printf("\nCARATTERE");
    	printf("\n valore: %c -- dimensione: %ld", c, sizeof(c));
    printf("\nINTERO");
    	printf("\n valore: %d -- dimensione: %ld", i, sizeof(i));
    printf("\nINTERO CORTO");
    	printf("\n valore: %d -- dimensione: %ld", si, sizeof(si));
    printf("\nINTERO LUNGO");
    	printf("\n valore: %ld -- dimensione: %ld", li, sizeof(li));
    printf("\nCARATTERE SENZA SEGNO");
    	printf("\n valore: %c -- dimensione: %ld", uc, sizeof(uc));
    printf("\nINTERO SENZA SEGNO");
		printf("\n valore: %d -- dimensione: %ld", ui, sizeof(ui));
    printf("\nINTERO LUNGO SENZA SEGNO");
		printf("\n valore: %ld -- dimensione: %ld", ul, sizeof(ul));
	printf("\nVARIABILE MOBILE CON PRECISIONE SINGOLA");
    	printf("\n valore: %f -- dimensione: %ld", f, sizeof(f));
    printf("\nVARIABILE MOBILE CON PRECISIONE DOPPIA");
    	printf("\n valore: %f -- dimensione: %ld", d, sizeof(d));
    printf("\nVARIABILE MOBILE CON PRECISIONE ESTESA");
    	printf("\n valore: %Lf -- dimensione: %ld", ld, sizeof(ld));
    printf("\n\n");

    //stampo usando i vari modificatori e il numero dei caratteri che usano
    printf("Stampo usando i vari modificatori e il numero dei caratteri che usano-->");
    l = printf("\n %-d", i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n %+d", i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n % d", i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n %#d",i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n %0d", i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n %10d", i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n %.10d", i);
    printf(" -- numero di caratteri: %d", l);
    l = printf("\n %ld", i);
    printf(" -- numero di caratteri: %d", l);
    printf("\n\n");
    
    //stampo usando i valori minimi e massimi di ogni tipo di variabile
    printf("Stampo i valori minimi e massimi di ogni variabile-->");
    printf("\nCARATTERE:");
    	printf("%d", CHAR_BIT);
    printf("\nINTERO");
    	printf("\n minimo: %d", INT_MIN);
    printf("\nINTERO CORTO");
    	printf("\n minimo: %d", INT_MAX);
    printf("\nINTERO LUNGO");	
    	printf("\n minimo: %ld, massimo: %ld", LONG_MIN, LONG_MAX);
    printf("\nCARATTERE SENZA SEGNO");
        printf(": %d", UCHAR_MAX);
    printf("\nINTERO SENZA SEGNO");
        printf(": %d", UINT_MAX);
    printf("\nINTERO LUNGO SENZA SEGNO");
		printf(": %ld", ULONG_MAX);
	printf("\nVARIABILE MOBILE CON PRECISIONE SINGOLA");
		printf("\n minimo: %f, massimo: %f", FLT_MIN, FLT_MAX);
    printf("\nVARIABILE MOBILE CON PRECISIONE DOPPIA");
		printf("\n minimo: %f, massimo: %f", DBL_MIN, DBL_MAX);
    printf("\nVARIABILE MOBILE CON PRECISIONE ESTESA");
    	printf("\n minimo: %Lf, massimo: %Lf", LDBL_MIN, LDBL_MAX);
    
    printf("\n\n");
    return 0;
}