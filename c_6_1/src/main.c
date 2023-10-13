#include <stdio.h>

typedef struct Vector {
  int value_one;
  int value_two;
} Vector;

typedef struct Result {
  int* result_one;
  int* result_two;
} Result;

void AddVectors(Vector* vector_one, Vector* vector_two, Result* result) {
  *result->result_one = vector_one->value_one + vector_two->value_one;
  *result->result_two = vector_one->value_two + vector_two->value_two;
}

int main() {
  int result_one = 0;
  int result_two = 0;

  // NOLINTBEGIN(readability-magic-numbers)
  // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
  AddVectors(&(struct Vector){-56, -23}, &(struct Vector){3, 4},
             &(struct Result){&result_one, &result_two});
  // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
  // NOLINTEND(readability-magic-numbers)

  printf("Result vector values: (%d %d)", result_one, result_two);
}
