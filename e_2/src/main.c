#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

U16 GetDiceRoll() {
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  return (rand() % (kDiceUpperBound - kDiceLowerBound + 1)) + kDiceLowerBound;
}

U16 GetOccurrenceCountOfTargetOutcome(const U16 target_outcome,
                                      const U16* dice_roll_results_buffer,
                                      const U16 number_of_dice) {
  U16 occurrence_count = 0;

  for (U16 dice = 0; dice < number_of_dice; dice++) {
    if (target_outcome != dice_roll_results_buffer[dice]) {
      continue;
    }

    occurrence_count++;
  }

  return occurrence_count;
}

void RunRound(const U16 number_of_dice, U16* dice_roll_results_buffer) {
  for (U16 dice = 0; dice < number_of_dice; dice++) {
    dice_roll_results_buffer[dice] = GetDiceRoll();
  }
}

U16 CheckForFourOfAKind(const U16 number_of_dice,
                        U16* dice_roll_results_buffer) {
  RunRound(number_of_dice, dice_roll_results_buffer);

  printf("Four of a Kind:\t\t");

  U16 sum_of_four_of_a_kind = 0;

  U16 array[kDiceUpperBound] = {0};

  for (U16 dice = 0; dice < number_of_dice; dice++) {
    printf("%d ", dice_roll_results_buffer[dice]);

    switch (dice_roll_results_buffer[dice]) {
      case kOne:
        array[kOne - 1]++;
        break;
      case kTwo:
        array[kTwo - 1]++;
        break;
      case kThree:
        array[kThree - 1]++;
        break;
      case kFour:
        array[kFour - 1]++;
        break;
      case kFive:
        array[kFive - 1]++;
        break;
      case kSix:
        array[kSix - 1]++;
        break;
      default:
        break;
    }
  }

  for (U16 i = 0; i < (U16)kDiceUpperBound; i++) {
    if (4 <= array[i]) {
      sum_of_four_of_a_kind = sum_of_four_of_a_kind + ((i + 1) * 4);
    }
  }

  printf("-- Sum of four of a kind: %d", sum_of_four_of_a_kind);
  printf("\n");

  return sum_of_four_of_a_kind;
}

void CheckForStraight(const U16 number_of_dice, U16* dice_roll_results_buffer,
                      const U16 lower_bound, const char* name,
                      const U16 upper_bound) {
  RunRound(number_of_dice, dice_roll_results_buffer);
  printf("%s:\t\t", name);

  bool outcome_found[kDiceUpperBound - kDiceLowerBound] = {false};
  U16 extra_points = 0;

  for (U16 dice = 0; dice < number_of_dice; dice++) {
    printf("%d ", dice_roll_results_buffer[dice]);

    for (U16 outcome = lower_bound; outcome < upper_bound + 1; outcome++) {
      if (outcome == dice_roll_results_buffer[dice] &&
          !outcome_found[outcome - lower_bound]) {
        outcome_found[outcome - lower_bound] = true;

        extra_points = extra_points + outcome;
      }
    }
  }

  for (U16 outcome_index = 0;
       outcome_index < (U16)(kDiceUpperBound - kDiceLowerBound);
       outcome_index++) {
    if (!outcome_found[outcome_index]) {
      extra_points = 0;

      break;
    }
  }

  printf("-- Extra points: %d", extra_points);
  printf("\n");
}

void RunUpperSection(const U16 number_of_dice, U16* dice_roll_results_buffer) {
  printf(
      "UPPER SECTION "
      "------------------------------------------------------------------\n");

  U16 one_indexed_target_outcome = 0;
  const char* kUpperSectionNames[kUpperSections] = {"Ones",  "Twos",  "Threes",
                                                    "Fours", "Fives", "Sixes"};

  for (U16 target_outcome = 0; target_outcome < (U16)kDiceUpperBound;
       target_outcome++) {
    RunRound(number_of_dice, dice_roll_results_buffer);

    printf("%s:\t\t\t\t", kUpperSectionNames[target_outcome]);

    for (U16 dice = 0; dice < number_of_dice; dice++) {
      printf("%d ", dice_roll_results_buffer[dice]);
    }

    one_indexed_target_outcome = target_outcome + 1;

    printf("-- Sum of all dice showing this number: %d",
           one_indexed_target_outcome *
               GetOccurrenceCountOfTargetOutcome(one_indexed_target_outcome,
                                                 dice_roll_results_buffer,
                                                 number_of_dice));
    printf("\n");
  }
}

void RunLowerSection(const U16 number_of_dice, U16* dice_roll_results_buffer) {
  printf(
      "LOWER SECTION "
      "------------------------------------------------------------------\n");

  CheckForFourOfAKind(number_of_dice, dice_roll_results_buffer);
  CheckForStraight(number_of_dice, dice_roll_results_buffer, kDiceLowerBound,
                   "Small Straight", kDiceUpperBound - 1);
  CheckForStraight(number_of_dice, dice_roll_results_buffer,
                   kDiceLowerBound + 1, "Large Straight", kDiceUpperBound);
}

int main() {
  srand(time(NULL));

  printf("Welcome to the Yatzy CLI. Copyright © 2023 AAU\n");
  printf("\n");

  // NOLINTBEGIN
  U16* dice_roll_results_buffer = calloc(20, sizeof(U16));
  RunUpperSection(20, dice_roll_results_buffer);
  RunLowerSection(20, dice_roll_results_buffer);
  free(dice_roll_results_buffer);
  // NOLINTEND

  return EXIT_SUCCESS;
}
