#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* ReadUserInput(const char* const message) {
  printf("%s ", message);

  char* input = calloc(kBufferSize, sizeof(char));

  if (!input) {
    perror("Memory allocation failed");

    return NULL;
  }

  if (!fgets(input, kBufferSize, stdin)) {
    free(input);

    return NULL;
  }

  const size_t kUserInputLength = strlen(input);

  if (1 > kUserInputLength || '\n' != input[kUserInputLength - 1]) {
    free(input);

    return NULL;
  }

  input[kUserInputLength - 1] = '\0';

  return input;
}

int GetDiceRoll() {
  // NOLINTNEXTLINE(concurrency-mt-unsafe)
  return (rand() % (kDiceUpperBound - kDiceLowerBound + 1)) + kDiceLowerBound;
}

int GetOccurrenceCountOfTargetOutcome(const int target_outcome,
                                      const int* dice_roll_results_buffer,
                                      const int number_of_dice) {
  int occurrence_count = 0;

  for (int dice = 0; dice < number_of_dice; dice++) {
    if (target_outcome != dice_roll_results_buffer[dice]) {
      continue;
    }

    occurrence_count++;
  }

  return occurrence_count;
}

void RunRound(const int number_of_dice, int* dice_roll_results_buffer) {
  for (int dice = 0; dice < number_of_dice; dice++) {
    dice_roll_results_buffer[dice] = GetDiceRoll();
  }
}

void CheckForOnePair(const int number_of_dice, int* dice_roll_results_buffer) {
  RunRound(number_of_dice, dice_roll_results_buffer);

  printf("One pair:\t\t\t");

  for (int dice = 0; dice < number_of_dice; dice++) {
    printf("%d ", dice_roll_results_buffer[dice]);
  }

  int pair_dice_value = 0;
  int number_of_matches = 0;

  for (int die_value = kDiceUpperBound; die_value > kDiceLowerBound - 1;
       die_value--) {
    if (2 == number_of_matches) {
      break;
    }

    number_of_matches = 0;

    for (int dice = 0; dice < number_of_dice; dice++) {
      if (die_value != dice_roll_results_buffer[dice]) {
        continue;
      }

      if (2 > number_of_matches) {
        pair_dice_value = die_value;
        number_of_matches++;

        if (2 == number_of_matches) {
          break;
        }

        continue;
      }

      break;
    }
  }

  printf("-- Sum of the largest pair: %d", pair_dice_value * 2);
  printf("\n");
}

void CheckForTwoPairs(const int number_of_dice, int* dice_roll_results_buffer) {
  RunRound(number_of_dice, dice_roll_results_buffer);

  printf("Two pairs:\t\t\t");

  for (int dice = 0; dice < number_of_dice; dice++) {
    printf("%d ", dice_roll_results_buffer[dice]);
  }

  int pair_dice_value = 0;
  bool two_pairs_found = false;

  for (int die_value = kDiceUpperBound; die_value > kDiceLowerBound - 1;
       die_value--) {
    if (two_pairs_found) {
      break;
    }

    int count = GetOccurrenceCountOfTargetOutcome(
        die_value, dice_roll_results_buffer, number_of_dice);

    if (4 <= count) {
      two_pairs_found = true;

      pair_dice_value = die_value;
    }
  }

  printf("-- Sum of the two largest pairs: %d", pair_dice_value * 4);
  printf("\n");
}

int CheckForFourOfAKind(const int number_of_dice,
                        int* dice_roll_results_buffer) {
  RunRound(number_of_dice, dice_roll_results_buffer);

  printf("Four of a Kind:\t\t");

  int sum_of_four_of_a_kind = 0;

  int array[kDiceUpperBound] = {0};

  for (int dice = 0; dice < number_of_dice; dice++) {
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

  for (int i = 0; i < kDiceUpperBound; i++) {
    if (4 <= array[i]) {
      sum_of_four_of_a_kind = sum_of_four_of_a_kind + ((i + 1) * 4);
    }
  }

  printf("-- Sum of four of a kind: %d", sum_of_four_of_a_kind);
  printf("\n");

  return sum_of_four_of_a_kind;
}

void CheckForStraight(const int number_of_dice, int* dice_roll_results_buffer,
                      const int lower_bound, const char* name,
                      const int upper_bound) {
  RunRound(number_of_dice, dice_roll_results_buffer);
  printf("%s:\t\t", name);

  bool outcome_found[kDiceUpperBound - kDiceLowerBound] = {false};
  int extra_points = 0;

  for (int dice = 0; dice < number_of_dice; dice++) {
    printf("%d ", dice_roll_results_buffer[dice]);

    for (int outcome = lower_bound; outcome < upper_bound + 1; outcome++) {
      if (outcome == dice_roll_results_buffer[dice] &&
          !outcome_found[outcome - lower_bound]) {
        outcome_found[outcome - lower_bound] = true;

        extra_points = extra_points + outcome;
      }
    }
  }

  for (int outcome_index = 0;
       outcome_index < (kDiceUpperBound - kDiceLowerBound); outcome_index++) {
    if (!outcome_found[outcome_index]) {
      extra_points = 0;

      break;
    }
  }

  printf("-- Extra points: %d", extra_points);
  printf("\n");
}

void CheckForFullHouse(const int number_of_dice,
                       int* dice_roll_results_buffer) {
  RunRound(number_of_dice, dice_roll_results_buffer);

  printf("Full House:\t\t\t");

  for (int dice = 0; dice < number_of_dice; dice++) {
    printf("%d ", dice_roll_results_buffer[dice]);
  }

  int three_of_a_kind = 0;
  int pair = 0;

  for (int die_value = kDiceUpperBound; die_value >= kDiceLowerBound;
       die_value--) {
    int count = GetOccurrenceCountOfTargetOutcome(
        die_value, dice_roll_results_buffer, number_of_dice);

    if (count >= 3 && three_of_a_kind == 0) {
      three_of_a_kind = die_value;
    } else if (count >= 2) {
      pair = die_value;
    }
  }

  if (three_of_a_kind != 0 && pair != 0) {
    printf("-- Full House with three %d's and two %d's: %d", three_of_a_kind,
           pair, three_of_a_kind + pair * 2);
  }

  printf("\n");
}

void CheckForChance(const int number_of_dice, int* dice_roll_results_buffer) {
  RunRound(number_of_dice, dice_roll_results_buffer);

  printf("Chance:\t\t\t\t");

  for (int dice = 0; dice < number_of_dice; dice++) {
    printf("%d ", dice_roll_results_buffer[dice]);
  }

  int sum = 0;

  for (int dice = 0; dice < number_of_dice; dice++) {
    sum += dice_roll_results_buffer[dice];
  }

  printf("-- Sum of all dice: %d", sum);
  printf("\n");
}

void CheckForYatzy(const int number_of_dice, int* dice_roll_results_buffer) {
  RunRound(number_of_dice, dice_roll_results_buffer);

  printf("Yatzy:\t\t\t\t");

  for (int dice = 0; dice < number_of_dice; dice++) {
    printf("%d ", dice_roll_results_buffer[dice]);
  }

  int yatzy_value = dice_roll_results_buffer[0];
  bool is_yatzy = true;

  for (int dice = 1; dice < number_of_dice; dice++) {
    if (dice_roll_results_buffer[dice] != yatzy_value) {
      is_yatzy = false;

      break;
    }
  }

  if (!is_yatzy) {
    printf("-- No Yatzy :(");
  } else {
    printf("-- Yatzy with all dice showing %d", yatzy_value);
  }

  printf("\n");
}

void RunUpperSection(const int number_of_dice, int* dice_roll_results_buffer) {
  printf(
      "UPPER SECTION "
      "------------------------------------------------------------------\n");

  int one_indexed_target_outcome = 0;
  const char* const kUpperSectionNames[kUpperSections] = {
      "Ones", "Twos", "Threes", "Fours", "Fives", "Sixes"};

  for (int target_outcome = 0; target_outcome < kDiceUpperBound;
       target_outcome++) {
    RunRound(number_of_dice, dice_roll_results_buffer);

    printf("%s:\t\t\t\t", kUpperSectionNames[target_outcome]);

    for (int dice = 0; dice < number_of_dice; dice++) {
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

void RunLowerSection(const int number_of_dice, int* dice_roll_results_buffer) {
  printf(
      "LOWER SECTION "
      "------------------------------------------------------------------\n");

  CheckForOnePair(number_of_dice, dice_roll_results_buffer);
  CheckForTwoPairs(number_of_dice, dice_roll_results_buffer);
  CheckForFourOfAKind(number_of_dice, dice_roll_results_buffer);
  CheckForStraight(number_of_dice, dice_roll_results_buffer, kDiceLowerBound,
                   "Small Straight", kDiceUpperBound - 1);
  CheckForStraight(number_of_dice, dice_roll_results_buffer,
                   kDiceLowerBound + 1, "Large Straight", kDiceUpperBound);
  CheckForFullHouse(number_of_dice, dice_roll_results_buffer);
  CheckForChance(number_of_dice, dice_roll_results_buffer);
  CheckForYatzy(number_of_dice, dice_roll_results_buffer);
}

int main() {
  srand(time(NULL));

  printf("Welcome to the Yatzy CLI. Copyright © 2023 AAU\n");
  printf("\n");

  char* const kUserInput =
      ReadUserInput("Enter the number of dice you want to play with:");
  const int kNumberOfDice = atoi(kUserInput);
  free(kUserInput);

  // NOLINTBEGIN
  int* dice_roll_results_buffer = calloc(kNumberOfDice, sizeof(int));
  RunUpperSection(kNumberOfDice, dice_roll_results_buffer);
  RunLowerSection(kNumberOfDice, dice_roll_results_buffer);
  free(dice_roll_results_buffer);
  // NOLINTEND

  return EXIT_SUCCESS;
}
