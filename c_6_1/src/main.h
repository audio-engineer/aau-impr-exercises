#ifndef AAU_IMPR_EXERCISES_C_6_1_SRC_MAIN_H_
#define AAU_IMPR_EXERCISES_C_6_1_SRC_MAIN_H_

typedef struct Vector {
  int* component_one;
  int* component_two;
} Vector;

void AddVectors(Vector* vector_one, Vector* vector_two, Vector* result);

#endif  // AAU_IMPR_EXERCISES_C_6_1_SRC_MAIN_H_
