#include <stdio.h>
#include <stdlib.h>

/* AFLEVERINGS OPGAVE 4.6 */

// Funktion for at finde GCD
long FindGcd(long num1, long num2) {
  while (num2 != 0) {
    long temp = num2;
    num2 = num1 % num2;
    num1 = temp;
  }

  return num1;
}

int main() {
  // To variabler til at indholde user input i string format
  char* input_one = malloc(sizeof(char));
  char* input_two = malloc(sizeof(char));

  long user_input1 = 0;
  long user_input2 = 0;

  static const int kBase = 10;

  while (1) {
    // User input
    printf("Enter positive integer: \n");
    fgets(input_one, sizeof(input_one), stdin);
    printf("Enter positive integer: \n");
    fgets(input_two, sizeof(input_two), stdin);

    // Konverterer string til int
    char* endptr1 = NULL;
    char* endptr2 = NULL;
    user_input1 = strtol(input_one, &endptr1, kBase);
    user_input2 = strtol(input_two, &endptr2, kBase);

    // Bruger FindGcd funktionen til at finde GCD
    unsigned long gcd = FindGcd(user_input1, user_input2);
    if (user_input1 <= 0 || user_input2 <= 0) {
      // Error handling
      printf("Error: One or more numbers are not positive integers\n");
      break;
    }
    printf("Greatest common divisor between %lu and %lu is %lu\n", user_input1,
           user_input2, gcd);
  }

  free(input_one);
  free(input_two);

  return 0;
}