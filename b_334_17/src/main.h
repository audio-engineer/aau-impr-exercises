#ifndef AAU_IMPR_EXERCISES_B_334_17_SRC_MAIN_H_
#define AAU_IMPR_EXERCISES_B_334_17_SRC_MAIN_H_

enum Constants { kNumberOfNValues = 7 };

const short kNumberOfSubintervalsValues[kNumberOfNValues] = {2,  4,  8,  16,
                                                             32, 64, 128};

double FunctionG(double point_x);

double FunctionH(double point_x);

double Trap(double lower_bound, double upper_bound,
            short number_of_subintervals, double function(double point_x));

#endif  // AAU_IMPR_EXERCISES_B_334_17_SRC_MAIN_H_
