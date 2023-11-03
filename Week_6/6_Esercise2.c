/**
 * @file 6_Exercise2.c
 * @author Alessandro Gardini n. matricola: 0001114867, Filippo Greppi n. matricola: 0001114837, Lorenzo Rossi n. matricola: 0001114876
 * @version 0.1
 * @date 30/10/23
*/

#include <stdio.h>

int main(){
    int n, *pn = &n;
    float f, *pf = &f;
    double d, *pd = &d;
    char c, *pc = &c;
    int array[5] = {10,20,30,40,50};

    /** initialing*/
    printf("Int-->");
    scanf("%d", pn);
    printf("Float-->");
    scanf("%f", pf);
    printf("Duble-->");
    scanf("%lf", pd);
    printf("Char-->");
    fflush(stdin);
    scanf("%c", pc);

    /** printing value*/
    printf("\nValue-->\n");
    printf("%d - %d\n", n, *pn);
    printf("%.3f - %.3f\n", f, *pf);
    printf("%.3lf - %.3lf\n", d, *pd);
    printf("%c - %c\n", c, *pc);

    /** printing memory addres*/
    printf("\nAddres-->\n");
    printf("Int--> %p - %p\n", &n, pn);
    printf("Float--> %p - %p\n", &f, pf);
    printf("Double--> %p - %p\n", &d, pd);
    printf("Char--> %p - %p\n", &c, pc);



}