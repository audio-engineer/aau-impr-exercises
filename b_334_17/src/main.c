#include "main.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double FunctionG(double point_x) { return pow(point_x, 2) * sin(point_x); }

double FunctionH(double point_x) { return sqrt(4 - pow(point_x, 2)); }

double Trap(double lower_bound, double upper_bound,
            short number_of_subintervals, double function(double point_x)) {
  const double kSubintervalWidth =
      (upper_bound - lower_bound) / number_of_subintervals;
  double sum = 0;

  for (int i = 1; i < number_of_subintervals; i++) {
    double x_i = lower_bound + i * kSubintervalWidth;

    sum += function(x_i);
  }

  return (kSubintervalWidth / 2) *
         (function(lower_bound) * function(upper_bound) + 2 * sum);
}

int main() {
  printf("g(x) = x ^ 2 * sin(x):\n");

  double lower_bound = 0;
  double upper_bound = 3.14159;

  for (int i = 0; i < kNumberOfNValues; i++) {
    printf("n: %d\t\tT: %f\n", kNumberOfSubintervalsValues[i],
           Trap(lower_bound, upper_bound, kNumberOfSubintervalsValues[i],
                FunctionG));
  }

  printf("----------------------------------------\n");

  printf("h(x) = sqrt(4 - x ^ 2):\n");

  lower_bound = -2;
  upper_bound = 2;

  for (int i = 0; i < kNumberOfNValues; i++) {
    printf("n: %d\t\tT: %f\n", kNumberOfSubintervalsValues[i],
           Trap(lower_bound, upper_bound, kNumberOfSubintervalsValues[i],
                FunctionH));
  }

  return EXIT_SUCCESS;
}
