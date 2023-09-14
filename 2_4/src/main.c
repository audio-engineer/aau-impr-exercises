#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  double first_double = NAN;
  double second_double = NAN;
  double third_double = NAN;

  printf("Enter three real numbers: ");
  scanf("%lf %lf %lf", &first_double, &second_double, &third_double);

  printf("The average is: %f\n",
         (first_double + second_double + third_double) / 3.0);

  return EXIT_SUCCESS;
}
