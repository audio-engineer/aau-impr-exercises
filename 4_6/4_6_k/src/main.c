#include <stdio.h>

int main(void) {
  int num1;
  int num2;
  int gcd;

  // get numbers
  scanf_s("%d %d", &num1, &num2);
  printf("Insert two numbers: ");
  scanf("%d %d", &num1, &num2);

  // check which is bigger

  if (num1 > num2) {
    gcd = num1 + 1;  // we add 1 to compensate for the 'gcd--'
  } else {           // in the do-while loop. if not, 'gcd 5 5'
    gcd = num2 + 1;  // would return '1' instead of '5'
  }

  // divide both numbers until modulo is 0

  do {
    gcd--;
  } while (num1 % gcd != 0 || num2 % gcd != 0);

  // print result

  printf("The greatest common divisor is %d\n", gcd);
}