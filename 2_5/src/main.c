#include "main.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
  char input_buffer[kBufferSize];
  char* end = NULL;

  printf("Enter a number of seconds: ");

  char* output = fgets(input_buffer, (int)sizeof(input_buffer), stdin);

  if (output == NULL) {
    return EXIT_FAILURE;
  }

  unsigned long input_seconds_long = strtol(input_buffer, &end, kBase);

  if (*end != '\n') {
    return EXIT_FAILURE;
  }

  unsigned long seconds_per_minute = kSeconds;
  unsigned long seconds_per_hour = seconds_per_minute * kSeconds;
  unsigned long seconds_per_day = seconds_per_hour * kHours;
  unsigned long seconds_per_week = seconds_per_day * kDays;

  unsigned long weeks = input_seconds_long / seconds_per_week;
  input_seconds_long %= seconds_per_week;

  unsigned long days = input_seconds_long / seconds_per_day;
  input_seconds_long %= seconds_per_day;

  unsigned long hours = input_seconds_long / seconds_per_hour;
  input_seconds_long %= seconds_per_hour;

  unsigned long minutes = input_seconds_long / seconds_per_minute;

  unsigned long seconds = input_seconds_long % seconds_per_minute;

  printf("This number of seconds is equivalent to:\n");
  printf("Weeks: %ld\n", weeks);
  printf("Days: %ld\n", days);
  printf("Hours: %ld\n", hours);
  printf("Minutes: %ld\n", minutes);
  printf("Seconds: %ld\n", seconds);

  return EXIT_SUCCESS;
}
