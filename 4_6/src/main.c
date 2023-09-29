#include <stdio.h>
#include <stdlib.h>

/* AFLEVERINGS OPGAVE 4.6 */

// Funktion for at finde GCD
int FindGcd(int a, int b) {
  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }

  return a;
}

int main() {
  // To variabler til at indholde user input i string format
  char* input_one = malloc(sizeof(char));
  char* input_two = malloc(sizeof(char));

  int a, b;

  while (1) {
    // User input
    printf("Enter positive integer: \n");
    fgets(input_one, sizeof(input_one), stdin);
    printf("Enter positive integer: \n");
    fgets(input_two, sizeof(input_two), stdin);

    // Konverterer string til int
    char* endptr1 = NULL;
    char* endptr2 = NULL;
    a = strtol(input_one, &endptr1, 10);
    b = strtol(input_two, &endptr2, 10);

    // Bruger FindGcd funktionen til at finde GCD
    int gcd = FindGcd(a, b);
    if (a <= 0 || b <= 0) {
      // Error handling
      printf("Error: One or more numbers are not positive integers\n");
      break;
    } else {
      printf("Greatest common divisor between %d and %d is %d\n", a, b, gcd);
    }
  }
  return 0;
}