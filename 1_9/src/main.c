#include "main.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  float first_number = NAN;
  float second_number = NAN;
  float third_number = NAN;

  printf(
      "Please input three integers or floating-point numbers. Those will be "
      "added and then divided by %f\n",
      kDivisor);

  scanf("%f %f %f", &first_number, &second_number, &third_number);

  float calculation = (first_number + second_number + third_number) / kDivisor;
  printf("Result: %f\n", calculation);

  return EXIT_SUCCESS;
}
