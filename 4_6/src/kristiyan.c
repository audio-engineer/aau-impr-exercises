#include <stdio.h>

int main(void) {
    
    int a, b, gcd;

    // get numbers

    printf("Insert two numbers: ");
    scanf("%d %d", &a, &b);

    // check which is bigger

    if (a > b) {
        gcd = a + 1;    // we add 1 to compensate for the 'gcd--' 
    } else {            // in the do-while loop. if not, 'gcd 5 5' 
        gcd = b + 1;    // would return '1' instead of '5'
    }

    // divide both numbers until modulo is 0

    do {
        gcd--;
    } while (a % gcd != 0 || b % gcd != 0);

    // print result
    
    printf("The greatest common divisor is %d\n", gcd);
}