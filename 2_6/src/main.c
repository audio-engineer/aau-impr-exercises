#include <stdio.h>
#include <stdlib.h>

int main() {
  /*
   * First version
   */
  int c1, c2, c3, c4, scanRes;

  printf("Enter input on the following line\n");

  scanRes = scanf("%c%c%c%c", &c1, &c2, &c3, &c4);

  printf("c1 = %c, c2 = %c, c3 = %c, c4 = %c\n", c1, c2, c3, c4);
  printf("scanRes = %d\n", scanRes);

  /*
   * Second version
   */
  int i1, i2;

  printf("Enter input on the following line\n");

  scanRes = scanf("%d%d", &i1, &i2);

  printf("i1 = %d, i2 = %d\n", i1, i2);
  printf("scanRes = %d\n", scanRes);

  /*
   * Third version
   */
  printf("Enter input on the following line\n");

  scanRes = scanf("%d;%d", &i1, &i2);

  printf("i1 = %d, i2 = %d\n", i1, i2);
  printf("scanRes = %d\n", scanRes);

  /*
   * Fourth version
   */
  printf("Enter input on the following line\n");

  scanRes = scanf("%d abe %d", &i1, &i2);

  printf("i1 = %d, i2 = %d\n", i1, i2);
  printf("scanRes = %d\n", scanRes);

  /*
   * Fifth version
   */
  double d1, d2;

  printf("Enter input on the following line\n");

  scanRes = scanf("%lf %lf", &d1, &d2);

  printf("d1 = %10.5f, d2 = %8.4f\n", d1, d2);
  printf("scanRes = %d\n", scanRes);

  return EXIT_SUCCESS;
}
