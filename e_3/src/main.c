#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
Match matches[kMaximumNumberOfMatches];
Team teams[kMaximumNumberOfTeams];

int total_teams = 0;
int total_matches = 0;
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

void ReadMatchesFromFile(const char* const file_name) {
  FILE* file = fopen(file_name, "r");

  if (!file) {
    printf("Could not open file %s\n", file_name);

    exit(EXIT_FAILURE);
  }

  while (
      kNumberOfRowItems ==
      // NOLINTNEXTLINE(clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling)
      fscanf(file, "%s %s %s %s - %s %d - %d %d\n",
             matches[total_matches].weekday, matches[total_matches].date,
             matches[total_matches].time, matches[total_matches].home_team,
             matches[total_matches].away_team,
             &matches[total_matches].home_goals,
             &matches[total_matches].away_goals,
             &matches[total_matches].spectators)) {
    total_matches++;
  }

  fclose(file);
}

void UpdateTeams() {
  for (int i = 0; i < total_matches; i++) {
    int home_team_index = -1;

    for (int j = 0; j < total_teams; j++) {
      if (strcmp(teams[j].name, matches[i].home_team) == 0) {
        home_team_index = j;
        break;
      }
    }

    if (home_team_index == -1) {
      strcpy(teams[total_teams].name, matches[i].home_team);

      home_team_index = total_teams;
      total_teams++;
    }

    teams[home_team_index].goals_scored += matches[i].home_goals;
    teams[home_team_index].goals_conceded += matches[i].away_goals;

    int away_team_index = -1;
    for (int j = 0; j < total_teams; j++) {
      if (strcmp(teams[j].name, matches[i].away_team) == 0) {
        away_team_index = j;

        break;
      }
    }

    if (away_team_index == -1) {
      strcpy(teams[total_teams].name, matches[i].away_team);

      away_team_index = total_teams;
      total_teams++;
    }

    teams[away_team_index].goals_scored += matches[i].away_goals;
    teams[away_team_index].goals_conceded += matches[i].home_goals;

    if (matches[i].home_goals > matches[i].away_goals) {
      teams[home_team_index].points += 3;
    } else if (matches[i].home_goals < matches[i].away_goals) {
      teams[away_team_index].points += 3;
    } else {
      teams[home_team_index].points++;
      teams[away_team_index].points++;
    }
  }
}

void SortTeams() {
  for (int i = 0; i < total_teams - 1; i++) {
    for (int j = 0; j < total_teams - i - 1; j++) {
      if (teams[j].points < teams[j + 1].points ||
          (teams[j].points == teams[j + 1].points &&
           (teams[j].goals_scored - teams[j].goals_conceded) <
               (teams[j + 1].goals_scored - teams[j + 1].goals_conceded))) {
        Team temp = teams[j];

        teams[j] = teams[j + 1];
        teams[j + 1] = temp;
      }
    }
  }
}

void PrintStandings() {
  printf("%-10s%-8s%-15s%-15s\n", "Holdnavn", "Point", "Mål-af-hold",
         "Mål-mod-hold");

  for (int i = 0; i < total_teams; i++) {
    printf("%-10s%-8d%-15d%-15d\n", teams[i].name, teams[i].points,
           teams[i].goals_scored, teams[i].goals_conceded);
  }
}

int main() {
  const char* filename = "kampe-2023-2024.txt";

  ReadMatchesFromFile(filename);
  UpdateTeams();
  SortTeams();
  PrintStandings();

  return EXIT_SUCCESS;
}
