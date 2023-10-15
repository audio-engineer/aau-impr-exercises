#include "main.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PrintMenu() {
  printf("Welcome to the Calculator CLI. Copyright © 2023 AAU\n");
  printf("\n");

  printf(
      "When prompted for an operator, enter a character to select one of the "
      "following options, then press Return:\n");

  printf("Binary operations\n");
  printf("\t'+' Addition\n");
  printf("\t'-' Subtraction\n");
  printf("\t'*' Multiplication\n");
  printf("\t'/' Division\n");
  printf("\t'^' Exponentiation\n");

  printf("Unary operations\n");
  printf("\t'#' Square root\n");
  printf("\t'%%' Negation\n");
  printf("\t'!' Multiplicative inverse\n");
  printf("\n");

  printf("\t'q' Quit\n");
  printf("\n");
}

char* ReadUserInput(const char* message) {
  printf("%s ", message);

  char* input = malloc(kInputBufferSize * sizeof(char));

  if (NULL == input) {
    perror("Memory allocation failed");

    return NULL;
  }

  if (fgets(input, kInputBufferSize, stdin)) {
    const size_t kUserInputLength = strlen(input);

    if (1 > kUserInputLength || '\n' != input[kUserInputLength - 1]) {
      free(input);

      return NULL;
    }

    input[kUserInputLength - 1] = '\0';

    return input;
  }

  free(input);

  return NULL;
}

double* ReadSecondOperand(const char* message) {
  char* input = ReadUserInput(message);

  double* second_operand = malloc(sizeof(double));

  char* end = NULL;
  *second_operand = strtod(input, &end);

  if ('\0' != *end) {
    free(input);
    free(second_operand);

    return NULL;
  }

  free(input);

  return second_operand;
}

bool IsValidOperator(const char* operator) {
  if (1 < strlen(operator)) {
    return false;
  }

  switch (*operator) {
    case kAddition:
    case kSubtraction:
    case kMultiplication:
    case kDivision:
    case kExponentiation:
    case kSquareRoot:
    case kNegation:
    case kMultiplicativeInverse:
    case kExit:
      return true;
    default:
      return false;
  }
}

bool IsBinaryOperator(const char* operator) {
  switch (*operator) {
    case kAddition:
    case kSubtraction:
    case kMultiplication:
    case kDivision:
    case kExponentiation:
      return true;
    default:
      return false;
  }
}

void DoNextOperation(const OperationInputParameters* operation_input_parameters,
                     double* accumulator) {
  const OperationInputParameters kOperationInputParameters =
      *operation_input_parameters;

  switch (*kOperationInputParameters.math_operator) {
    case kAddition:
      *accumulator += *kOperationInputParameters.second_operand;
      return;
    case kSubtraction:
      *accumulator -= *kOperationInputParameters.second_operand;
      return;
    case kMultiplication:
      *accumulator *= *kOperationInputParameters.second_operand;
      return;
    case kDivision:
      if (0 == *kOperationInputParameters.second_operand) {
        return;
      }

      *accumulator /= *kOperationInputParameters.second_operand;
      return;
    case kExponentiation:
      *accumulator =
          pow(*accumulator, *kOperationInputParameters.second_operand);
      return;
    case kSquareRoot:
      if (0 > *accumulator) {
        return;
      }

      *accumulator = sqrt(*accumulator);
      return;
    case kNegation:
      *accumulator = -*accumulator;
      return;
    case kMultiplicativeInverse:
      *accumulator = 1 / *accumulator;
      return;
    default:
      return;
  }
}

void PrintAccumulator(const double* accumulator) {
  printf("Result so far is %lf.\n", *accumulator);
}

void PrintFinalAccumulator(const double* accumulator) {
  printf("Final result is: %lf\n", *accumulator);
}

double RunCalculator() {
  double accumulator = 0;

  PrintMenu();

  while (true) {
    char* math_operator = ReadUserInput("Enter operator:");
    double* second_operand = NULL;

    if (NULL == math_operator) {
      perror("Math operator could not be set");

      return EXIT_FAILURE;
    }

    if (!IsValidOperator(math_operator)) {
      printf("Invalid math operator. Try again.\n");

      free(math_operator);

      continue;
    }

    if (kExit == *math_operator) {
      free(math_operator);

      break;
    }

    if (IsBinaryOperator(math_operator)) {
      while (!(second_operand = ReadSecondOperand("Enter operand:"))) {
        printf("Second operand could not be set. Try again.\n");
      }
    } else {
      second_operand = malloc(sizeof(double));

      if (NULL == second_operand) {
        free(math_operator);

        perror("Memory allocation failed");

        return EXIT_FAILURE;
      }

      *second_operand = 0;
    }

    const OperationInputParameters kOperationInputParameters = {math_operator,
                                                                second_operand};

    DoNextOperation(&kOperationInputParameters, &accumulator);

    free(math_operator);
    free(second_operand);

    PrintAccumulator(&accumulator);
  }

  return accumulator;
}

int main() {
  double final_accumulator = RunCalculator();
  PrintFinalAccumulator(&final_accumulator);

  return EXIT_SUCCESS;
}
