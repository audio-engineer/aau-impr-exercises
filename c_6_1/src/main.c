#include "main.h"

#include <stdio.h>
#include <stdlib.h>

void AddVectors(Vector* vector_one, Vector* vector_two, Vector* result) {
  *result->component_one =
      *vector_one->component_one + *vector_two->component_one;
  *result->component_two =
      *vector_one->component_two + *vector_two->component_two;
}

int main() {
  int result_component_one = 0;
  int result_component_two = 0;

  // NOLINTBEGIN(readability-magic-numbers)
  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
  AddVectors(&(struct Vector){&(int){-56}, &(int){-23}},
             &(struct Vector){&(int){3}, &(int){4}},
             &(struct Vector){&result_component_one, &result_component_two});
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
  // NOLINTEND(readability-magic-numbers)

  printf("Result vector: (%d %d)", result_component_one, result_component_two);

  return EXIT_SUCCESS;
}
