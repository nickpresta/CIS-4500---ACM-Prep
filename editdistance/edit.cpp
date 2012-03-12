#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class EditDistance {
  private:
    std::string m_source;
    int m_source_length;
    std::string m_target;
    int m_target_length;
    int m_del_cost;
    int m_ins_cost;
    int m_sub_cost;
    std::vector<std::vector<int>> m_distance_grid;

  public:
    EditDistance(std::string s, std::string t) : m_source(s), m_target(t) {
      m_source_length = m_source.length();
      m_target_length = m_target.length();
      // Initialize distance grid structure, and fill first row/column
      m_distance_grid = std::vector<std::vector<int>>(m_source_length + 1,
          std::vector<int>(m_target_length + 1));
      for (int i = 0; i <= m_source_length; ++i) {
        m_distance_grid[i][0] = i;
      }
      for (int i = 0; i <= m_target_length; ++i) {
        m_distance_grid[0][i] = i;
      }
      m_del_cost = m_ins_cost = m_sub_cost = 1;
    }
    void set_costs(int del, int ins, int sub) {
        m_del_cost = del;
        m_ins_cost = ins;
        m_sub_cost = sub;
    }
    int get_distance();
};

int EditDistance::get_distance() {
  for (int s = 1; s <= m_source_length; ++s) {
    const char source_cell = m_source[s - 1];
    for (int t = 1; t <= m_target_length; ++t) {
      const char target_cell = m_target[t - 1];

      int sub_cost;
      if (source_cell == target_cell) {
        sub_cost = 0;
      } else {
        sub_cost = m_sub_cost;
      }

      const int top = m_distance_grid[s - 1][t];
      const int left = m_distance_grid[s][t - 1];
      const int diagonal = m_distance_grid[s - 1][t - 1];

      const int del = top + m_del_cost;
      const int ins = left + m_ins_cost;
      // The sub_cost is calculated above
      const int sub = diagonal + sub_cost;

      const int cell = std::min(del, std::min(ins, sub));

      m_distance_grid[s][t] = cell;
    }
  }

  return m_distance_grid[m_source_length][m_target_length];
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "You must provide two strings to compare!" << std::endl;
    return 1;
  }

  EditDistance edit = EditDistance(std::string(argv[1]), std::string(argv[2]));
  std::cout << edit.get_distance() << std::endl;

  return 0;
}
