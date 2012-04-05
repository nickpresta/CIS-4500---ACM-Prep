#include <algorithm>
#include <iostream>
#include <vector>

const int MAX_TEAMS = 70;
const int MAX_TABLES = 50;

typedef struct {
  int id;
  int num_members;
} Team;

typedef struct {
  int id;
  int num_seats;
} Table;

typedef std::vector<std::vector<int>> Seats;

bool sort_teams(const Team i,  const Team j) {
  return i.num_members > j.num_members;
}

bool seat_members(std::vector<Team> &teams, std::vector<Table> &tables, Seats &seats) {
  int teams_size = teams.size();
  int tables_size = tables.size();

  for (int i = 0; i < teams_size; ++i) {
    Team *team = &teams[i];
    for (int j = 0; j < tables_size; ++j) {
      Table *table = &tables[j];
      if (team->num_members > 0 && table->num_seats > 0) {
        --team->num_members;
        --table->num_seats;
        ++seats[team->id][table->id];

        if (seats[team->id][table->id] > 1) {
          // More than 1 person from the same team is at this table
          return false;
        }
      } else if (team->num_members > 0) {
        continue;
      } else {
        break;
      }
    }
    if (team->num_members > 0) {
      return false; // more people than tables available
    }
  }

  return true;
}

int main() {
  int num_teams_input = 0;
  int num_tables_input = 0;
  std::vector<Team> teams(MAX_TEAMS);
  std::vector<Table> tables(MAX_TABLES);

  while (std::cin >> num_teams_input >> num_tables_input) {
    if (num_teams_input == 0 && num_tables_input == 0) {
      break;
    }

    for (int i = 0; i < num_teams_input; ++i) {
      teams[i].id = i;
      std::cin >> teams[i].num_members;
    }

    for (int i = 0; i < num_tables_input; ++i) {
      tables[i].id = i;
      std::cin >> tables[i].num_seats;
    }

    teams.resize(num_teams_input);
    tables.resize(num_tables_input);
    Seats seats(num_teams_input, std::vector<int>(num_tables_input));

    std::sort(teams.begin(), teams.end(), sort_teams);

    if (seat_members(teams, tables, seats)) {
      std::cout << "1\n";

      int teams_size = teams.size();
      int tables_size = tables.size();
      for (int i = 0; i < teams_size; ++i) {
        for (int j = 0; j < tables_size; ++j) {
          if (seats[i][j] > 0) {
            std::cout << j + 1 << " ";
          }
        }
        std::cout << "\n";
      }
    } else {
      std::cout << "0\n";
    }
  }

  return 0;
}
