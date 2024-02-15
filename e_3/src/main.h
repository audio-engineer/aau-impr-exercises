#ifndef AAU_IMPR_EXERCISES_E_3_SRC_MAIN_H_
#define AAU_IMPR_EXERCISES_E_3_SRC_MAIN_H_

enum Constants {
  kWeekdayNameLength = 3,
  kTeamNameLength = 3,
  kDateLength = 5,
  kTimeLength = 5,
  kNumberOfRowItems = 8,
  kMaximumNumberOfTeams = 12,
  kMaximumNumberOfMatches = 90
};

typedef struct Match {
  char weekday[kWeekdayNameLength + 1];
  char date[kDateLength + 1];
  char time[kTimeLength + 1];
  char home_team[kTeamNameLength + 1];
  char away_team[kTeamNameLength + 1];
  int home_goals;
  int away_goals;
  int spectators;
} Match;

typedef struct Team {
  char name[kTeamNameLength + 1];
  int points;
  int goals_scored;
  int goals_conceded;
} Team;

#endif  // AAU_IMPR_EXERCISES_E_3_SRC_MAIN_H_
