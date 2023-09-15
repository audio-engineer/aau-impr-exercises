#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  double p1_x = NAN;
  double p1_y = NAN;
  double p2_x = NAN;
  double p2_y = NAN;
  double p3_x = NAN;
  double p3_y = NAN;

  printf("Enter point 1: ");
  scanf("%lf %lf", &p1_x, &p1_y);

  printf("Enter point 2: ");
  scanf("%lf %lf", &p2_x, &p2_y);

  printf("Enter point 3: ");
  scanf("%lf %lf", &p3_x, &p3_y);

  double length_one = sqrt(pow((p2_x - p1_x), 2) + pow((p2_y - p1_y), 2));
  double length_two = sqrt(pow((p3_x - p2_x), 2) + pow((p3_y - p2_y), 2));
  double length_three = sqrt(pow((p3_x - p1_x), 2) + pow((p3_y - p1_y), 2));

  double total_length = length_one + length_two + length_three;

  printf("The total length is: %lf\n", total_length);

  return EXIT_SUCCESS;
}
