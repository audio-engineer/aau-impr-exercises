#include "main.h"

#include <stdio.h>
#include <stdlib.h>

bool IsScanfInputValid(int number_of_assigned_input_items) {
  if (number_of_assigned_input_items == EOF ||
      number_of_assigned_input_items != 1) {
    printf("Invalid number_of_assigned_input_items. Try again.\n");

    while (fgetc(stdin) != '\n') {
    }

    return false;
  }

  return true;
}

int main() {
  char* input_seconds_string = malloc(sizeof(char));
  unsigned long input_seconds_long = 0;
  char* end = NULL;

  printf("Enter a number of seconds: ");

  int number_of_assigned_input_items = scanf("%s", input_seconds_string);

  if (!IsScanfInputValid(number_of_assigned_input_items)) {
    free(input_seconds_string);

    return EXIT_FAILURE;
  }

  input_seconds_long = strtol(input_seconds_string, &end, kBase);
  free(input_seconds_string);

  unsigned long seconds_per_minute = kSeconds;
  unsigned long seconds_per_hour = seconds_per_minute * kSeconds;
  unsigned long seconds_per_day = seconds_per_hour * kHours;
  unsigned long seconds_per_week = seconds_per_day * kDays;

  unsigned long weeks = 0;
  unsigned long days = 0;
  unsigned long hours = 0;
  unsigned long minutes = 0;
  unsigned long seconds = 0;

  weeks = input_seconds_long / seconds_per_week;
  input_seconds_long %= seconds_per_week;

  days = input_seconds_long / seconds_per_day;
  input_seconds_long %= seconds_per_day;

  hours = input_seconds_long / seconds_per_hour;
  input_seconds_long %= seconds_per_hour;

  minutes = input_seconds_long / seconds_per_minute;
  seconds = input_seconds_long % seconds_per_minute;

  printf("This number of seconds is equivalent to:\n");
  printf("Weeks: %ld\n", weeks);
  printf("Days: %ld\n", days);
  printf("Hours: %ld\n", hours);
  printf("Minutes: %ld\n", minutes);
  printf("Seconds: %ld\n", seconds);

  return EXIT_SUCCESS;
}
