/*Alessandro Gardini n. matricola: 0001114867
Filippo Greppi n. matricola:
Lorenzo Rossi n. matricola:

Exercise number: 1

*/

#include <stdio.h>

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
    printf("\nCARATTERE");
    	printf("\n minimo: -128, massimo: 127");
    printf("\nINTERO");
    	printf("\n minimo: -32768, massimo: 32767");
    printf("\nINTERO CORTO");
    	printf("\n minimo: -32768, massimo: 32767");
    printf("\nINTERO LUNGO");	
    	printf("\n minimo: -2147483648, massimo: 2147483647");
    printf("\nCARATTERE SENZA SEGNO");
    	printf("\n minimo: 0, massimo: 255");
    printf("\nINTERO SENZA SEGNO");
		printf("\n minimo: 0, massimo: 65535");
    printf("\nINTERO LUNGO SENZA SEGNO");
		printf("\n minimo: 0, massimo: 4294967295");
	printf("\nVARIABILE MOBILE CON PRECISIONE SINGOLA");
		printf("\n minimo: 1.2x10^-38, massimo: 3.4x10^38");
    printf("\nVARIABILE MOBILE CON PRECISIONE DOPPIA");
		printf("\n minimo: 2.2x10^-308, massimo: 1.8x10^308");
    printf("\nVARIABILE MOBILE CON PRECISIONE ESTESA");
    	printf("\n minimo: 3.4x10^-4932, massimo: 1.1x10^4932");
    
    printf("\n\n");
    return 0;
}
