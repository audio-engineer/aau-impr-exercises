#include <stdio.h>
#include <stdlib.h>

int main() {
  int input_m = 0;
  int input_n = 0;

  printf("Enter a variable m: ");
  scanf("%d", &input_m);
  printf("Enter a variable n: ");
  scanf("%d", &input_n);

  printf("\n");

  if (!(input_m > input_n)) {
    printf("Error: m must be bigger than n");

    return EXIT_FAILURE;
  }

  int side_one = (input_m ^ 2) - (input_n ^ 2);
  int side_two = 2 * input_m * input_n;
  int hypotenuse = (input_m ^ 2) + (input_n ^ 2);

  printf("The Pythagorean triple is:\n");
  printf("\tSide one: %d\n", side_one);
  printf("\tSide two: %d\n", side_two);
  printf("\tHypotenuse: %d\n", hypotenuse);

  return EXIT_SUCCESS;
}
