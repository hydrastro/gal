#include <stdio.h>
#include "gal.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
    setbuf(stdout, NULL);
    char *m;

    printf("input string : ");
    m = readString(20);
    stringElement_t * sampleValue;
    sampleValue = parseString(m);
    printStringChain(sampleValue);


    printf("\n");
    printFraction(sampleValue->nextElement->value);

/* yeah, I know, this doesn't look very good lol */
/*    printf("\nx\n%d\n", sampleValue);
//printf("sampleValue numerator: %d\n", (*sampleValue).value.numerator);
/*printf("first numerator %d\n", (sampleValue->value).numerator);
printf(" numerator: %d\n", sampleValue->nextElement->nextElement->value.numerator);
printf(" numerator: %d\n", sampleValue->nextElement->nextElement->nextElement->value.numerator);
printf(" numerator: %d\n", sampleValue->nextElement->nextElement->nextElement->nextElement->value.numerator);
printf(" numerator: %d\n", sampleValue->nextElement->nextElement->nextElement->nextElement->nextElement->value.numerator);

/*
printf("SIZET %d\n", sizeof(stringElement_t));
printf("\nNORBAL \n%d\n", sampleValue);
printf("%d\n", sampleValue->nextElement);
printf("\nDEREF\n%d\n", &sampleValue);
printf("%d\n", &sampleValue->nextElement);
printf("\nPTR\n%d\n", *sampleValue);
printf("%d\n", *sampleValue->nextElement);

printf("%d\n", sampleValue->nextElement->value.numerator);
//printf("%d\n", *sampleValue->nextElement);
*/

    return(0);
}
