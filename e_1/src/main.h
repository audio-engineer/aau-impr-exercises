#ifndef AAU_IMPR_EXERCISES_E_1_SRC_MAIN_H_
#define AAU_IMPR_EXERCISES_E_1_SRC_MAIN_H_

enum Constants { kInputBufferSize = 256 };

enum BinaryOperators {
  kAddition = '+',
  kSubtraction = '-',
  kMultiplication = '*',
  kDivision = '/',
  kExponentiation = '^'
};

enum UnaryOperators {
  kSquareRoot = '#',
  kNegation = '%',
  kMultiplicativeInverse = '!',
  kExit = 'q'
};

typedef struct OperationInputParameters {
  char* math_operator;
  double* second_operand;
} OperationInputParameters;

void DoNextOperation(const OperationInputParameters* operation_input_parameters,
                     double* accumulator);

double RunCalculator();

#endif  // AAU_IMPR_EXERCISES_E_1_SRC_MAIN_H_
